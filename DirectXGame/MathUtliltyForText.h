#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

Matrix4x4 Multply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
// 　代入演算子オーバーロード
// 　Vector3の足算
Vector3& operator+=(Vector3& lhv, const Vector3& rhv);

// 2項演算子オーバーロード
// Vector3の足算
const Vector3 operator+(const Vector3& v1, const Vector3& v2);

// 　代入演算子オーバーロード
// 　Vector3の掛け算
Vector3& operator*=(Vector3& v, float s);

// 2項演算子オーバーロード
// Vector3の掛け算
const Vector3 operator*(const Vector3& v, float s);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

