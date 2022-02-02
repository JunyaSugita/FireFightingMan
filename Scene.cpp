#include "Scene.h"
#include "Dxlib.h"

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
	clear = new Clear;
	charcoal = new Charcoal;

	x = 640;
	y = -480;
	isPush = 0;
	time = 0;
	isChange = 0;
	isClear = 0;

	for (int i = 0; i < 20; i++) {
		whiteX[i] = 1480 + (i * 128);
		if (i < 10) {
			whiteY[i] = 280 + rand() % 51 - 25;
		}
		else if (i >= 10) {
			whiteY[i] = 680 + rand() % 51 - 25;
		}
	}
	isOpen = 0;
	textX = 1480;

	vignette = LoadGraph("resource/vignette.png");
	titleGraph = LoadGraph("resource/title.png");
	backWall[0] = LoadGraph("resource/BackWall_0.png");
	blackGraph = LoadGraph("resource/black.png");
	whiteLine = LoadGraph("resource/whiteLine.png");
	openGraph = LoadGraph("resource/open.png");

	//BGM
	mainBGM = LoadSoundMem("sound/main.mp3");
	titleBGM = LoadSoundMem("sound/title.mp3");
	selectBGM = LoadSoundMem("sound/selectBGM.mp3");
	clearBGM = LoadSoundMem("sound/clear.mp3");

	//SE
	yes = LoadSoundMem("sound/yes.mp3");
	car = LoadSoundMem("sound/car.ogg");

	//音量調整
	ChangeVolumeSoundMem(120, mainBGM);
	ChangeVolumeSoundMem(120, titleBGM);
	ChangeVolumeSoundMem(120, selectBGM);
	ChangeVolumeSoundMem(120, clearBGM);
	ChangeVolumeSoundMem(140, yes);
	ChangeVolumeSoundMem(120, car);
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
	delete clear;
	delete charcoal;
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
			if (CheckSoundMem(mainBGM) == true) {
				StopSoundMem(mainBGM);
			}
			if (CheckSoundMem(selectBGM) == true) {
				StopSoundMem(selectBGM);
			}
			if (CheckSoundMem(clearBGM) == true) {
				StopSoundMem(clearBGM);
			}

			if (CheckSoundMem(titleBGM) == false) {
				PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP, true);
			}

			if (time == 0) {
				if (isPush == 1) {
					isPush = 0;
				}
			}

			if (isClear == 1) {
				y -= 64;
				if (y + 480 < 0) {
					isChange = 0;
					isClear = 0;
					y = -480;
				}
			}


			if (time > 14) {
				if (pad & PAD_INPUT_2) {
					if (isPush == 0) {
						isPush = 1;
						isChange = 1;
						reset();
						PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
					}
				}
			}
			else if (isClear == 0) {
				time++;
			}
			else {}
			damParticle->Reset();
			stageSelect->Reset();

			if (isClear == 0) {
				if (isChange == 1) {
					if (y + 480 < WIN_HEIGHT) {
						y += 64;
					}
					time++;
					if (time == 65) {
						player->scene = 2;
						time = 0;
						isChange = 0;
						PlaySoundMem(car, DX_PLAYTYPE_BACK, true);
					}
				}
			}
			break;

			//ステージセレクト
		case STAGE_SELECT:
			if (CheckSoundMem(titleBGM) == true) {
				StopSoundMem(titleBGM);
			}
			if (CheckSoundMem(selectBGM) == false) {
				PlaySoundMem(selectBGM, DX_PLAYTYPE_LOOP, true);
			}
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
				if (CheckSoundMem(car) == true) {
					StopSoundMem(car);
				}
				if (pad & PAD_INPUT_2) {
					if (isPush == 0) {
						if (isChange == 0) {
							isChange = 1;
							stageSelect->time = 0;
							stageSelect->Move();
							PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
						}
					}
				}
				else {
					isPush = 0;
				}
			}

			if (isChange == 1) {
				if (CheckSoundMem(car) == false) {
					PlaySoundMem(car, DX_PLAYTYPE_BACK, true);
				}
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
					if (CheckSoundMem(selectBGM) == true) {
						StopSoundMem(selectBGM);
					}
				}
			}

			break;
			//ゲーム
		case MAIN_GAME:
			if (CheckSoundMem(car) == true) {
				StopSoundMem(car);
			}
			if (CheckSoundMem(mainBGM) == false) {
				PlaySoundMem(mainBGM, DX_PLAYTYPE_LOOP, true);
			}

		
			//開幕演出
			if (isOpen == 0) {
				openTime++;
				for (int i = 0; i < 20; i++) {
					whiteX[i] -= 96;
					if (whiteX[i] + 200 < 0) {
						whiteX[i] = 1480;
					}
				}

				if (openTime < 12) {
					textX -= 64;
				}
				else if (openTime > 12 && openTime < 66) {
					textX -= 3;
				}
				else {
					textX -= 72;
				}

				if (textX + 240 < 0) {
					isOpen = 1;
					textX = 1480;
					openTime = 0;
				}
			}
			else {
				//プレイヤー位置の保存
				player->SaveOldPlayer();

				//プレイヤーのジャンプの可否
				player->GetPlayerBottom(map->BLOCK_SIZE);

				//プレイヤーの移動
				player->Dash(pad, rescued->isRescued, padInput.Rx, padInput.Ry);
				player->PlayerJump(pad, rescued->isRescued, map->map);
				player->PlayerMove(padInput.X, padInput.Rx, padInput.Ry, rescued->isRescued);
				player->CheckStick(padInput.Ry, rescued->isRescued);

				//弾の発射
				player->PlayerShot(padInput.Rx, padInput.Ry, rescued->isRescued, stageSelect->select);

				//弾の挙動
				player->bullet->BulletMove(player->G, padInput.X, padInput.Y);

				//消化
				fire->FireFighting(player->bullet->bullet, smoke, map->map);

				//マップチップ上の座標位置の取得
				player->GetOldPlayer(map->BLOCK_SIZE);
				player->GetPlayer(map->BLOCK_SIZE);
				player->bullet->GetBullet(map->BLOCK_SIZE);

				//当たり判定
				player->BlockCollision(map->map,charcoal->isBrocken);
				player->bullet->BlockCollision(map->map);
				rescued->RescuedCollision(player, player->hp, stageSelect->select);
				goal->GetGoal(player, rescued, player->hp, fire, stageSelect->select);
				gameover->GotoGameover(player->scene, player->hp);
				//プレイヤーが地面で浮かないように
				player->GetPlayer(map->BLOCK_SIZE);
				player->GetPlayerBottom(map->BLOCK_SIZE);
				player->CheckStick(padInput.Ry, rescued->isRescued);
				player->DownPlayer(map->map, map->BLOCK_SIZE);
				rescued->Move(player);
				rescued->CatchRescued();

				//ブロックが破壊されるように
				charcoal->BrockenChar(map->map);

				//敵の出現
				ene->Update(player->bullet->bullet, map->map);
				for (int i = 0; i < fire->FIRE_CONST; i++) {
					ene->FireColision(fire->fire[i].transform.x, fire->fire[i].transform.y, fire->fire[i].Xr, fire->fire[i].Yr, fire->fire[i].isFire);
				}
				//スクロール
				player->GetScroll(stageSelect->select);

				for (int i = 0; i < 100; i++) {
					player->PlayerDamage(fire->fire[i].transform.x, fire->fire[i].transform.y, fire->fire[i].Xr, fire->fire[i].isFire, rescued->isRescued, stageSelect->select);
					particle->Emit(fire->fire[i].transform.x, fire->fire[i].transform.y, fire->fire[i].Xr, fire->fire[i].isFire);
				}
				for (int i = 0; i < 10; i++) {
					player->PlayerDamage(ene->enemy[i].transform.x, ene->enemy[i].transform.y + ene->enemy[i].hp / 4, ene->enemy[i].hp / 4, ene->enemy[i].hp, rescued->isRescued, stageSelect->select);
					particle->Emit(ene->enemy[i].transform.x, ene->enemy[i].transform.y + ene->enemy[i].hp / 4, ene->enemy[i].hp / 4, 1);
				}
				player->DamageCount();
				particle->Move();

				smoke->Move();

				pause->ChangePause(pad, player->scene);
				pause->Move();


				//////////ここからチュートリアル記述//////////
				if (stageSelect->select == TUTORIAL) {
					//ダッシュ
					if (tutorial->isCom[0] == 0) {
						if (tutorial->step == 0) {
							player->scene = TEXT;
							tutorial->textNum = 1;
						}
					}

					//ジャンプ
					if (tutorial->isCom[1] == 0) {
						if (player->player.transform.x > 400) {
							player->scene = TEXT;
							tutorial->textNum = 2;
						}
					}

					//水
					if (tutorial->isCom[2] == 0) {
						if (player->player.transform.x > 778) {
							player->scene = TEXT;
							tutorial->textNum = 3;
						}
					}

					//火消
					if (tutorial->isCom[3] == 0) {
						if (player->player.transform.x > 1018) {
							player->scene = TEXT;
							tutorial->textNum = 4;
						}
					}

					//ブロック
					if (tutorial->isCom[4] == 0) {
						if (player->player.transform.x > 1278) {
							player->scene = TEXT;
							tutorial->textNum = 5;
						}
					}

					//救出後
					if (tutorial->isCom[5] == 0) {
						if (rescued->isRescued == 1) {
							player->scene = TEXT;
							tutorial->textNum = 6;
						}
					}
				}

				if (isLost == 0) {
					if (player->water == 0) {
						player->scene = TEXT;
						isLost = 1;
					}
				}

			}
			break;

		case GAMEOVER:
			gameover->GotoTitle(pad, rescued, player, fire, goal, particle);
			if (CheckSoundMem(mainBGM) == true) {
				StopSoundMem(mainBGM);
			}
			if (CheckSoundMem(player->walkSE) == true) {
				StopSoundMem(player->walkSE);
			}
			if (CheckSoundMem(player->dashSE) == true) {
				StopSoundMem(player->dashSE);
			}
			if (CheckSoundMem(player->jumpSE) == true) {
				StopSoundMem(player->jumpSE);
			}
			if (CheckSoundMem(player->waterSE) == true) {
				StopSoundMem(player->waterSE);
			}

			break;

		case PAUSE:
			pause->ChangeScene(pad, player->scene);
			pause->Move();

			//選択
			if (padInput.Y < 0 || pad & PAD_INPUT_UP) {
				if (pause->isReset == 0) {
					if (isPush == 0) {
						pause->isReset = 1;
						PlaySoundMem(stageSelect->selectSE, DX_PLAYTYPE_BACK, true);
						isPush = 1;
					}
				}
			}
			else if (padInput.Y > 0 || pad & PAD_INPUT_DOWN) {
				if (pause->isReset == 1) {
					if (isPush == 0) {
						pause->isReset = 0;
						PlaySoundMem(stageSelect->selectSE, DX_PLAYTYPE_BACK, true);
						isPush = 1;
					}
				}
			}
			else {
				isPush = 0;
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
						PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
						if (CheckSoundMem(mainBGM) == true) {
							StopSoundMem(mainBGM);
						}
					}
					//タイトルへ
					else if (pause->isReset == 0) {
						isPush = true;
						reset();
						pause->isPause = false;
						pause->xr = 0;
						pause->yr = 0;
						PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
					}
				}
			}
			else {
				isPush = false;
			}

			break;

		case CLEAR:
			if (CheckSoundMem(mainBGM) == true) {
				StopSoundMem(mainBGM);
			}

			if (CheckSoundMem(titleBGM) == false) {
				PlaySoundMem(titleBGM, DX_PLAYTYPE_LOOP, true);
			}


			//選択
			if (padInput.Y < 0 || pad & PAD_INPUT_UP) {
				if (clear->isNext == 0) {
					if (isPush == 0) {
						clear->isNext = 1;
						PlaySoundMem(stageSelect->selectSE, DX_PLAYTYPE_BACK, true);
						isPush = 1;
					}
				}
			}
			else if (padInput.Y > 0 || pad & PAD_INPUT_DOWN) {
				if (clear->isNext == 1) {
					if (isPush == 0) {
						clear->isNext = 0;
						PlaySoundMem(stageSelect->selectSE, DX_PLAYTYPE_BACK, true);
						isPush = 1;
					}
				}
			}
			else {
				isPush = 0;
			}

			//ステージ選択orタイトル
			if (pad & PAD_INPUT_2) {
				//ステージ
				if (clear->isPush == false) {
					if (clear->isNext == 1) {
						clear->isPush = true;
						PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
						if (CheckSoundMem(mainBGM) == true) {
							StopSoundMem(mainBGM);
						}
						isChange = 1;
						time = 0;
					}
					//タイトルへ
					else if (clear->isNext == 0) {
						if (clear->isPush == false) {
							clear->isPush = true;
							PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
							isChange = 1;
							time = 0;
							isLost = 0;
						}
					}
				}
			}
			else {
				clear->isPush = false;
			}

			if (isChange == 1) {
				if (y + 480 < WIN_HEIGHT) {
					y += 64;
				}
				time++;
				if (time == 50) {
					reset();
					if (clear->isNext == 1) {
						delete stageSelect;
						player->scene = STAGE_SELECT;
						stageSelect = new StageSelect;
						PlaySoundMem(car, DX_PLAYTYPE_BACK, true);
					}
					else {
						player->scene = 0;
						isClear = 1;
					}
					time = 0;
					isChange = 0;
				}
			}
			break;



		case TEXT://チュートリアル
			pause->ChangePause(pad, player->scene);
			pause->Move();

			if (CheckSoundMem(player->walkSE) == 1) {
				StopSoundMem(player->walkSE);
			}
			if (CheckSoundMem(player->dashSE) == 1) {
				StopSoundMem(player->dashSE);
			}


			if (isLost == 1) {
				if (tutorial->lostNum == 0) {
					if (pad & PAD_INPUT_2) {
						if (isPush == 0) {
							isPush = 1;
							tutorial->lostNum = 1;
							PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
						}
					}
					else {
						isPush = 0;
					}
				}
				else if (tutorial->lostNum == 1) {
					if (pad & PAD_INPUT_2) {
						if (isPush == 0) {
							isPush = 1;
							player->scene = 1;
							isLost = 2;
							PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
						}
					}
					else {
						isPush = 0;
					}
				}
			}
			else {
				if (tutorial->textNum == 1) {
					if (pad & PAD_INPUT_2) {
						if (isPush == 0) {
							isPush = 1;
							player->scene = 1;
							tutorial->isCom[0] = 1;
							PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
						}
					}
					else {
						isPush = 0;
					}
				}
				else if (tutorial->textNum == 2) {
					if (pad & PAD_INPUT_2) {
						if (isPush == 0) {
							isPush = 1;
							player->scene = 1;
							tutorial->isCom[1] = 1;
							PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
						}
					}
					else {
						isPush = 0;
					}
				}
				else if (tutorial->textNum == 3) {
					if (tutorial->exNum[0] == 0) {
						if (pad & PAD_INPUT_2) {
							if (isPush == 0) {
								isPush = 1;
								tutorial->exNum[0] = 1;
								PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
							}
						}
						else {
							isPush = 0;
						}
					}
					if (tutorial->exNum[0] == 1) {
						if (pad & PAD_INPUT_2) {
							if (isPush == 0) {
								isPush = 1;
								player->scene = 1;
								tutorial->isCom[2] = 1;
								PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
							}
						}
						else {
							isPush = 0;
						}
					}
				}
				else if (tutorial->textNum == 4) {
					if (tutorial->exNum[1] == 0) {
						if (pad & PAD_INPUT_2) {
							if (isPush == 0) {
								isPush = 1;
								tutorial->exNum[1] = 1;
								PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
							}
						}
						else {
							isPush = 0;
						}
					}
					if (tutorial->exNum[1] == 1) {
						if (pad & PAD_INPUT_2) {
							if (isPush == 0) {
								isPush = 1;
								tutorial->exNum[1] = 1;
								tutorial->isCom[3] = 1;
								player->scene = 1;
								PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
							}
						}
						else {
							isPush = 0;
						}
					}
				}
				else if (tutorial->textNum == 5) {
					if (tutorial->exNum[2] == 0) {
						if (pad & PAD_INPUT_2) {
							if (isPush == 0) {
								isPush = 1;
								tutorial->exNum[2] = 1;
								PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
							}
						}
						else {
							isPush = 0;
						}
					}
					if (tutorial->exNum[2] == 1) {
						if (pad & PAD_INPUT_2) {
							if (isPush == 0) {
								isPush = 1;
								player->scene = 1;
								tutorial->isCom[4] = 1;
								PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
							}
						}
						else {
							isPush = 0;
						}
					}
				}
				else if (tutorial->textNum == 6) {
					if (tutorial->exNum[3] == 0) {
						if (pad & PAD_INPUT_2) {
							if (isPush == 0) {
								isPush = 1;
								tutorial->exNum[3] = 1;
								PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
							}
						}
						else {
							isPush = 0;
						}
					}
					if (tutorial->exNum[3] == 1) {
						if (pad & PAD_INPUT_2) {
							if (isPush == 0) {
								isPush = 1;
								tutorial->exNum[3] = 2;
								PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
							}
						}
						else {
							isPush = 0;
						}
					}
					if (tutorial->exNum[3] == 2) {
						if (pad & PAD_INPUT_2) {
							if (isPush == 0) {
								isPush = 1;
								tutorial->isCom[5] = 1;
								player->scene = 1;
								PlaySoundMem(yes, DX_PLAYTYPE_BACK, true);
							}
						}
						else {
							isPush = 0;
						}
					}
				}
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
	delete charcoal;
	player = new Player;
	bullet = new Bullet;
	rescued = new Rescued;
	map = new Map;
	fire = new Fire;
	goal = new Goal;
	ene = new Enemy;
	particle = new Particle;
	gameover = new Gameover;
	tutorial = new Tutorial;
	damParticle = new DamParticle;
	smoke = new Smoke;
	charcoal = new Charcoal;
	isOpen = 0;
}

void Scene::restart() {
	for (int y = 0; y < map->mapCountY; y++) {
		for (int x = 0; x < map->mapCountX; x++) {
			if (map->map[y][x] == CHARCOAL|| map->map[y][x] == 7) {
				map->map[y][x] = FLAME;
			}
		}
	}
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
	delete charcoal;
	bullet = new Bullet;
	rescued = new Rescued;
	fire = new Fire;
	goal = new Goal;
	ene = new Enemy;
	particle = new Particle;
	gameover = new Gameover;
	tutorial = new Tutorial;
	damParticle = new DamParticle;
	smoke = new Smoke;
	charcoal = new Charcoal;
	fire->SetFire(map->map);
	player->Spawn(map->map);
	rescued->Spawn(map->map);
	ene->Make(map->map);
	player->scroll = 0;
	player->water = player->WATER_CONST;
	player->hp = 3;
	for (int i = 0; i < 5000; i++) {
		player->bullet->bullet[i].isShot = false;
	}
}


void Scene::Draw() {


	switch (player->scene) {
		case MAIN_TITLE:
			DrawGraph(0, 0, titleGraph, true);
			/*DrawFormatString(640, 450, GetColor(255, 255, 255), "B to Start");*/
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
			DrawGraph(0 - player->scroll, 0, backWall[0], true);
			goal->Draw(rescued, player->scroll, stageSelect->select);
			/*fire->DrawFire(player->scroll);*/
			smoke->Draw();
			particle->Draw(player->scroll);
			map->DrawMap(map->map, player->scroll, charcoal->brockenTimer);
			rescued->Draw(player->scroll, player->way);
			player->bullet->DrawBullet(player->scroll);
			player->DrawPlayer(rescued->isRescued);
			if (player->scene == GAMEOVER) {
				gameover->DrawGameover();
				damParticle->Draw(player->player.transform.x, player->player.transform.y, player->scroll);
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144);
			DrawExtendGraph(0, 0, 1280, 960, vignette, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			player->DrawWater();
			pause->Draw();

			if (isOpen == 0) {

				DrawGraph(0, 0, blackGraph, true);

				SetDrawBlendMode(DX_BLENDMODE_ADD, 64);
				for (int j = 0; j < 8; j++) {
					for (int i = 0; i < 20; i++) {
						DrawGraph(whiteX[i], whiteY[i], whiteLine, true);
					}
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				DrawGraph(textX - 280, 450, openGraph, true);
			}

			break;

		case CLEAR:

			clear->Draw();

			DrawBox(x - 640, y - 480, x + 640, y + 480, GetColor(200, 200, 200), true);
			for (int i = 0; i < 14; i++) {
				DrawLine(0, y - 420 + (i * 60), 1280, y - 420 + (i * 60), GetColor(128, 128, 128), 8);
			}
			DrawLine(0, y + 464, 1280, y + 464, GetColor(72, 72, 72), 32);
			break;

		case TEXT://チュートリアル
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			// 描画処理
			DrawGraph(0 - player->scroll, 0, backWall[0], true);
			goal->Draw(rescued, player->scroll, stageSelect->select);
			/*fire->DrawFire(player->scroll);*/
			smoke->Draw();
			particle->Draw(player->scroll);
			map->DrawMap(map->map, player->scroll,charcoal->brockenTimer);
			rescued->Draw(player->scroll, player->way);
			player->bullet->DrawBullet(player->scroll);
			player->DrawPlayer(rescued->isRescued);
			if (player->scene == GAMEOVER) {
				gameover->DrawGameover();
				damParticle->Draw(player->player.transform.x, player->player.transform.y, player->scroll);
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144);
			DrawExtendGraph(0, 0, 1280, 960, vignette, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			player->DrawWater();
			pause->Draw();

			//////////////ここからチュートリアル描画/////////////

			DrawGraph(0, 0, blackGraph, true);

			tutorial->DrawTutorial(stageSelect->select, player->scroll, rescued->isRescued, isLost);
			if (tutorial->textNum == 3) {
				if (player->water > 0) {
					DrawBox(100, 920, 100 + player->water, 950, GetColor(0, 160, 200), true);
				}
				DrawGraph(75, 920, player->waterTank, true);
			}

			break;
	}
	goal->Efect();
}