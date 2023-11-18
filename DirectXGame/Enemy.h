#pragma once
#include "WorldTransform.h"
#include "Model.h"


class Enemy {
public:
	void Initialize(Model* model, uint32_t textureHandle, Vector3 pos);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

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

};
