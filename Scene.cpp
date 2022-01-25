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

	x = 640;
	y = -480;
	isPush = 0;
	time = 0;
	isChange = 0;
}

//コンストラクタ
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
			stageSelect->Select(padInput.Y,pad);
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
					fire->SetFire(map->map);
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
			fire->FireFighting(player->bullet->bullet);

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
			ene->Update(player->bullet->bullet, map);

			//スクロール
			player->GetScroll();

			for (int i = 0; i < 100; i++) {
				player->PlayerDamage(fire->fire[i].transform.x, fire->fire[i].transform.y, fire->fire[i].Xr, fire->fire[i].isFire);
				particle->Emit(fire->fire[i].transform.x, fire->fire[i].transform.y, fire->fire[i].Xr, fire->fire[i].isFire);
			}
			player->DamageCount();
			particle->Move();

			break;

		case GAMEOVER:
			gameover->GotoTitle(pad, rescued, player, fire, goal, particle);

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
			// 描画処理
			goal->Draw(rescued, player->scroll);
			/*fire->DrawFire(player->scroll);*/
			map->DrawMap(map->map, player->scroll);
			rescued->Draw(player->scroll);
			player->bullet->DrawBullet(player->scroll);
			player->DrawPlayer();
			ene->Draw(player->scroll);
			particle->Draw(player->scroll);
			tutorial->DrawTutorial(stageSelect->select, player->scroll,rescued->isRescued);
			player->DrawWater();
			if (player->scene == GAMEOVER) {
				gameover->DrawGameover();
				damParticle->Draw(player->player.transform.x, player->player.transform.y, player->scroll);
			}

			//デバッグ
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			player->DrawHp();
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
	}
}