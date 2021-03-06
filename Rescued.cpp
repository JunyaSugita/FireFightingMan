#include "Rescued.h"

//コンストラクタ
Rescued::Rescued() {
	transform = {
		2300,
		300
	};
	r = 20;
	isRescued = false;

	LoadDivGraph("resource/syoubousi_kyujo.png",5,5,1,64,64, rescueGraph,true);

	player = new Player;
	cx = 0;
	for (int i = 0; i < 2; i++) {
		cy[i] = 0;
	}
	cr = 36;
	time = 0;
	rescueAniTime = 0;
	alpha = 255;
	catchGraph = LoadGraph("resource/catch.png");
	map = new Map;

	rescueSE = LoadSoundMem("sound/rescue.ogg");

	ChangeVolumeSoundMem(180, rescueSE);
}

//デストラクタ
Rescued::~Rescued() {
	delete player;
}

///-----クラス関数-----///

//救助者のスポーン
void Rescued::Spawn(int mapChip[][50]) {
	for (int y = 0; y < map->mapCountY; y++) {
		for (int x = 0; x < map->mapCountX; x++) {
			if (mapChip[y][x] == WOMAN_SPAWN) {
				transform.x = x * map->BLOCK_SIZE;
				transform.y = y * map->BLOCK_SIZE + 20;
				break;
			}
		}
	}
}

//当たり判定
void Rescued::RescuedCollision(Player* player,int &hp,int scene) {
	if (isRescued == false) {
		if (transform.x + r > player->player.transform.x - player->player.r && player->player.transform.x + player->player.r > transform.x - r) {
			if (transform.y + r > player->player.transform.y - player->player.r && player->player.transform.y + player->player.r > transform.y - r) {
				isRescued = true;
				hp = 1;
				cx = player->player.transform.x;
				for (int i = 0; i < 2; i++) {
					cy[i] = player->player.transform.y;
				}
				if (scene == TUTORIAL) {
					hp = 3;
				}
				player->speed = 0.8f;

				PlaySoundMem(rescueSE, DX_PLAYTYPE_BACK, true);
			}
		}
	}
}

//移動関数
void Rescued::Move(Player* player) {
	if (isRescued == true) {
		transform.x = player->player.transform.x;
		transform.y = player->player.transform.y - 25;
	}
	if (isRescued == false) {
		rescueAniTime++;
		if (40 <= rescueAniTime) {
			rescueAniTime = 0;
		}
	}
}

//描画関数
void Rescued::Draw(int scroll,int way) {
	//DrawBox(transform.x - r - scroll, transform.y - r, transform.x + r - scroll, transform.y + r, GetColor(0, 255, 255), true);7
	if (isRescued == false) {
		if (0 <= rescueAniTime && rescueAniTime <= 10) {
			DrawRotaGraph(15 + transform.x - 2 - scroll, transform.y + 5, 0.8, 0.0, rescueGraph[0], 1, 0, 0);
		}
		if (11 <= rescueAniTime && rescueAniTime <= 20) {
			DrawRotaGraph(15 + transform.x - 2 - scroll, transform.y + 5, 0.8, 0.0, rescueGraph[1], 1, 0, 0);
		}
		if (21 <= rescueAniTime && rescueAniTime <= 30) {
			DrawRotaGraph(15 + transform.x - 2 - scroll, transform.y + 5, 0.8, 0.0, rescueGraph[2], 1, 0, 0);
		}
		if (31 <= rescueAniTime && rescueAniTime <= 40) {
			DrawRotaGraph(15 + transform.x - 2 - scroll, transform.y + 5, 0.8, 0.0, rescueGraph[3], 1, 0, 0);
		}
	}
	if (isRescued == true) {
		SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
		if (cr > 0) {
			for (int i = 0; i < 15; i++) {
				DrawCircle(cx - scroll, cy[0], cr + (i * 1), GetColor(255, 255, 96), false);
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (way == 0) {
			DrawRotaGraph(15 + transform.x - 20 - scroll, transform.y + 5, 0.8, 0.0, rescueGraph[4], 1, 1, 0);
		}
		if (way == 1) {
			DrawRotaGraph(15 + transform.x - 2 - scroll, transform.y + 5, 0.8, 0.0, rescueGraph[4], 1, 0, 0);
		}
		

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraph2(cx -scroll - 128, cy[1] - 32,0,0,1.2,0, catchGraph, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//リセット関数
void Rescued::Reset() {
	transform.x = 2300;
	transform.y = 300;
	cr = 36;
	time = 0;
	rescueAniTime = 0;
	alpha = 255;
	isRescued = false;
}

void Rescued::CatchRescued() {
	if (isRescued == true) {
		time++;
		if (time < 6) {
			cr -= 4;
			cy[1] -= 30 * 0.6;
		}
		else {
			cr -= 2;
			if (alpha > 0) {
				alpha -= 16;
				cy[1] -= 1;
			}
		}
	}
}