#include "RailCamera.h"
#include "MathUtliltyForText.h"
using namespace KamataEngine;
using namespace MathUtility;

void RailCamera::Initialize(Vector3& pos, Vector3& rotate, Camera& camera) {
	// ���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	worldTransform_.rotation_ = rotate;

	// �J�����̏�����
	camera_ = &camera;
}

void RailCamera::Update() {

	// ���[���h�g�����X�t�H�[���̍��W�̐��l�����Z�����肷��(�ړ�)

	// ���[���h�g�����X�t�H�[���̍��W�̐��l�����Z�����肷��(�ړ�)

	// �J�����I�u�W�F�N�g�̃��[���h�s�񂩂�r���[�s����v�Z����
	camera_->matView = Inverse(worldTransform_.matWorld_);
}
