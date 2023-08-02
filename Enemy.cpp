#include "Enemy.h"
#include "ImGuiManager.h"
#include "MyMath.h"
#include "cassert"
#include <Model.h>

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 2.0f, 30.0f};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	velocity_ = {0.0f, 0.0f, 0.0f};
	moveApproachInitialize();
}

void Enemy::Update() {
	// worldTransform_.TransferMatrix();
	/*worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);*/
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	switch (phase_) {
	case Phase::Approach:
	default:
		// 接近移動
		moveApproach();
		break;

	case Phase::Leave:
		// 離脱移動
		moveLeave();
		break;
	}
	worldTransform_.UpdateMatrix();

	

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::moveApproach() {
	velocity_ = {0.0f, 0.0f, -0.01f};
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	if (worldTransform_.translation_.z < 5.0f) {
		phase_ = Phase::Leave;
	}

	/*Fire();*/
	fireTimer--;
	if (fireTimer <= 0) {
		Fire();
		fireTimer = kFireInterval;
	}
}

void Enemy::moveLeave() {
	velocity_ = {-0.2f, 0.2f, 0.0f};
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
}

void Enemy::Fire() {

	const float kBulletSpeed = -10.0f;
	Vector3 velocity(0, 0, kBulletSpeed);
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	bullets_.push_back(newBullet);
}

Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Enemy::moveApproachInitialize() { fireTimer = kFireInterval; }