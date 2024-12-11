#pragma once
#include"KamataEngine.h"
using namespace KamataEngine;
/// <summary>
/// ���[���J����
/// </summary>
class RailCamera {
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Vector3& pos, Vector3& rotate, Camera& camera);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// �J����
	Camera* camera_;

};
