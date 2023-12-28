#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Transform
{
public:
    Transform();
    ~Transform();

    void MoveRelative(float dx, float dy, float dz);

    void SetPosition(float x, float y, float z);
    void SetRotation(float pitch, float yaw, float roll);
    void SetScale(float scaleX, float scaleY, float scaleZ);

    XMMATRIX GetWorldMatrix() const;

    XMVECTOR GetUpVector() const;
    XMVECTOR GetForwardVector() const;
    XMVECTOR GetRightVector() const;

    XMVECTOR GetPosition() const;
    XMVECTOR GetRotation() const;
    XMVECTOR GetScale() const;

private:
    XMFLOAT3 position;
    XMFLOAT3 rotation;
    XMFLOAT3 scale;

    XMVECTOR GetRotationQuaternion() const;
};
