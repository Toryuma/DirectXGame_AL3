#include"Enemy.h"
#include "ImGuiManager.h"
#include "cassert"
#include <Model.h>
#include"MyMath.h"

	void Enemy::Initialize(Model* model, uint32_t textureHandle) {
		assert(model);

		model_ = model;
		textureHandle_ = textureHandle;

		worldTransform_.Initialize();
	    worldTransform_.translation_ = {0.0f,2.0f,0.0f};
		worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
		worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	    velocity_ ={0.0f, 0.0f, -0.2f};
	}

	void Enemy::Update() { 
		worldTransform_.TransferMatrix();
	    worldTransform_.UpdateMatrix();
	    worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	}

	void Enemy::Draw(ViewProjection& viewProjection) {
		model_->Draw(worldTransform_, viewProjection, textureHandle_);
	}