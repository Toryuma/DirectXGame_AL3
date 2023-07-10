#include "Player.h"
#include "cassert"
#include <Model.h>
#include <MyMath.h>
#include "ImGuiManager.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {

	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
};

void Player::Update() {
	worldTransform_.TransferMatrix();

	// スケーリング行列宣言
	Matrix4x4 matScale = {0};
	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;
	matScale.m[3][3] = 1;

	Matrix4x4 matRotX = {0};
	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sinf(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sinf(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cosf(worldTransform_.rotation_.x);
	matRotX.m[3][3] = 1;

	Matrix4x4 matRotY = {0};
	matRotY.m[0][0] = cosf(worldTransform_.rotation_.y);
	matRotY.m[1][1] = 1;
	matRotY.m[0][2] = -sinf(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sinf(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cosf(worldTransform_.rotation_.y);
	matRotY.m[3][3] = 1;

	Matrix4x4 matRotZ = {0};
	matRotZ.m[0][0] = cosf(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = sinf(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = -sinf(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cosf(worldTransform_.rotation_.z);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	Matrix4x4 matRot = MakeRotateXYZMatrix(matRotX, matRotY, matRotZ);
	Matrix4x4 matTrans = MakeTranslateMatrix(worldTransform_.translation_);

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// キーボード移動処理
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	// 移動限界座標
	const float kMoveLimitX = 10;
	const float kMoveLimitY = 10;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	ImGui::Begin("Debug");
	float playerPos[] = {
	    worldTransform_.translation_.x, 
		worldTransform_.translation_.y,
	    worldTransform_.translation_.z
	};
	ImGui::SliderFloat3("PlayerPos", playerPos, 30, 15);

	worldTransform_.translation_.x = playerPos[0];
	worldTransform_.translation_.y = playerPos[1];
	worldTransform_.translation_.z = playerPos[2];
	ImGui::End();

	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}