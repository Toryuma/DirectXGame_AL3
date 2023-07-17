#pragma once
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "WorldTransform.h"
#include "cassert"

class Player {

public:
	void Initialize(Model* model, uint32_t textureHandle);

	void Attack();

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	PlayerBullet* bullet_ = nullptr;
};
