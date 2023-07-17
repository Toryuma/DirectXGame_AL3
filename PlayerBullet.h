#pragma once
#include <Model.h>
#include <Player.h>
#include <WorldTransform.h>

class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;

};