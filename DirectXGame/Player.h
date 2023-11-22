#pragma once
#include "Model.h"
#include "WorldTransform.h"
 #include"RailCamera.h"
#include "Input.h"
#include "Affine.h"
 #include <list>
#include "Windows.h"
 #include "ViewProjection.h"

class Player {
public:

	void Initalize(Model* model, uint32_t textureHandle);


	void Update();



	void Draw(ViewProjection &viewProjection);

	const WorldTransform& GetWorldTransform() { return worldTransform_[0]; }

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	void SetTarget(const WorldTransform* target) { target_ = target; }

private:

	WorldTransform worldTransform_[2];

	const WorldTransform* target_ = nullptr;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	float theta = 0;

	  // 　カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
	};
