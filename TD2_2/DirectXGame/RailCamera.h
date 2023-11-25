#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class RailCamera {

	private:
	bool isDebugCameraActive_ = false;

	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	const WorldTransform* target_ = nullptr;

	

public:
	void Initalize();

	void Update();

	~RailCamera();

	Vector3 GetWorldPosition();

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	void SetTarget(const WorldTransform* target) { target_ = target; }

};
