#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"
#include "EnemyBullet.h"
#include<list>

class Enemy {

public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);
	//接近フェーズ
	void moveApproach();
	//離脱フェーズ
	void moveLeave();
	void Fire();
	~Enemy();
	static const int kFireInterval = 60;
	//接近フェーズ初期化
	void moveApproachInitialize();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_;

	std::list<EnemyBullet*> bullets_;

	enum class Phase {
		Approach,
		Leave,
	};
	Phase phase_ = Phase::Approach;//クラスの中はすべてクラスで返す

	int32_t fireTimer = 0;
};