#include "Enemy.h"
#include "EnemyBullet.h"
#include <cassert>
#include "Player.h"
#include "Affine.h"
#include "Mymath.h"
#include "ImGuiManager.h"


Enemy::~Enemy() {

}

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	worldTransform_.scale_ = {10.0f, 10.0f, 10.0f};

	worldTransform_.rotation_ = {0.0f, 4.6f, 0.0f};

	worldTransform_.translation_ = {0.0f, 0.0f, 50.0f};

	EnemyBullet_ = Model::CreateFromOBJ("EnemyBullet", true);
}

void Enemy::Update() { 

	

	worldTransform_.UpdateMatrix(); 

		phaseReset();

		


	#ifdef _DEBUG
	ImGui::Begin("x");
	ImGui::Text(" %d", isDead_);

	ImGui::End();
#endif

	


}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);

	

}

void Enemy::OnCollision() {
	isDead_ = true;
}

void Enemy::AddEnemyBullet(EnemyBullet* enemyBullet_) {
	bullets_.push_back(enemyBullet_); 
}

void Enemy::Fire() {
	assert(player_);

	// 弾の速度
	const float kBulletSpeed = 1.0f;

	Vector3 PlayerWorldPosition = player_->GetWorldPosition();

	Vector3 EnemyWorldPosition = GetWorldPosition();

	Vector3 difVector = {
	    PlayerWorldPosition.x - EnemyWorldPosition.x,
		PlayerWorldPosition.y - EnemyWorldPosition.y,
	    PlayerWorldPosition.z - EnemyWorldPosition.z};

	Vector3 difVectorN = Normalize(difVector);

	Vector3 velocity(
	    difVectorN.x * kBulletSpeed, difVectorN.y * kBulletSpeed, difVectorN.z * kBulletSpeed);

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_,worldTransform_.translation_, velocity);

	// 弾を登録する
	AddEnemyBullet(newBullet);
}


Vector3 Enemy::GetWorldPosition() { 
	Vector3 pos;
	pos.x = worldTransform_.matWorld_.m[3][0];
	pos.y = worldTransform_.matWorld_.m[3][1];
	pos.z = worldTransform_.matWorld_.m[3][2];

	return pos;

}

void Enemy::phaseReset() {

fireTimer--;

	if (fireTimer <= 0 ) {

		Fire();

		fireTimer = kFireInterval;
	}

}


