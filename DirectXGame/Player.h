#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "Affine.h"


class Player {
public:

	void Initalize(Model* model, uint32_t textureHandle,Vector3 pos);


	void Update();


	void Draw(ViewProjection &viewProjection);

	void SetEnemyPosition(Vector3 pos) { Enemypos = pos; };

	Vector3 GetWorldPosition();

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
