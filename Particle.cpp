#include"Particle.h"
#include "stdlib.h"
#include "time.h"

//コンストラクタ
Particle::Particle() {
	srand(time(NULL));
	for (int i = 0; i < PARTICLE_CONST; i++) {
		particle[i] = {
			{
				0,
				0
			},
			16,
			0,
			-6,
			0,
			0,
			0
		};
		centerX = 800;
		centerY = 890;
	}
	fire = new Fire;
	player = new Player;
}

//デストラクタ
Particle::~Particle() {
	delete fire;
	delete player;
}

void Particle::Emit(int x, int y, int fireR,int isFire) {
	if (isFire == true) {
		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < PARTICLE_CONST; i++) {
				if (particle[i].isEmit == 0) {
					particle[i].isEmit = 1;
					particle[i].transform.x = x + rand() % 31 - 15;
					particle[i].transform.y = y + rand() % 21 - 10;
					particle[i].r = fireR / 5 * 3;
					break;
				}
			}
		}
	}
}

//移動
void Particle::Move() {

	for (int i = 0; i < PARTICLE_CONST; i++) {
		if (particle[i].isEmit == 1) {
			particle[i].speedX = rand() % 5 - 2;

			particle[i].transform.y += particle[i].speedY;
			particle[i].transform.x += particle[i].speedX;
			particle[i].timer++;
			if (particle[i].timer == 1) {
				particle[i].alpha -= 32;
				particle[i].r--;
				particle[i].timer = 0;
			}
		}
		//画面外もしくは見えなくなったら消す
		if (particle[i].transform.y < 0 || particle[i].r <= 0) {
			particle[i].isEmit = 0;
			particle[i].transform.x = 0;
			particle[i].transform.y = 0;
			particle[i].r = 16;
			particle[i].alpha = 255;
			particle[i].timer = 0;
		}
	}

}

void Particle::DeleteParticle() {
	for (int i = 0; i < PARTICLE_CONST; i++) {
		particle[i].isEmit = 0;
		particle[i].r = 0;
	}
}

//描画
void Particle::Draw(int scroll) {
	for (int i = 0; i < PARTICLE_CONST; i++) {
		if (particle[i].isEmit == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, particle[i].alpha);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 196);
			DrawCircle(particle[i].transform.x - scroll, particle[i].transform.y, particle[i].r, GetColor(72, 8, 2), true);
			DrawCircle(particle[i].transform.x - scroll, particle[i].transform.y, particle[i].r - 2, GetColor(0, 32, 12), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}