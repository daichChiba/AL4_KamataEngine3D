#include "MathUtliltyForText.h"
using namespace KamataEngine;
using namespace MathUtility;
void WorldTransform::UpdateMatrix() {
	//スケール、回転、平行移動を合成して行列を計算する
	matWorld_ = MathUtliltyForText::MakeAffineMatrix(scale_, rotation_, translation_);

	if (parent_) {
		matWorld_ *= parent_->matWorld_;
	}

	//定数バッファに転送する
	TransferMatrix();
}