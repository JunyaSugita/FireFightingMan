#include "Player.h"

Player::Player() {
	player = {
		{
			100,
			800
		},
		20,
		0,
		0.0f
	};

	oldPlayer = {
		0,
		0
	};

	hp = 3;
	isDamage = 0;
	isDamageTimer = 0;

	speed = 1.0f;

	inertia = 0;
	inertiaSpeed = 0;

	isButton = 0;

	isShow = 0;

	water = WATER_CONST;

	//左上の座標
	leftTopX = 0;
	leftTopY = 0;
	//左下の座標
	leftBottomX = 0;
	leftBottomY = 0;
	//右下の座標
	rightTopX = 0;
	rightTopY = 0;
	//右下の座標
	rightBottomX = 0;
	rightBottomY = 0;
	//1フレーム前の左上の座標
	oldLeftTopX = 0;
	oldLeftTopY = 0;
	//1フレーム前の右上の座標
	oldRightTopX = 0;
	oldRightTopY = 0;
	//1フレーム前の左下の座標
	oldLeftBottomX = 0;
	oldLeftBottomY = 0;
	//1フレーム前の右下の座標
	oldRightBottomX = 0;
	oldRightBottomY = 0;

	scroll = 0;

	//グラフ
	graph_h = LoadGraph("resource/syoubousi_1.png");
	graph_h2 = LoadGraph("resource/syoubousi_2.png");
	waterTank = LoadGraph("resource/waterTank3.png");

	bullet = new Bullet;
	map = new Map;

	//SE
	damageSE = LoadSoundMem("sound/damage.mp3");
	waterSE = LoadSoundMem("sound/water.mp3");
	walkSE = LoadSoundMem("sound/walk.ogg");
	startSE = LoadSoundMem("sound/start.mp3");
	jumpSE = LoadSoundMem("sound/jump.wav");
	dashSE = LoadSoundMem("sound/dash.ogg");

	ChangeVolumeSoundMem(150, damageSE);
	ChangeVolumeSoundMem(150, waterSE);
	ChangeVolumeSoundMem(140, walkSE);
	ChangeVolumeSoundMem(200, startSE);
	ChangeVolumeSoundMem(180, jumpSE);
	ChangeVolumeSoundMem(140, dashSE);
}

Player::~Player() {
	delete bullet;
	delete map;
}

void Player::Spawn(int mapChip[][50]) {
	for (int y = 0; y < map->mapCountY; y++) {
		for (int x = 0; x < map->mapCountX; x++) {
			if (mapChip[y][x] == PLAYER_SPAWN) {
				player.transform.x = x * map->BLOCK_SIZE + 28;
				player.transform.y = y * map->BLOCK_SIZE + 28;

				if (CheckSoundMem(startSE) == false) {
					PlaySoundMem(startSE, DX_PLAYTYPE_BACK, true);
				}
				break;
			}
		}
	}
}

void Player::SaveOldPlayer() {
	oldPlayer.x = player.transform.x;
	oldPlayer.y = player.transform.y;
}

void Player::GetPlayerBottom(int BLOCK_SIZE) {
	//左下の座標の取得
	leftBottomX = (player.transform.x - player.r) / BLOCK_SIZE;
	leftBottomY = (player.transform.y + player.r - 1 + 1) / BLOCK_SIZE;
	//右下の座標の取得
	rightBottomX = (player.transform.x + player.r - 1) / BLOCK_SIZE;
	rightBottomY = (player.transform.y + player.r - 1 + 1) / BLOCK_SIZE;
}

void Player::Dash(int pad, int isRescued, int inputX, int inputY) {
	if (player.isJump == false) {
		speed = 0.8f;
	}
	if (isRescued == false) {
		if ((pad & PAD_INPUT_1 || pad & PAD_INPUT_2 || pad & PAD_INPUT_3 || pad & PAD_INPUT_4) && player.isJump == false) {
			speed = 1.5f;
		}
	}
	if (inputY > 0 && isRescued == false && water > 0) {
		speed = 0.8f;
	}
}

void Player::PlayerMove(int LInputX, int RInputX, int RInputY, int isRescued) {
	if (LInputX > 0 || LInputX < 0) {
		player.transform.x += (LInputX / 200) * speed;
		if (((LInputX / 200) * speed) <= 0) {
			way = 1;
		}
		if (((LInputX / 200) * speed) >= 0) {
			way = 0;
		}
		if (player.isJump == false) {
			if (speed == 0.8f) {
				if (CheckSoundMem(walkSE) == false) {
					PlaySoundMem(walkSE, DX_PLAYTYPE_BACK, true);
				}
				if (CheckSoundMem(dashSE) == true) {
					StopSoundMem(dashSE);
				}
			}
			else if (speed == 1.5f) {
				if (CheckSoundMem(dashSE) == false) {
					PlaySoundMem(dashSE, DX_PLAYTYPE_BACK, true);
				}
				if (CheckSoundMem(walkSE) == true) {
					StopSoundMem(walkSE);
				}
			}
		}
		else {
			if (CheckSoundMem(dashSE) == true) {
				StopSoundMem(dashSE);
			}
			if (CheckSoundMem(walkSE) == true) {
				StopSoundMem(walkSE);
			}
		}
	}
	else {
		if (CheckSoundMem(dashSE) == true) {
			StopSoundMem(dashSE);
		}
		if (CheckSoundMem(walkSE) == true) {
			StopSoundMem(walkSE);
		}
	}
	player.transform.y += G - player.jumpPow;

	inertia = 0;
	if (isRescued == false && player.jumpPow <= G && water > 0) {
		if (RInputX != 0 || RInputY != 0) {
			player.transform.x += (RInputX * -1) / 180;
			inertia = (RInputY * -1) / 70;

			if (CheckSoundMem(waterSE) == false) {
				PlaySoundMem(waterSE, DX_PLAYTYPE_BACK, true);
			}
		}
	}

	if (inertia > inertiaSpeed) {
		inertiaSpeed++;
	}
	else if (inertia < inertiaSpeed) {
		if (inertiaSpeed >= -G) {
			inertiaSpeed = -G;
		}
		inertiaSpeed--;
	}
	player.transform.y += inertiaSpeed;
}

void Player::PlayerJump(int pad, int isRescued, int map[][50]) {
	if (map[leftBottomY][leftBottomX] != BLOCK && map[rightBottomY][rightBottomX] != BLOCK && map[leftBottomY][leftBottomX] != CHARCOAL && map[rightBottomY][rightBottomX] != CHARCOAL) {
		player.isJump = true;
	}
	if (pad & PAD_INPUT_5) {
		if (isButton == 0 && player.isJump == false) {
			player.isJump = true;
			isButton = 1;
			if (isRescued == false) {
				player.jumpPow = 24.3;
			}
			else {
				player.jumpPow = 24.3;
			}
			if (CheckSoundMem(jumpSE) == false) {
				PlaySoundMem(jumpSE, DX_PLAYTYPE_BACK, true);
			}
		}
	}
	else {
		isButton = 0;
	}

	if (player.jumpPow > 0) {
		player.jumpPow--;
	}
}

void Player::PlayerShot(int InputX, int InputY, int isRescued, int select) {
	if (isRescued == false && player.jumpPow <= G && water > 0) {
		if (InputX != 0 || InputY != 0) {
			bullet->BulletShot(player.transform, InputX, InputY);
			switch (select) {
				case 0:
					water--;
					break;
				case 1:
					water -= 350 / 50;
					break;
				case 2:
					water -= 350 / 80;
					break;
				case 3:
					water -= 350 / 150;
					break;
			}
		}
	}
}

void Player::PlayerDamage(int fireX, int fireY, int fireR, int isFire, int isRescued, int select) {
	if (isDamage == 0 && isFire >= 1) {
		if (fireX - fireR < player.transform.x + player.r &&
			player.transform.x - player.r < fireX + fireR &&
			fireY - fireR < player.transform.y + player.r &&
			player.transform.y - player.r < fireY + fireR) {
			if (isRescued == 0) {
				water -= 40;
			}
			else {
				hp--;
			}
			isDamage = 1;
			isDamageTimer = 100;
			if (CheckSoundMem(damageSE) == false) {
				PlaySoundMem(damageSE, DX_PLAYTYPE_BACK, true);
			}
		}
	}
}

void Player::DamageCount() {
	if (isDamage == 1) {
		isDamageTimer--;
		if (isDamageTimer <= 0) {
			isDamage = 0;
		}
	}
}

void Player::GetPlayer(int BLOCK_SIZE) {
	//左上の座標の取得
	leftTopX = (player.transform.x - player.r) / BLOCK_SIZE;
	leftTopY = (player.transform.y - player.r) / BLOCK_SIZE;
	//右上の座標の取得
	rightTopX = (player.transform.x + player.r - 1) / BLOCK_SIZE;
	rightTopY = (player.transform.y - player.r) / BLOCK_SIZE;
	//左下の座標の取得
	leftBottomX = (player.transform.x - player.r) / BLOCK_SIZE;
	leftBottomY = (player.transform.y + player.r - 1) / BLOCK_SIZE;
	//右下の座標の取得
	rightBottomX = (player.transform.x + player.r - 1) / BLOCK_SIZE;
	rightBottomY = (player.transform.y + player.r - 1) / BLOCK_SIZE;

	//ジャンプ用の座標を取得
	jumpLeftBottomX = (player.transform.x - player.r) / BLOCK_SIZE;
	jumpLeftBottomY = (player.transform.y + player.r - 1 - 1) / BLOCK_SIZE;
	jumpRightBottomX = (player.transform.x + player.r - 1) / BLOCK_SIZE;
	jumpRightBottomY = (player.transform.y + player.r - 1 - 1) / BLOCK_SIZE;
}

void Player::GetOldPlayer(int BLOCK_SIZE) {
	//1フレーム前の左上の座標の取得
	oldLeftTopX = (oldPlayer.x - player.r) / BLOCK_SIZE;
	oldLeftTopY = (oldPlayer.y - player.r) / BLOCK_SIZE;
	//1フレーム前の右上の座標の取得
	oldRightTopX = (oldPlayer.x + player.r - 1) / BLOCK_SIZE;
	oldRightTopY = (oldPlayer.y - player.r) / BLOCK_SIZE;
	//1フレーム前の左下の座標の取得
	oldLeftBottomX = (oldPlayer.x - player.r) / BLOCK_SIZE;
	oldLeftBottomY = (oldPlayer.y + player.r - 1) / BLOCK_SIZE;
	//1フレーム前の右下の座標の取得
	oldRightBottomX = (oldPlayer.x + player.r - 1) / BLOCK_SIZE;
	oldRightBottomY = (oldPlayer.y + player.r - 1) / BLOCK_SIZE;
}

void Player::GetScroll(int select) {
	if (select == 0) {
		if (player.transform.x >= WIN_WIDTH / 2 && player.transform.x <= WIN_WIDTH - (48 * 4)) {
			scroll = player.transform.x - WIN_WIDTH / 2;
		}
	}
}

void Player::BlockCollision(int map[][50], int isBrocken[][50]) {

	if (player.jumpPow <= G) {
		if (map[leftBottomY][leftBottomX] == BLOCK && map[rightBottomY][rightBottomX] != BLOCK && map[leftTopY][leftTopX] != BLOCK) {
			player.isJump = false;
		}
		if (map[leftBottomY][leftBottomX] != BLOCK && map[rightBottomY][rightBottomX] == BLOCK && map[rightTopY][rightTopX] != BLOCK) {
			player.isJump = false;
		}
		if (map[leftBottomY][leftBottomX] == BLOCK && map[jumpLeftBottomY][jumpLeftBottomX] != BLOCK) {
			player.isJump = false;
		}
		if (map[rightBottomY][rightBottomX] == BLOCK && map[jumpRightBottomY][jumpRightBottomX] != BLOCK) {
			player.isJump = false;
		}
		if (map[leftBottomY][leftBottomX] == BLOCK && map[rightBottomY][rightBottomX] == BLOCK) {
			player.isJump = false;
		}

		if (map[leftBottomY][leftBottomX] == CHARCOAL && map[rightBottomY][rightBottomX] != CHARCOAL && map[leftTopY][leftTopX] != CHARCOAL) {
			player.isJump = false;
			isBrocken[leftBottomY][leftBottomX] = true;
		}
		if (map[leftBottomY][leftBottomX] != CHARCOAL && map[rightBottomY][rightBottomX] == CHARCOAL && map[rightTopY][rightTopX] != CHARCOAL) {
			player.isJump = false;
			isBrocken[rightBottomY][rightBottomX] = true;
		}
		if (map[leftBottomY][leftBottomX] == CHARCOAL && map[jumpLeftBottomY][jumpLeftBottomX] != CHARCOAL) {
			player.isJump = false;
			isBrocken[leftBottomY][leftBottomX] = true;
		}
		if (map[rightBottomY][rightBottomX] == CHARCOAL && map[jumpRightBottomY][jumpRightBottomX] != CHARCOAL) {
			player.isJump = false;
			isBrocken[rightBottomY][rightBottomX] = true;
		}
		if (map[leftBottomY][leftBottomX] == CHARCOAL && map[rightBottomY][rightBottomX] == CHARCOAL) {
			player.isJump = false;
			isBrocken[leftBottomY][leftBottomX] = true;
			isBrocken[rightBottomY][rightBottomX] = true;
		}
	}

	if (map[leftTopY][leftTopX] == BLOCK) {
		if (map[oldLeftTopY][leftTopX] != BLOCK && map[leftTopY][oldLeftTopX] != BLOCK) {}

		else if (map[oldLeftTopY][leftTopX] != BLOCK && map[leftTopY][oldLeftTopX] == BLOCK) {
			player.transform.y = oldPlayer.y;

		}

		else if (map[oldLeftTopY][leftTopX] == BLOCK && map[leftTopY][oldLeftTopX] != BLOCK) {
			player.transform.x = oldPlayer.x;
		}

		else if (map[oldLeftTopY][leftTopX] == BLOCK && map[leftTopY][oldLeftTopX] == BLOCK) {
			player.transform.x = oldPlayer.x;
			player.transform.y = oldPlayer.y;
		}
	}
	if (map[rightTopY][rightTopX] == BLOCK) {
		if (map[oldRightTopY][rightTopX] != BLOCK && map[rightTopY][oldRightTopX] != BLOCK) {}

		else if (map[oldRightTopY][rightTopX] != BLOCK && map[rightTopY][oldRightTopX] == BLOCK) {
			player.transform.y = oldPlayer.y;

		}

		else if (map[oldRightTopY][rightTopX] == BLOCK && map[rightTopY][oldRightTopX] != BLOCK) {
			player.transform.x = oldPlayer.x;
		}

		else if (map[oldRightTopY][rightTopX] == BLOCK && map[rightTopY][oldRightTopX] == BLOCK) {
			player.transform.x = oldPlayer.x;
			player.transform.y = oldPlayer.y;
		}
	}
	if (map[leftBottomY][leftBottomX] == BLOCK) {

		if (map[oldLeftBottomY][leftBottomX] != BLOCK && map[leftBottomY][oldLeftBottomX] != BLOCK) {}

		else if (map[oldLeftBottomY][leftBottomX] != BLOCK && map[leftBottomY][oldLeftBottomX] == BLOCK) {
			player.transform.y = oldPlayer.y;
		}

		else if (map[oldLeftBottomY][leftBottomX] == BLOCK && map[leftBottomY][oldLeftBottomX] != BLOCK) {
			player.transform.x = oldPlayer.x;
		}

		else if (map[oldLeftBottomY][leftBottomX] == BLOCK && map[leftBottomY][oldLeftBottomX] == BLOCK) {
			player.transform.x = oldPlayer.x;
			player.transform.y = oldPlayer.y;
		}
	}
	if (map[rightBottomY][rightBottomX] == BLOCK) {
		if (map[oldRightBottomY][rightBottomX] != BLOCK && map[rightBottomY][oldRightBottomX] != BLOCK) {}

		else if (map[oldRightBottomY][rightBottomX] != BLOCK && map[rightBottomY][oldRightBottomX] == BLOCK) {
			player.transform.y = oldPlayer.y;
		}

		else if (map[oldRightBottomY][rightBottomX] == BLOCK && map[rightBottomY][oldRightBottomX] != BLOCK) {
			player.transform.x = oldPlayer.x;
		}

		else if (map[oldRightBottomY][rightBottomX] == BLOCK && map[rightBottomY][oldRightBottomX] == BLOCK) {
			player.transform.x = oldPlayer.x;
			player.transform.y = oldPlayer.y;
		}
	}

	if (map[leftTopY][leftTopX] == CHARCOAL) {
		if (map[oldLeftTopY][leftTopX] != CHARCOAL && map[leftTopY][oldLeftTopX] != CHARCOAL) {}

		else if (map[oldLeftTopY][leftTopX] != CHARCOAL && map[leftTopY][oldLeftTopX] == CHARCOAL) {
			player.transform.y = oldPlayer.y;

		}

		else if (map[oldLeftTopY][leftTopX] == CHARCOAL && map[leftTopY][oldLeftTopX] != CHARCOAL) {
			player.transform.x = oldPlayer.x;
		}

		else if (map[oldLeftTopY][leftTopX] == CHARCOAL && map[leftTopY][oldLeftTopX] == CHARCOAL) {
			player.transform.x = oldPlayer.x;
			player.transform.y = oldPlayer.y;
		}
	}
	if (map[rightTopY][rightTopX] == CHARCOAL) {
		if (map[oldRightTopY][rightTopX] != CHARCOAL && map[rightTopY][oldRightTopX] != CHARCOAL) {}

		else if (map[oldRightTopY][rightTopX] != CHARCOAL && map[rightTopY][oldRightTopX] == CHARCOAL) {
			player.transform.y = oldPlayer.y;

		}

		else if (map[oldRightTopY][rightTopX] == CHARCOAL && map[rightTopY][oldRightTopX] != CHARCOAL) {
			player.transform.x = oldPlayer.x;
		}

		else if (map[oldRightTopY][rightTopX] == CHARCOAL && map[rightTopY][oldRightTopX] == CHARCOAL) {
			player.transform.x = oldPlayer.x;
			player.transform.y = oldPlayer.y;
		}
	}
	if (map[leftBottomY][leftBottomX] == CHARCOAL) {

		if (map[oldLeftBottomY][leftBottomX] != CHARCOAL && map[leftBottomY][oldLeftBottomX] != CHARCOAL) {}

		else if (map[oldLeftBottomY][leftBottomX] != CHARCOAL && map[leftBottomY][oldLeftBottomX] == CHARCOAL) {
			player.transform.y = oldPlayer.y;
		}

		else if (map[oldLeftBottomY][leftBottomX] == CHARCOAL && map[leftBottomY][oldLeftBottomX] != CHARCOAL) {
			player.transform.x = oldPlayer.x;
		}

		else if (map[oldLeftBottomY][leftBottomX] == CHARCOAL && map[leftBottomY][oldLeftBottomX] == CHARCOAL) {
			player.transform.x = oldPlayer.x;
			player.transform.y = oldPlayer.y;
		}
	}
	if (map[rightBottomY][rightBottomX] == CHARCOAL) {
		if (map[oldRightBottomY][rightBottomX] != CHARCOAL && map[rightBottomY][oldRightBottomX] != CHARCOAL) {}

		else if (map[oldRightBottomY][rightBottomX] != CHARCOAL && map[rightBottomY][oldRightBottomX] == CHARCOAL) {
			player.transform.y = oldPlayer.y;
		}

		else if (map[oldRightBottomY][rightBottomX] == CHARCOAL && map[rightBottomY][oldRightBottomX] != CHARCOAL) {
			player.transform.x = oldPlayer.x;
		}

		else if (map[oldRightBottomY][rightBottomX] == CHARCOAL && map[rightBottomY][oldRightBottomX] == CHARCOAL) {
			player.transform.x = oldPlayer.x;
			player.transform.y = oldPlayer.y;
		}
	}
}

void Player::DownPlayer(int map[][50], int BLOCK_SIZE) {
	if (player.isJump == false) {
		for (int i = 0; i < G; i++) {
			if (map[leftBottomY][leftBottomX] == BLOCK || map[rightBottomY][rightBottomX] == BLOCK) {
				break;
			}
			if (map[leftBottomY][leftBottomX] == CHARCOAL || map[rightBottomY][rightBottomX] == CHARCOAL) {
				break;
			}
			else {
				player.transform.y++;
				GetPlayerBottom(BLOCK_SIZE);
			}
		}
	}
}

void Player::CheckStick(int InputY, int isRescued) {
	if (InputY > 0 && isRescued == false && water > 0) {
		player.isJump = true;
	}
}


void Player::DrawPlayer(int isRescued) {
	if (isDamageTimer % 5 != 1 && isDamageTimer % 5 != 2) {
		//DrawBox(player.transform.x - player.r - scroll, player.transform.y - player.r,
			//player.transform.x + player.r - scroll, player.transform.y + player.r, GetColor(200, 200, 200), true);
		if (isRescued == false) {
			DrawRotaGraph(player.transform.x - scroll + 3, player.transform.y - 3, 0.8, 0.0, graph_h, 1, way, 0);
		}
		if (isRescued == true) {
			DrawRotaGraph(player.transform.x - scroll + 3, player.transform.y - 3, 0.8, 0.0, graph_h2, 1, way, 0);
		}

	}

}

void Player::DrawHp() {
	for (int i = 0; i < 3; i++) {
		DrawCircle(player.transform.x - scroll, player.transform.y - 10 + (i * 10), 4, GetColor(55, 55, 55), false);
	}

	for (int i = 0; i < hp; i++) {
		DrawCircle(player.transform.x - scroll, player.transform.y - 10 + (i * 10), 4, GetColor(55, 55, 55), true);
	}
}

void Player::DrawWater() {
	if (water > 0) {
		DrawBox(100, 920, 100 + water, 950, GetColor(0, 160, 200), true);
	}
	DrawGraph(75, 920, waterTank, true);
}