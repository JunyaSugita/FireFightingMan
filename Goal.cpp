#include "Goal.h"

//コンストラクタ
Goal::Goal() {
	player = new Player;
	rescued = new Rescued;
	isGoal = false;
	x = 144;
}

//デストラクタ
Goal::~Goal() {
	delete player;
	delete rescued;
}


///-----クラス関数-----///
void Goal::GetGoal(Player* player, Rescued* rescued, int& hp) {
	if (rescued->isRescued == true) {
		if (player->player.transform.x + player->player.r > x - 96 && x > player->player.transform.x - player->player.r) {
			if (player->player.transform.y + player->player.r > 912 - 96 && 912 > player->player.transform.y - player->player.r) {
				if (isGoal == false) {
					isGoal = true;
					player->scene = 0;
					Reset(rescued, hp);
				}
			}
		}
	}
}

void Goal::Gameover(int& scene, Rescued* rescued, int& hp, Player* player) {
	if (hp == 0) {
		scene = 0;
		Reset(rescued, hp);
		player->player.transform.x = 100;
		player->player.transform.y = 800;
		player->scroll = 0;
		player->isDamageTimer = 0;
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