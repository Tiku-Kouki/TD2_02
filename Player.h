#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "Affine.h"
 #include"RailCamera.h"
#include "Affine.h"

#include <list>
#include "Windows.h"



class Player {

public:
	void Initalize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection &viewProjection);
	const WorldTransform& GetWorldTransform();

	int x = 0;

private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;

	int mon;

};
