#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
class Enemy {

public:
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;
	enum class Phase {
		Approach,
		Leave,
	};
	Phase phase_ = Phase::Approach;//クラスの中はすべてクラスで返す
};