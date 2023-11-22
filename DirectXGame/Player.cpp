#include "Player.h"
#include "cassert"
#include "ImGuiManager.h"
 #define _USE_MATH_DEFINES
#include <math.h>

void Player::Initalize(Model* model, uint32_t textureHandle,Vector3 pos) { 
	
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.translation_ = {pos};

	worldTransform_.Initialize();

	input_ = Input::GetInstance();


	
}

void Player::Update() {

	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
	/*	move.x -= kCharacterSpeed;*/
		angle -= 1.0f / 180.0f * (float)M_PI;
	} else if (input_->PushKey(DIK_RIGHT)) {
		/*move.x += kCharacterSpeed;*/
		angle += 1.0f / 180.0f * (float)M_PI;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(viewProjection_->rotation_.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_->rotation_.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(viewProjection_->rotation_.z);

	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	//move = TransformNormal(move, rotateXYZMatrix);

	

			worldTransform_.rotation_.y = std::atan2(
			    Enemypos.x - worldTransform_.translation_.x,
			    Enemypos.z - worldTransform_.translation_.z);
		
	
	worldTransform_.translation_.x = Enemypos.x + std::cos(angle) * 50.0f;
	worldTransform_.translation_.z = Enemypos.z + std::sin(angle) * 50.0f;


	worldTransform_.UpdateMatrix();
#ifdef _DEBUG
	ImGui::Begin("du");
	ImGui::Text(
	    " x: %f,y: %f z: %f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);
	
	ImGui::End();
#endif



}

void Player::Draw(ViewProjection &viewProjection) {
	

	model_->Draw(worldTransform_, viewProjection);
	

}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
