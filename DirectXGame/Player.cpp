#include "Player.h"
#include "cassert"
#include "ImGuiManager.h"
 #define _USE_MATH_DEFINES
#include <math.h>
#include <numbers>

void Player::Initalize(Model* model, Model* PlayerBullet, uint32_t textureHandle, Vector3 pos) { 
	
	assert(model); 
	assert(PlayerBullet);
	model_ = model;
	
	ModelPlayerBullet_ = PlayerBullet;
	textureHandle_ = textureHandle;


	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};

	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.translation_ = {pos};

	worldTransform_.Initialize();

	input_ = Input::GetInstance();

	 Life_ = 3;
	
}

void Player::Update() {

	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;

	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	if (input_->PushKey(DIK_LEFT)) {
	/*	move.x -= kCharacterSpeed;*/
		angle -= 1.0f / 180.0f * std::numbers::pi_v<float>;
	} else if (input_->PushKey(DIK_RIGHT)) {
		/*move.x += kCharacterSpeed;*/
		angle += 1.0f / 180.0f * std::numbers::pi_v<float>;
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


	// キャラクターの攻撃処理
	Attack();

	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	worldTransform_.UpdateMatrix();
#ifdef _DEBUG
	ImGui::Begin("du");
	ImGui::Text(
	    " x: %f,y: %f z: %f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);
	ImGui::Text(" x: %f", Enemypos.z);
	
	ImGui::End();
#endif



}

void Player::Draw(ViewProjection &viewProjection) {
	

	model_->Draw(worldTransform_, viewProjection);
	
	 for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
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

void Player::OnCollision() {
	Life_--;
	if (Life_ <= 0) {
		isDead_ = true;
	}
}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {

		if (--BulletTimer < 0) {
			BulletTimer = 30;

			// 弾の速度
			const float kBulletSpeed = 1.0f;
			

			

			Vector3 enemyWorld = Enemypos;
			Vector3 playerWorld = GetWorldPosition();

			Vector3 difVector = {
			    enemyWorld.x - playerWorld.x,
				enemyWorld.y - playerWorld.y ,
			    enemyWorld.z - playerWorld.z };

			Vector3 difVectorN = Normalize(difVector);

			Vector3 velocity(
			    difVectorN.x * kBulletSpeed, difVectorN.y * kBulletSpeed,
			    difVectorN.z * kBulletSpeed);

			//velocity = TransformNormal(velocity, worldTransform_.matWorld_);

			

			// 弾を生成し、初期化
			PlayerBullet* newBullet = new PlayerBullet();
			newBullet->Initialize(ModelPlayerBullet_, GetWorldPosition(), velocity);

			// 弾を登録する
			bullets_.push_back(newBullet);
		}
	}
}
