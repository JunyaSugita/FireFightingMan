#include "Scene.h"

//コンストラクタ
Scene::Scene() {
	player = new Player;
	bullet = new Bullet;
	rescued = new Rescued;
	map = new Map;
	fire = new Fire;
	goal = new Goal;
	ene = new Enemy;
	particle = new Particle;
	stageSelect = new StageSelect;
	gameover = new Gameover;
	tutorial = new Tutorial;
	damParticle = new DamParticle;
	pause = new Pause;
	smoke = new Smoke;

	x = 640;
	y = -480;
	isPush = 0;
	time = 0;
	isChange = 0;
}

//デスストラクタ
Scene::~Scene() {
	delete player;
	delete bullet;
	delete rescued;
	delete map;
	delete fire;
	delete goal;
	delete ene;
	delete particle;
	delete gameover;
	delete tutorial;
	delete damParticle;
	delete smoke;
}


///-----関数-----///
void Scene::Update(char* keys, char* oldkeys) {

	//例外処理
	if (keys == nullptr || oldkeys == nullptr) {
		return;
	}

	GetHitKeyStateAll(keys);
	ClearDrawScreen();

	GetJoypadDirectInputState(DX_INPUT_PAD1, &padInput);
	pad = GetJoypadInputState(DX_INPUT_PAD1);

	switch (player->scene) {
		//タイトル
		case MAIN_TITLE:
			if (time > 14) {
				if (pad & PAD_INPUT_2) {
					isPush = 1;
					isChange = 1;
					reset();
				}
			}
			else {
				time++;
			}
			damParticle->Reset();
			stageSelect->Reset();

			if (isChange == 1) {
				if (y + 480 < WIN_HEIGHT) {
					y += 64;
				}
				time++;
				if (time == 65) {
					player->scene = 2;
					time = 0;
					isChange = 0;
				}
			}
			break;

			//ステージセレクト
		case STAGE_SELECT:
			if (isChange == 0) {
				if (time < 21) {
					time++;
				}
			}

			if (time >= 21) {
				y -= 64;
			}
			stageSelect->Select(padInput.Y, pad);
			if (stageSelect->isStop == 1) {
				if (pad & PAD_INPUT_2) {
					if (isPush == 0) {
						if (isChange == 0) {
							isChange = 1;
							stageSelect->time = 0;
							stageSelect->Move();
						}
					}
				}
				else {
					isPush = 0;
				}
			}

			if (isChange == 1) {
				time++;
				//マップ選択
				if (time > 95) {
					map->MapSelect(stageSelect->select);
					player->Spawn(map->map);
					rescued->Spawn(map->map);
					fire->SetFire(map->map);
					ene->Make(map->map);
					player->scene = 1;
					time = 0;
					isChange = 0;
					y = -480;
					stageSelect->isStop = 0;
				}
			}

			break;
			//ゲーム
		case MAIN_GAME:
			//チュートリアルの表示
			tutorial->CountTimer();
			tutorial->StepUpdate(stageSelect->select, pad, rescued->isRescued, player->player.transform.x, fire->fire[5].isFire, fire->fire[6].isFire, fire->fire[7].isFire);

			//プレイヤー位置の保存
			player->SaveOldPlayer();

			//プレイヤーのジャンプの可否
			player->GetPlayerBottom(map->BLOCK_SIZE);

			//プレイヤーの移動
			player->Dash(pad, rescued->isRescued);
			player->PlayerJump(pad, rescued->isRescued, map->map);
			player->PlayerMove(padInput.X, padInput.Rx, padInput.Ry, rescued->isRescued);
			player->CheckStick(padInput.Ry, rescued->isRescued);

			//弾の発射
			player->PlayerShot(padInput.Rx, padInput.Ry, rescued->isRescued);

			//弾の挙動
			player->bullet->BulletMove(player->G, padInput.X, padInput.Y);

			//消化
			fire->FireFighting(player->bullet->bullet, smoke);

			//マップチップ上の座標位置の取得
			player->GetOldPlayer(map->BLOCK_SIZE);
			player->GetPlayer(map->BLOCK_SIZE);
			player->bullet->GetBullet(map->BLOCK_SIZE);

			//当たり判定
			player->BlockCollision(map->map);
			player->bullet->BlockCollision(map->map);
			rescued->RescuedCollision(player, player->hp, stageSelect->select);
			goal->GetGoal(player, rescued, player->hp, fire);
			gameover->GotoGameover(player->scene, player->hp);
			//プレイヤーが地面で浮かないように
			player->GetPlayer(map->BLOCK_SIZE);
			player->GetPlayerBottom(map->BLOCK_SIZE);
			player->CheckStick(padInput.Ry, rescued->isRescued);
			player->DownPlayer(map->map, map->BLOCK_SIZE);
			rescued->Move(player);
			rescued->CatchRescued();

			//敵の出現
			ene->Update(player->bullet->bullet, map->map);

			//スクロール
			player->GetScroll();

			for (int i = 0; i < 100; i++) {
				player->PlayerDamage(fire->fire[i].transform.x, fire->fire[i].transform.y, fire->fire[i].Xr, fire->fire[i].isFire);
				particle->Emit(fire->fire[i].transform.x, fire->fire[i].transform.y, fire->fire[i].Xr, fire->fire[i].isFire);
			}
			for (int i = 0; i < 10; i++) {
				player->PlayerDamage(ene->enemy[i].transform.x, ene->enemy[i].transform.y + ene->enemy[i].hp / 4, ene->enemy[i].hp / 4, ene->enemy[i].hp);
				particle->Emit(ene->enemy[i].transform.x, ene->enemy[i].transform.y + ene->enemy[i].hp / 4, ene->enemy[i].hp / 4, 1);
			}
			player->DamageCount();
			particle->Move();

			smoke->Move();

			pause->ChangePause(pad, player->scene);
			pause->Move();
			break;

		case GAMEOVER:
			gameover->GotoTitle(pad, rescued, player, fire, goal, particle);

			break;

		case PAUSE:
			pause->ChangeScene(pad, player->scene);
			pause->Move();

			//選択
			if (padInput.Y < 0 && pause->isReset == 0 || pad & PAD_INPUT_UP) {
				pause->isReset = 1;
			}
			else if (padInput.Y > 0 && pause->isReset == 1 || pad & PAD_INPUT_DOWN) {
				pause->isReset = 0;
			}

			//リセットorタイトル
			if (pad & PAD_INPUT_2) {
				//リセット
				if (isPush == false) {
					if (pause->isReset == 1) {
						isPush = true;
						pause->isPause = false;
						restart();
						player->scene = MAIN_GAME;
					}
					//タイトルへ
					else if (pause->isReset == 0) {
						isPush = true;
						reset();
						pause->isPause = false;
						pause->xr = 0;
						pause->yr = 0;
					}
				}
			}
			else {
				isPush = false;
			}

			break;
	}
}

void Scene::reset() {
	delete player;
	delete bullet;
	delete rescued;
	delete map;
	delete fire;
	delete goal;
	delete ene;
	delete particle;
	delete gameover;
	delete tutorial;
	delete damParticle;
	delete smoke;
	player = new Player;
	bullet = new Bullet;
	rescued = new Rescued;
	map = new Map;
	fire = new Fire;
	goal = new Goal;
	ene = new Enemy;
	particle = new Particle;
	stageSelect = new StageSelect;
	gameover = new Gameover;
	tutorial = new Tutorial;
	damParticle = new DamParticle;
	smoke = new Smoke;
}

void Scene::restart() {
	delete bullet;
	delete rescued;
	delete fire;
	delete goal;
	delete ene;
	delete particle;
	delete gameover;
	delete tutorial;
	delete damParticle;
	delete smoke;
	bullet = new Bullet;
	rescued = new Rescued;
	fire = new Fire;
	goal = new Goal;
	ene = new Enemy;
	particle = new Particle;
	stageSelect = new StageSelect;
	gameover = new Gameover;
	tutorial = new Tutorial;
	damParticle = new DamParticle;
	smoke = new Smoke;
	fire->SetFire(map->map);
	player->Spawn(map->map);
	rescued->Spawn(map->map);
	player->scroll = 0;
	player->water = player->WATER_CONST;
	player->hp = 3;
}


void Scene::Draw() {


	switch (player->scene) {
		case MAIN_TITLE:
			DrawFormatString(640, 450, GetColor(255, 255, 255), "B to Start");
			DrawBox(x - 640, y - 480, x + 640, y + 480, GetColor(200, 200, 200), true);
			for (int i = 0; i < 14; i++) {
				DrawLine(0, y - 420 + (i * 60), 1280, y - 420 + (i * 60), GetColor(128, 128, 128), 8);
			}
			DrawLine(0, y + 464, 1280, y + 464, GetColor(72, 72, 72), 32);
			break;

		case STAGE_SELECT:
			stageSelect->DrawStageSelect();
			DrawBox(x - 640, y - 480, x + 640, y + 480, GetColor(200, 200, 200), true);
			for (int i = 0; i < 14; i++) {
				DrawLine(0, y - 420 + (i * 60), 1280, y - 420 + (i * 60), GetColor(128, 128, 128), 8);
			}
			DrawLine(0, y + 464, 1280, y + 464, GetColor(72, 72, 72), 32);
			break;

		case GAMEOVER:
		case MAIN_GAME:
			pause->Draw();
		case PAUSE:
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			// 描画処理
			goal->Draw(rescued, player->scroll);
			/*fire->DrawFire(player->scroll);*/
			map->DrawMap(map->map, player->scroll);
			rescued->Draw(player->scroll);
			player->bullet->DrawBullet(player->scroll);
			player->DrawPlayer(rescued->isRescued);
			particle->Draw(player->scroll);
			tutorial->DrawTutorial(stageSelect->select, player->scroll, rescued->isRescued);
			player->DrawWater();
			if (player->scene == GAMEOVER) {
				gameover->DrawGameover();
				damParticle->Draw(player->player.transform.x, player->player.transform.y, player->scroll);
			}
			pause->Draw();
			//デバッグ
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			player->DrawHp();
			DrawFormatString(0, 0, GetColor(0, 0, 0), "%d",tutorial->step);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			smoke->Draw();
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
	}
	goal->Efect();
}