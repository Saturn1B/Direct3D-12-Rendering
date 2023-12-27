#include "Transform.h"

Transform::Transform() : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f)
{
}

Transform::~Transform()
{
}

void Transform::SetPosition(float x, float y, float z)
{
    position = XMFLOAT3(x, y, z);
}

void Transform::SetRotation(float pitch, float yaw, float roll)
{
    rotation = XMFLOAT3(pitch, yaw, roll);
}

void Transform::SetScale(float scaleX, float scaleY, float scaleZ)
{
    scale = XMFLOAT3(scaleX, scaleY, scaleZ);
}

XMMATRIX Transform::GetWorldMatrix()
{
    XMMATRIX translationMat = XMMatrixTranslationFromVector(XMLoadFloat3(&position));
    XMMATRIX rotationMat = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&rotation));
    XMMATRIX scaleMat = XMMatrixScalingFromVector(XMLoadFloat3(&scale));

    return scaleMat * rotationMat * translationMat;
}