#include "Gameover.h"

Gameover::Gameover(){}

Gameover::~Gameover(){}

void Gameover::GotoGameover(int& scene, int& hp) {
	if (hp == 0) {
		scene = GAMEOVER;
	}
}

void Gameover::GotoTitle(int pad, Rescued* rescued, Player* player, Fire* fire, Goal* goal,Particle* particle) {
	if (pad & PAD_INPUT_2) {
		player->scene = MAIN_TITLE;
		goal->Reset(rescued, player->hp);
		player->player.transform.x = 100;
		player->player.transform.y = 800;
		player->scroll = 0;
		player->isDamageTimer = 0;
		fire->DeleteFire();
		particle->DeleteParticle();
		player->bullet->DeleteBullet();
	}
}

void Gameover::DrawGameover() {
	DrawFormatString(200, 200, GetColor(200, 0, 0), "ゲームオーバー Bでタイトルへ");
}