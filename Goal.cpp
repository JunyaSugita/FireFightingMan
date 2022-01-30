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
		efectX[i] = 3380 + rand() % 101 - 50;
		isMove[i] = false;
		randNum[i] = 0;
	}
	time = 0;
}

//デストラクタ
Goal::~Goal() {
	delete player;
	delete rescued;
	delete fire;
}


///-----クラス関数-----///
void Goal::GetGoal(Player* player, Rescued* rescued, int& hp, Fire* fire) {
	if (rescued->isRescued == true) {
		if (player->player.transform.x + player->player.r > x - 96 && x > player->player.transform.x - player->player.r) {
			if (player->player.transform.y + player->player.r > 912 - 96 && 912 > player->player.transform.y - player->player.r) {
				if (isGoal == false) {
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
	if (isGoal == true) {
		time++;
		if (time == 30) {
			player->scene = 0;
			Reset(rescued, hp);
			fire->DeleteFire();
		}
	}
}

void Goal::Draw(Rescued* rescued, int scroll) {
	if (rescued->isRescued == true) {
		if (isGoal == false) {
			DrawBox(x - 96 - scroll, 812, x - scroll, 912, GetColor(255, 255, 0), false);
		}
		else {
			DrawBox(x - 96 - scroll, 812, x - scroll, 912, GetColor(255, 255, 0), true);
		}
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
			efectX[i] -= 64;
		}
		
		if (efectX[i] < 0) {
			isMove[i] = false;
		}
	}

	for (int i = 0; i < 10; i++) {
		DrawBox(efectX[i] - 2000, 0 + (i * 120), efectX[i], 120 + (i * 120), GetColor(200 + randNum[i], 200 + randNum[i], 64), true);
		DrawBox(efectX[i] - 2000, 0 + (i * 120), efectX[i], 120 + (i * 120), GetColor(64, 64, 64), false);
	}
}