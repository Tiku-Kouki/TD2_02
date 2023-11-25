#include "Enemy.h"
#include "EnemyBullet.h"
#include <cassert>
#include "Player.h"
#include "Affine.h"
#include "Mymath.h"

Enemy::~Enemy() {

}

void Enemy::Initialize(Model* model, uint32_t textureHandle, Vector3 pos) {
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	worldTransform_.translation_ = pos;

	EnemyBullet_ = Model::CreateFromOBJ("EnemyBullet", true);
}

void Enemy::Update() { 
	worldTransform_.UpdateMatrix(); 
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
	const float kBulletSpeed = -1.0f;

	Vector3 PlayerWorldPosition = player_->GetWorldPosition();

	Vector3 EnemyWorldPosition = Enemy::GetWorldPosition();

	Vector3 A = Subtract(EnemyWorldPosition, PlayerWorldPosition);

	A = Normalize(A);

	Vector3 velocity = Multiply(A, kBulletSpeed);

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


