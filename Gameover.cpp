#include "Gameover.h"

Gameover::Gameover(){
	dieSE = LoadSoundMem("sound/die.mp3");
	gameoverBGM = LoadSoundMem("sound/gameover.ogg");

	ChangeVolumeSoundMem(120, gameoverBGM);
}

Gameover::~Gameover(){}

void Gameover::GotoGameover(int& scene, int& hp) {
	if (hp == 0) {
		scene = GAMEOVER;
		if (CheckSoundMem(dieSE) == false) {
			PlaySoundMem(dieSE, DX_PLAYTYPE_BACK, true);
		}
		if (CheckSoundMem(gameoverBGM) == false) {
			PlaySoundMem(gameoverBGM, DX_PLAYTYPE_BACK, true);
		}
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