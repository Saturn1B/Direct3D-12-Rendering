#include "Transform.h"

Transform::Transform() : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f)
{
}

Transform::~Transform()
{
}

void Transform::MoveRelative(float dx, float dy, float dz) {
    
    // Calculate the movement vector in local space
    XMVECTOR movement = XMVectorSet(dx, dy, dz, 0.0f);

    // Rotate the movement vector to align with the local orientation
    movement = XMVector3Rotate(movement, GetRotationQuaternion());

    // Update the position
    XMStoreFloat3(&position, XMVectorAdd(GetPosition(), movement));
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

XMVECTOR Transform::GetUpVector() const
{
    return XMVector3Rotate(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), GetRotationQuaternion());
}

XMVECTOR Transform::GetForwardVector() const
{
    return XMVector3Rotate(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), GetRotationQuaternion());
}

XMVECTOR Transform::GetRightVector() const 
{
    return XMVector3Rotate(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), GetRotationQuaternion());
}

XMVECTOR Transform::GetPosition() const
{
    return XMLoadFloat3(&position);
}

XMVECTOR Transform::GetRotation() const
{
    return XMLoadFloat3(&rotation);
}

XMVECTOR Transform::GetScale() const
{
    return XMLoadFloat3(&scale);
}

XMVECTOR Transform::GetRotationQuaternion() const {
    return XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&rotation));
}