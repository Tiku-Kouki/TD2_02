#include "Player.h"
#include "ImGuiManager.h"
#include "cassert"
#define _USE_MATH_DEFINES
#include <math.h>

void Player::Initalize(Model* model, uint32_t textureHandle) {

	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_[0].scale_ = {1.0f, 1.0f, 1.0f};

	worldTransform_[0].rotation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_[0].translation_ = {0.0f, 0.0f, 0.0f};

	// enemy想定のworldTransform_
	worldTransform_[1].scale_ = {1.0f, 1.0f, 1.0f};

	worldTransform_[1].rotation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_[1].translation_ = {0.0f, 0.0f, 0.0f};

	for (int i = 0; i < 2; i++) {
		worldTransform_[i].Initialize();
	}
	input_ = Input::GetInstance();
}

void Player::Update() {

	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		theta -= 1.0f / 180.0f * (float)M_PI;
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		theta += 1.0f / 180.0f * (float)M_PI;
		move.x += kCharacterSpeed;
	}
	/*if (input_->PushKey(DIK_UP)) {
	    move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
	    move.y -= kCharacterSpeed;
	}*/

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(viewProjection_->rotation_.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_->rotation_.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(viewProjection_->rotation_.z);

	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	move = TransformNormal(move, rotateXYZMatrix);

	if (move.x != 0) {

		for (int i = 0; i < 4; i++) {
			worldTransform_[0].rotation_.y = std::atan2(
			    worldTransform_[1].translation_.x - worldTransform_[0].translation_.x,
			    worldTransform_[1].translation_.z - worldTransform_[0].translation_.z);
		}
	}

	for (int i = 0; i < 2; i++) {
		worldTransform_[0].translation_.x = cosf(theta) * 40 + (worldTransform_[1].translation_.x);
		worldTransform_[0].translation_.y += move.y;
		worldTransform_[0].translation_.z = sinf(theta) * 40 + (worldTransform_[1].translation_.z);

		worldTransform_[i].UpdateMatrix();
	}

#ifdef _DEBUG
	ImGui::Begin("du");
	ImGui::DragFloat3("dx", &worldTransform_[0].translation_.x, 0.1f);
	ImGui::End();
#endif
}

void Player::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_[0], viewProjection, textureHandle_);
}
