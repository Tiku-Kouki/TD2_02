#pragma once
#include "Affine.h"
#include "Input.h"
#include "Model.h"
#include "RailCamera.h"
#include "ViewProjection.h"
#include "Windows.h"
#include "WorldTransform.h"
#include <list>

class Player {
public:
	void Initalize(Model* model, uint32_t textureHandle, Vector3 pos);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void SetEnemyPosition(Vector3 pos) { Enemypos = pos; };

	Vector3 GetWorldPosition();

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	Vector3 Enemypos = {};

	float angle = 0.0f;

	// 　カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
};
