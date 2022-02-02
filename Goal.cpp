#include "Goal.h"
#include "time.h"
#include "stdlib.h"

//コンストラクタ
Goal::Goal() {
	player = new Player;
	rescued = new Rescued;
	fire = new Fire;
	isGoal = false;
	isShow = false;
	x = 144;
	for (int i = 0; i < 10; i++) {
		efectX[i] = -2380 + rand() % 101 - 50;
		isMove[i] = false;
		randNum[i] = 0;
	}
	time = 0;

	goalSE = LoadSoundMem("sound/goal.mp3");

	ChangeVolumeSoundMem(120, goalSE);

	LoadDivGraph("resource/goal.png", 2, 2, 1, 96, 96, goalGraph);
}

//デストラクタ
Goal::~Goal() {
	delete player;
	delete rescued;
	delete fire;
}


///-----クラス関数-----///
void Goal::GetGoal_1(Player* player, Rescued* rescued, int& hp, Fire* fire, int select) {
	if (isGoal == false) {
		time++;
		if (time == 30) {
			time = 0;
		}

		if (rescued->isRescued == 1) {
			if (player->player.transform.x + player->player.r > x - 96 && x > player->player.transform.x - player->player.r) {
				if (player->player.transform.y + player->player.r > 912 - 96 && 912 > player->player.transform.y - player->player.r) {
					if (isGoal == false) {
						time = 0;
						PlaySoundMem(goalSE, DX_PLAYTYPE_BACK, true);
						isGoal = true;
						isShow = true;
						for (int i = 0; i < 10; i++) {
							isMove[i] = true;
							randNum[i] = rand() % 51 - 25;
						}
					}
				}
			}
		}
	}

	if (isGoal == true) {
		time++;
		if (time == 30) {
			player->scene = 4;
			Reset(rescued, hp);
			fire->DeleteFire();
		}
	}
}

void Goal::GetGoal_2(Player* player, Rescued* rescued, int& hp, Fire* fire, int select) {
	x = 192;
	if (isGoal == false) {
		time++;
		if (time == 30) {
			time = 0;
		}

		if (rescued->isRescued == 1) {
			if (player->player.transform.x + player->player.r > x - 96 && x > player->player.transform.x - player->player.r) {
				if (player->player.transform.y + player->player.r > 128 - 96 && 128 > player->player.transform.y - player->player.r) {
					if (isGoal == false) {
						time = 0;
						PlaySoundMem(goalSE, DX_PLAYTYPE_BACK, true);
						isGoal = true;
						isShow = true;
						for (int i = 0; i < 10; i++) {
							isMove[i] = true;
							randNum[i] = rand() % 51 - 25;
						}
					}
				}
			}
		}
	}

	if (isGoal == true) {
		time++;
		if (time == 30) {
			player->scene = 4;
			Reset(rescued, hp);
			fire->DeleteFire();
		}
	}
}

void Goal::Draw(Rescued* rescued, int scroll, int select) {
	if (select == 0) {
		if (time < 15) {
			DrawGraph(x - 90 - scroll, 812, goalGraph[0], true);
		}
		else {
			DrawGraph(x - 90 - scroll, 812, goalGraph[1], true);
		}
	}
	else {
		if (time < 15) {
			DrawGraph(x - 90 - scroll, 48, goalGraph[0], true);
		}
		else {
			DrawGraph(x - 90 - scroll, 48, goalGraph[1], true);
		}
	}
	if (rescued->isRescued == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		if (select == 0) {
			if (isGoal == false) {
				DrawBox(x - 96 - scroll, 902, x - scroll, 912, GetColor(255, 255, 0), true);
			}
		}
		if(select > 0) {
			if (isGoal == false) {
				DrawBox(x - 96 - scroll, 128, x - scroll, 148, GetColor(255, 255, 0), true);
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//リセット用
void Goal::Reset(Rescued* rescued, int& hp) {
	rescued->Reset();
	isGoal = false;
	hp = 3;
}

void Goal::Efect() {
	for (int i = 0; i < 10; i++) {
		if (isMove[i] == true) {
			efectX[i] += 64;
		}

		if (efectX[i] > WIN_HEIGHT + 400) {
			isMove[i] = false;
		}
	}

	for (int i = 0; i < 10; i++) {
		DrawBox(efectX[i] + 2000, 0 + (i * 120), efectX[i], 120 + (i * 120), GetColor(200 + randNum[i], 200 + randNum[i], 64), true);
		DrawBox(efectX[i] + 2000, 0 + (i * 120), efectX[i], 120 + (i * 120), GetColor(64, 64, 64), false);
	}

}