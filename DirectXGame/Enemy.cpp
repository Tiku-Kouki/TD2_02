#include "Enemy.h"
#include <cassert>
#include "Affine.h"

Enemy::~Enemy() {

}

void Enemy::Initialize(Model* model, uint32_t textureHandle, Vector3 pos) {
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	worldTransform_.translation_ = pos;

}

void Enemy::Update() {

}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

void Enemy::OnCollision() {
	isDead_ = true;
}

Vector3 Enemy::GetWorldPosition() { 
	Vector3 pos;
	pos.x = worldTransform_.matWorld_.m[3][0];
	pos.y = worldTransform_.matWorld_.m[3][1];
	pos.z = worldTransform_.matWorld_.m[3][2];

	return pos;

}


