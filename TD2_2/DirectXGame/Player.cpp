#include "Player.h"
#include "cassert"
#include "ImGuiManager.h"


void Player::Initalize(Model* model,Model* PlayerBullet, uint32_t textureHandle,Vector3 pos) { 
	
	assert(model);
	assert(PlayerBullet);
	model_ = model;
	ModelPlayerBullet_ = PlayerBullet;
	textureHandle_ = textureHandle;

	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};

	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};

	worldTransform_.translation_ = {pos};

	worldTransform_.Initialize();

	input_ = Input::GetInstance();

	model_ = Model::Create();


	Life_ = 3;
	
	
}

void Player::Update() {

	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;

	//デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});


	if (input_->PushKey(DIK_LEFT)) {
	/*	move.x -= kCharacterSpeed;*/
		angle -= 0.1f;
	} else if (input_->PushKey(DIK_RIGHT)) {
		/*move.x += kCharacterSpeed;*/
		angle += 0.1f;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	const float kMoveLimitX = 20;
	const float kMoveLimitY = 18;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	worldTransform_.translation_.x = Enemypos.x + std::cos(angle) * 50.0f;
	worldTransform_.translation_.z = Enemypos.z + std::sin(angle) * 50.0f;

	//キャラクターの攻撃処理
	Attack();

	//弾更新
	for (PlayerBullet* bullet : bullets_)
	{
		bullet->Update();
	}

	worldTransform_.UpdateMatrix();

	ImGui::Begin("du");
	ImGui::Text(
	    " x: %f,y: %f z: %f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);
	
	ImGui::End();




}

void Player::Draw(ViewProjection &viewProjection) {
	

	model_->Draw(worldTransform_, viewProjection);
	

}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::OnCollision() { 
	Life_--;
	if (Life_ <= 0) {
		isDead_ = true;
	}
}

void Player::Attack() {}
