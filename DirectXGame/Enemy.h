#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "EnemyBullet.h"
#include <list>

class Player;


class Enemy {
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	void AddEnemyBullet(EnemyBullet* enemyBullet_);

	void Fire();

	void SetPlayer(Player* player) { player_ = player; };

	bool IsDead() const { return isDead_; }

	Vector3 GetWorldPosition();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

private:
	// ワールド座標データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// デスフラグ
	bool isDead_ = false;
	// 弾
	std::list<EnemyBullet*> bullets_;
	// 発射タイマー
	int32_t EnemyBulletTimer = 0;
	Player* player_ = nullptr;
	Model* EnemyBullet_ = nullptr;
};
