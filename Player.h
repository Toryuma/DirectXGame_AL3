#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include "PlayerBullet.h"
#include "Player.h"
#include<list>

class Player {

public:
	void Initialize(Model* model, uint32_t textureHandle);

	void Attack();

	void Update();

	void Draw(ViewProjection& viewProjection);

	~Player();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;

	/*PlayerBullet* bullet_;*/
	std::list<PlayerBullet*> bullets_;
};
