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

    XMVECTOR GetPositionXM() const;
    XMVECTOR GetRotationXM() const;
    XMVECTOR GetScaleXM() const;

    XMFLOAT3  GetPosition() const;
    XMFLOAT3  GetRotation() const;
    XMFLOAT3  GetScale() const;

private:
    XMFLOAT3 position;
    XMFLOAT3 rotation;
    XMFLOAT3 scale;

    XMVECTOR GetRotationQuaternion() const;
};
