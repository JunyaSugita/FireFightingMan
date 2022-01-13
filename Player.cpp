#include "Player.h"

Player::Player() {
	player = {
		{
			100,
			800
		},
		20,
		0,
		0
	};

	oldPlayer = {
		0,
		0
	};

	inertia = 0;
	inertiaSpeed = 0;

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

	bullet = new Bullet;
	map = new Map;
}

Player::~Player() {
	delete bullet;
	delete map;
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

void Player::ResetIsJump(int map[][50]) {
	player.isJump = true;
	if (map[leftBottomY][leftBottomX] == BLOCK || map[rightBottomY][rightBottomX] == BLOCK) {
		player.isJump = false;
	}
}

void Player::PlayerMove(int LInputX, int RInputX, int RInputY) {
	if (LInputX > 0 || LInputX < 0) {
		player.transform.x += LInputX / 200;
	}
	player.transform.y += G - player.jumpPow;

	inertia = 0;
	if ((RInputX <= 0 && RInputY < 0) || (RInputX <= 0 && RInputY > 0) || RInputX < 0) {
		player.transform.x += (RInputX * -1) / 180;
		inertia = (RInputY * -1) / 40;
	}

	if (inertia > inertiaSpeed) {
		inertiaSpeed++;
	}
	else if (inertia < inertiaSpeed) {
		inertiaSpeed--;
	}
	player.transform.y += inertiaSpeed;
}

void Player::PlayerJump(int pad) {
	if (pad & PAD_INPUT_5 && player.isJump == 0) {
		player.isJump = 1;
		player.jumpPow = 30;
	}

	if (player.isJump == true && player.jumpPow > 0) {
		player.jumpPow--;
	}
}

void Player::PlayerShot(int InputX, int InputY) {
	if ((InputX <= 0 && InputY < 0) || (InputX <= 0 && InputY > 0) || InputX < 0) {
		bullet->BulletShot(player.transform, InputX, InputY);
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
	jumpLeftBottomY = (player.transform.y  - 1) / BLOCK_SIZE;
	jumpRightBottomX = (player.transform.x + player.r - 1) / BLOCK_SIZE;
	jumpRightBottomY = (player.transform.y - 1) / BLOCK_SIZE;
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

void Player::GetScroll() {
	if (player.transform.x >= WIN_WIDTH / 2 && player.transform.x <= WIN_WIDTH + (WIN_WIDTH / 2)) {
		scroll = player.transform.x - WIN_WIDTH / 2;
	}
}

void Player::BlockCollision(int map[][50]) {
	if ((map[rightTopY][rightTopX] == BLOCK || map[leftTopY][leftTopX] == BLOCK) && map[leftTopY][leftTopX] != BLOCK && map[rightTopY][rightTopX] != BLOCK) {
		player.jumpPow = 0;
	}
	if (map[leftBottomY][leftBottomX] == BLOCK) {
		player.isJump = false;
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
		player.isJump = false;
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
	if (map[leftTopY][leftTopX] == BLOCK) {
		player.isJump = true;
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
		player.isJump = true;
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

	if (map[jumpLeftBottomY][jumpLeftBottomX] == BLOCK || map[jumpRightBottomY][jumpRightBottomX] == BLOCK) {
		player.isJump = true;
	}
}

void Player::DownPlayer(int map[][50], int BLOCK_SIZE) {
	if (player.isJump == false) {
		for (int i = 0; i < 100; i++) {
			if (map[leftBottomY][leftBottomX] == BLOCK || map[rightBottomY][rightBottomX] == BLOCK) {
				break;
			}
			else {
				player.transform.y++;
				GetPlayerBottom(BLOCK_SIZE);
			}
		}
	}
}

void Player::DrawPlayer() {
	DrawBox(player.transform.x - player.r - scroll, player.transform.y - player.r,
		player.transform.x + player.r - scroll, player.transform.y + player.r, GetColor(200, 200, 200), true);
}