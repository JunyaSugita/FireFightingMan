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

	for (int i = 0; i < 10; i++) {
		x[i] = 100 * i;
		y[i] = 896;
	}
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
		case 0:
			if (pad & PAD_INPUT_2) {
				player->scene = 1;
				//マップ選択
				map->SelectMap1();
				fire->SetFire(map->map);
			}
			break;

			//ゲーム
		case 1:
			//プレイヤー位置の保存
			player->SaveOldPlayer();

			//プレイヤーのジャンプの可否
			player->GetPlayerBottom(map->BLOCK_SIZE);
			player->ResetIsJump(map->map);

			//プレイヤーの移動
			player->PlayerMove(padInput.X, padInput.Rx, padInput.Ry);
			player->PlayerJump(pad);
			

			//弾の発射
			player->PlayerShot(padInput.Rx, padInput.Ry);

			//弾の挙動
			player->bullet->BulletMove(player->G);

			//消化
			fire->FireFighting(player->bullet->bullet);

			//マップチップ上の座標位置の取得
			player->GetOldPlayer(map->BLOCK_SIZE);
			player->GetPlayer(map->BLOCK_SIZE);
			player->bullet->GetBullet(map->BLOCK_SIZE);

			player->ResetIsJump(map->map);

			//当たり判定
			player->BlockCollision(map->map);
			player->bullet->BlockCollision(map->map);
			rescued->RescuedCollision(player);
			goal->GetGoal(player, rescued);

			//プレイヤーが地面で浮かないように
			player->GetPlayerBottom(map->BLOCK_SIZE);
			player->DownPlayer(map->map, map->BLOCK_SIZE);
			rescued->Move(player);


			//敵の出現
			ene->Update(player->bullet->bullet,map);

			//スクロール
			player->GetScroll();

			for (int i = 0; i < 10; i++) {
				particle->Emit(fire->fire[i].transform.x,fire->fire[i].transform.y,fire->fire[i].Xr);
			}

			particle->Move();

			break;
	}
}

void Scene::Draw() {

	switch (player->scene) {
		case 0:
			DrawFormatString(640, 450, GetColor(255, 255, 255), "B to Start");
			break;

		case 1:
			// 描画処理
			goal->Draw(rescued, player->scroll);
			map->DrawMap(map->map, player->scroll);
			rescued->Draw(player->scroll);
			player->bullet->DrawBullet(player->scroll);
			player->DrawPlayer();
			ene->Draw(player->scroll);
			particle->Draw(player->scroll);

			//デバッグ
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
			DrawBox(0, 0, 500, 100, GetColor(255, 255, 255), true);
			DrawFormatString(0, 0, GetColor(50, 50, 50), "X:%d Y:%d Z:%d",
				padInput.X, padInput.Y, padInput.Z);
			DrawFormatString(0, 16, GetColor(50, 50, 50), "Rx:%d Ry:%d Rz:%d",
				padInput.Rx, padInput.Ry, padInput.Rz);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
	}
}