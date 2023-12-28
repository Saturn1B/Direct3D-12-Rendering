#include "GameLogic.h"

#pragma region VariableInitialization

time_point startTime = high_resolution_clock::now();
time_point prevTime = startTime;

Transform cameraTransform;
float rotationAngleX = 0.0f;
float rotationAngleY = 0.0f;
float rotationAngleZ = 0.0f;
float cameraMoveSpeed = 10.0f;
float cameraRotationSpeed = 0.00005f;
float xrot = 0.0f;
float yrot = 0.0f;
float zrot = 0.0f;

bool Running = true;

XMFLOAT4X4 cube1WorldMat;
XMFLOAT4X4 cube1RotMat;
XMFLOAT4 cube1Position;

#pragma endregion

void Update(double deltaTimeSec)
{
	// update app logic, such as moving the camera or figuring out what objects are in view

	// Handle user input for camera movement
	if (GetAsyncKeyState('W') & 0x8000) {
		cameraTransform.MoveRelative(0.0f, 0.0f, static_cast<float>(deltaTimeSec) * cameraMoveSpeed);
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		cameraTransform.MoveRelative(0.0f, 0.0f, static_cast<float>(deltaTimeSec) * -cameraMoveSpeed);
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		cameraTransform.MoveRelative(static_cast<float>(deltaTimeSec) * -cameraMoveSpeed, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		cameraTransform.MoveRelative(static_cast<float>(deltaTimeSec) * cameraMoveSpeed, 0.0f, 0.0f);
	}
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
		cameraTransform.MoveRelative(0.0f, static_cast<float>(deltaTimeSec) * -cameraMoveSpeed, 0.0f);
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		cameraTransform.MoveRelative(0.0f, static_cast<float>(deltaTimeSec) * cameraMoveSpeed, 0.0f);
	}

	rotationAngleY += static_cast<float>(deltaTimeSec) * cameraRotationSpeed * static_cast<float>(GetAsyncKeyState(VK_RIGHT) & 0x8001) -
		static_cast<float>(deltaTimeSec) * cameraRotationSpeed * static_cast<float>(GetAsyncKeyState(VK_LEFT) & 0x8001);
	rotationAngleX += static_cast<float>(deltaTimeSec) * cameraRotationSpeed * static_cast<float>(GetAsyncKeyState(VK_DOWN) & 0x8001) -
		static_cast<float>(deltaTimeSec) * cameraRotationSpeed * static_cast<float>(GetAsyncKeyState(VK_UP) & 0x8001);

	cameraTransform.SetRotation(rotationAngleX, rotationAngleY, 0.0f);

	// Update camera view matrix
	XMVECTOR cPos = cameraTransform.GetPosition();
	XMVECTOR cForward = cameraTransform.GetForwardVector();
	XMVECTOR cUp = cameraTransform.GetUpVector();
	XMVECTOR cTarg = cPos + cForward;
	XMMATRIX viewMat1 = XMMatrixLookAtLH(cPos, cTarg, cUp);
	XMStoreFloat4x4(&cameraViewMat, viewMat1);

	// Increment rotation angles over time
	xrot += static_cast<float>(deltaTimeSec) * 0.1f;
	yrot += static_cast<float>(deltaTimeSec) * 0.1f;
	zrot += static_cast<float>(deltaTimeSec) * 0.1f;

	// Update cube1's transformation using Transform class
	Transform cube1Transform;
	cube1Transform.SetRotation(xrot, yrot, zrot);
	cube1Transform.SetPosition(cube1Position.x, cube1Position.y, 5 + zrot);
	//cube1Transform.SetScale(rotationAngleX, rotationAngleY, rotationAngleZ);

	// Get the world matrix from the Transform class
	XMMATRIX worldMat = cube1Transform.GetWorldMatrix();

	// store cube1's world matrix
	XMStoreFloat4x4(&cube1WorldMat, worldMat);

	// update constant buffer for cube1
	// create the wvp matrix and store in constant buffer
	XMMATRIX viewMat = XMLoadFloat4x4(&cameraViewMat); // load view matrix
	XMMATRIX projMat = XMLoadFloat4x4(&cameraProjMat); // load projection matrix
	XMMATRIX wvpMat = XMLoadFloat4x4(&cube1WorldMat) * viewMat * projMat; // create wvp matrix
	XMMATRIX transposed = XMMatrixTranspose(wvpMat); // must transpose wvp matrix for the gpu
	XMStoreFloat4x4(&cbPerObject.wvpMat, transposed); // store transposed wvp matrix in constant buffer

													  // copy our ConstantBuffer instance to the mapped constant buffer resource
	memcpy(cbvGPUAddress[frameIndex], &cbPerObject, sizeof(cbPerObject));
}