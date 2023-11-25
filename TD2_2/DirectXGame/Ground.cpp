#include "Ground.h"
#include <cassert>

void Ground::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_.x = 200;
	worldTransform_.scale_.y = 200;
	worldTransform_.scale_.z = 200;

}

void Ground::Update() { 
	worldTransform_.UpdateMatrix(); 
}

void Ground::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_.viewProjection);
}

