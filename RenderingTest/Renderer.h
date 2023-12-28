#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"

#include "Vertex.h"
#include "Transform.h"
#include "WindowManager.h"
#include "GameLogic.h"

// this will only call release if an object exists (prevents exceptions calling release on non existant objects)
#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }

using namespace DirectX; // we will be using the directxmath library

// direct3d stuff
const int frameBufferCount = 3; // number of buffers we want, 2 for double buffering, 3 for tripple buffering

extern ID3D12Device* device; // direct3d device

extern IDXGISwapChain3* swapChain; // swapchain used to switch between render targets

extern ID3D12CommandQueue* commandQueue; // container for command lists

extern ID3D12DescriptorHeap* rtvDescriptorHeap; // a descriptor heap to hold resources like the render targets

extern ID3D12Resource* renderTargets[]; // number of render targets equal to buffer count

extern ID3D12CommandAllocator* commandAllocator[]; // we want enough allocators for each buffer * number of threads (we only have one thread)

extern ID3D12GraphicsCommandList* commandList; // a command list we can record commands into, then execute them to render the frame

extern ID3D12Fence* fence[];    // an object that is locked while our command list is being executed by the gpu. We need as many 
										 //as we have allocators (more if we want to know when the gpu is finished with an asset)

extern HANDLE fenceEvent; // a handle to an event when our fence is unlocked by the gpu

extern UINT64 fenceValue[frameBufferCount]; // this value is incremented each frame. each fence will have its own value

extern int frameIndex; // current rtv we are on

extern int rtvDescriptorSize; // size of the rtv descriptor on the device (all front and back buffers will be the same size)
					   // function declarations

bool InitD3D(); // initializes direct3d 12

void UpdateViewMatrix(const Transform& cameraTransform);
void UpdateObjectTransform(const Transform& objectTransform);
void UpdateConstantBuffer();

void UpdatePipeline(); // update the direct3d pipeline (update command lists)

void Render(); // execute the command list

void Cleanup(); // release com ojects and clean up memory

extern ID3D12PipelineState* pipelineStateObject; // pso containing a pipeline state

extern ID3D12RootSignature* rootSignature; // root signature defines data shaders will access

extern D3D12_VIEWPORT viewport; // area that output from rasterizer will be stretched to.

extern D3D12_RECT scissorRect; // the area to draw in. pixels outside that area will not be drawn onto

extern ID3D12Resource* vertexBuffer; // a default buffer in GPU memory that we will load vertex data for our triangle into
extern ID3D12Resource* indexBuffer; // a default buffer in GPU memory that we will load index data for our triangle into

extern D3D12_VERTEX_BUFFER_VIEW vertexBufferView; // a structure containing a pointer to the vertex data in gpu memory
										   // the total size of the buffer, and the size of each element (vertex)

extern D3D12_INDEX_BUFFER_VIEW indexBufferView; // a structure holding information about the index buffer

extern ID3D12Resource* depthStencilBuffer; // This is the memory for our depth buffer. it will also be used for a stencil buffer in a later tutorial
extern ID3D12DescriptorHeap* dsDescriptorHeap; // This is a heap for our depth/stencil buffer descriptor

struct ConstantBufferPerObject {
	XMFLOAT4X4 wvpMat;
};

// Constant buffers must be 256-byte aligned which has to do with constant reads on the GPU.
// We are only able to read at 256 byte intervals from the start of a resource heap, so we will
// make sure that we add padding between the two constant buffers in the heap (one for cube1 and one for cube2)
// Another way to do this would be to add a float array in the constant buffer structure for padding. In this case
// we would need to add a float padding[50]; after the wvpMat variable. This would align our structure to 256 bytes (4 bytes per float)
// The reason i didn't go with this way, was because there would actually be wasted cpu cycles when memcpy our constant
// buffer data to the gpu virtual address. currently we memcpy the size of our structure, which is 16 bytes here, but if we
// were to add the padding array, we would memcpy 64 bytes if we memcpy the size of our structure, which is 50 wasted bytes
// being copied.
extern int ConstantBufferPerObjectAlignedSize;

extern ConstantBufferPerObject cbPerObject; // this is the constant buffer data we will send to the gpu 
									 // (which will be placed in the resource we created above)

extern ID3D12Resource* constantBufferUploadHeaps[]; // this is the memory on the gpu where constant buffers for each frame will be placed

extern UINT8* cbvGPUAddress[]; // this is a pointer to each of the constant buffer resource heaps

extern XMFLOAT4X4 cameraProjMat; // this will store our projection matrix
extern XMFLOAT4X4 cameraViewMat; // this will store our view matrix

extern int numCubeIndices; // the number of indices to draw the cube