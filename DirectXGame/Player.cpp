#include "Player.h"
#include "cassert"
#include"ImGuiManager.h"


void Player::Initalize(Model* model, uint32_t textureHandle) { 
	
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.Initialize();

	input_ = Input::GetInstance();


	
}

void Player::Update() {

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
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	


	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	
	worldTransform_.TransferMatrix();
#ifdef _DEBUG
	ImGui::Begin("du");
	ImGui::Text(
	    " x: %f,y: %f z: %f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);
	
	ImGui::End();
#endif


}

void Player::Draw(ViewProjection &viewProjection) {
	

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	

}




