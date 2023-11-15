#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "Affine.h"
 #include"RailCamera.h"
#include "Affine.h"

#include <list>
#include "Windows.h"
 #include "ViewProjection.h"



class Player {


private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	  // 　カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	public:
	void Initalize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	 void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}



};
