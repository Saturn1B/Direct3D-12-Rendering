#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Transform
{
public:
    Transform();
    ~Transform();

    void SetPosition(float x, float y, float z);
    void SetRotation(float pitch, float yaw, float roll);
    void SetScale(float scaleX, float scaleY, float scaleZ);

    XMMATRIX GetWorldMatrix();

private:
    XMFLOAT3 position;
    XMFLOAT3 rotation;
    XMFLOAT3 scale;
};
