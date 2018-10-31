#include "sdkmesh.h"
#include <cassert>
#include <iostream>

void Sdkmesh::DoCheck()
{
	// cpp lacks binary standard in class and struct padding
	// so we have to make sure that the size of our headers are exacting the same as the input binary file's
	static_assert(sizeof(VertexElement) == 8, "Decl structure size incorrect");
	static_assert(sizeof(SdkmeshHeader) == 104, "SDK Mesh structure size incorrect");
	static_assert(sizeof(SdkmeshVertexBufferHeader) == 288, "SDK Mesh structure size incorrect");
	static_assert(sizeof(SdkmeshIndexBufferHeader) == 32, "SDK Mesh structure size incorrect");
	static_assert(sizeof(SdkmeshMesh) == 224, "SDK Mesh structure size incorrect");
	static_assert(sizeof(SdkmeshSubset) == 144, "SDK Mesh structure size incorrect");
	static_assert(sizeof(SdkmeshFrame) == 184, "SDK Mesh structure size incorrect");
	static_assert(sizeof(SdkmeshMaterial) == 1256, "SDK Mesh structure size incorrect");

	// not supported for animation
	//static_assert(sizeof(DXUT::SDKANIMATION_FILE_HEADER) == 40, "SDK Mesh structure size incorrect");
	//static_assert(sizeof(DXUT::SDKANIMATION_DATA) == 40, "SDK Mesh structure size incorrect");
	//static_assert(sizeof(DXUT::SDKANIMATION_FRAME_DATA) == 112, "SDK Mesh structure size incorrect");
}

void Sdkmesh::LoadSdkmeshHeader(std::ifstream& inputStream, std::streampos fileSize)
{
	std::streampos pos = inputStream.tellg();
	if (fileSize - pos < sizeof(Sdkmesh::SdkmeshHeader))
		throw std::exception("EOF before reading Sdkmesh_header");

	std::cout << pos << std::endl;

	// deprecated
	/*inputStream.read((char*)&sdkmesh_header.version, sizeof(sdkmesh_header.version));
	inputStream.read((char*)&sdkmesh_header.IsBigEndian, sizeof(sdkmesh_header.IsBigEndian));
	inputStream.seekg(3, std::ios::cur);
	inputStream.read((char*)&sdkmesh_header.HeaderSize, sizeof(sdkmesh_header.HeaderSize));
	inputStream.read((char*)&sdkmesh_header.NonBufferDataSize, sizeof(sdkmesh_header.NonBufferDataSize));
	inputStream.read((char*)&sdkmesh_header.BufferDataSize, sizeof(sdkmesh_header.BufferDataSize));
	inputStream.read((char*)&sdkmesh_header.NumVertexBuffers, sizeof(sdkmesh_header.NumVertexBuffers));
	inputStream.read((char*)&sdkmesh_header.NumIndexBuffers, sizeof(sdkmesh_header.NumIndexBuffers));
	inputStream.read((char*)&sdkmesh_header.NumMeshes, sizeof(sdkmesh_header.NumMeshes));
	inputStream.read((char*)&sdkmesh_header.NumTotalSubsets, sizeof(sdkmesh_header.NumTotalSubsets));
	inputStream.read((char*)&sdkmesh_header.NumFrames, sizeof(sdkmesh_header.NumFrames));
	inputStream.read((char*)&sdkmesh_header.NumMaterials, sizeof(sdkmesh_header.NumMaterials));*/

	inputStream.read((char*)&sdkmesh_header, sizeof(SdkmeshHeader));

	// print to check
	/*std::cout << "sdkmesh_header.version: " << sdkmesh_header.version << std::endl;
	std::cout << "sdkmesh_header.IsBigEndian: " << sdkmesh_header.IsBigEndian << std::endl;
	std::cout << "sdkmesh_header.HeaderSize: " << sdkmesh_header.HeaderSize << std::endl;
	std::cout << "sdkmesh_header.NonBufferDataSize: " << sdkmesh_header.NonBufferDataSize << std::endl;
	std::cout << "sdkmesh_header.BufferDataSize: " << sdkmesh_header.BufferDataSize << std::endl;
	std::cout << "sdkmesh_header.NumMeshes: " << sdkmesh_header.NumMeshes << std::endl;*/

}

void Sdkmesh::LoadSdkmeshVertexBufferHeader(std::ifstream& inputStream, std::streampos fileSize)
{
	std::streampos pos = inputStream.tellg();
	if (fileSize - pos < sizeof(SdkmeshVertexBufferHeader))
		throw std::exception("EOF before reading Sdkmesh_vertex_buffer_header");

	std::cout << pos << std::endl;

	unsigned numbers = sdkmesh_header.NumVertexBuffers;
	sdkmesh_vertex_header_buffers.resize(numbers);
	for (unsigned i = 0; i < numbers; i++)
	{
		inputStream.read((char*)&(sdkmesh_vertex_header_buffers[i]), sizeof(SdkmeshVertexBufferHeader));
	}

	// print to check end decode
	/*std::cout << "sdkmesh_vertex_header_buffers[0].NumVertices: " << sdkmesh_vertex_header_buffers[0].NumVertices << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[0].SizeBytes: " << sdkmesh_vertex_header_buffers[0].SizeBytes << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[0].StrideBytes: " << sdkmesh_vertex_header_buffers[0].StrideBytes << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[0] Method:" << (int)sdkmesh_vertex_header_buffers[1].Decl[0].method << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[0] usage:" << (int)sdkmesh_vertex_header_buffers[1].Decl[0].usage << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[0] type:" << (int)sdkmesh_vertex_header_buffers[1].Decl[0].type << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[1] Method:" << (int)sdkmesh_vertex_header_buffers[1].Decl[1].method << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[1] usage:" << (int)sdkmesh_vertex_header_buffers[1].Decl[1].usage << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[1] type:" << (int)sdkmesh_vertex_header_buffers[1].Decl[1].type << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[2] Method:" << (int)sdkmesh_vertex_header_buffers[1].Decl[2].method << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[2] usage:" << (int)sdkmesh_vertex_header_buffers[1].Decl[2].usage << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[2] type:" << (int)sdkmesh_vertex_header_buffers[1].Decl[2].type << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[3] Method:" << (int)sdkmesh_vertex_header_buffers[1].Decl[3].method << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[3] usage:" << (int)sdkmesh_vertex_header_buffers[1].Decl[3].usage << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[3] type:" << (int)sdkmesh_vertex_header_buffers[1].Decl[3].type << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[4] Method:" << (int)sdkmesh_vertex_header_buffers[1].Decl[4].method << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[4] usage:" << (int)sdkmesh_vertex_header_buffers[1].Decl[4].usage << std::endl;
	std::cout << "sdkmesh_vertex_header_buffers[1].Declaration[4] type:" << (int)sdkmesh_vertex_header_buffers[1].Decl[4].type << std::endl;*/

	// vertex elemet structure (input Squidroom): 
	//    usage        type      method
	// 1. pos          Float3    default
	// 2. normal       Dec3N     default
	// 3. textureCord  HalfTwo   default
	// 4. tangent      Dec3N     default

}


void Sdkmesh::LoadSdkemshIndexBufferHeader(std::ifstream& inputStream, std::streampos fileSize)
{

}


void Sdkmesh::LoadSdkmeshMesh(std::ifstream& inputStream, std::streampos fileSize)
{

}


void Sdkmesh::LoadSdkmeshSubset(std::ifstream& inputStream, std::streampos fileSize)
{

}


void Sdkmesh::LoadSdkmeshFrame(std::ifstream& inputStream, std::streampos fileSize)
{

}


void Sdkmesh::LoadSdkmeshMaterial(std::ifstream& inputStream, std::streampos fileSize)
{

}

void Sdkmesh::LoadSdkmeshVertexBuffer(std::ifstream& inputStreamm, std::streampos fileSize)
{

}

void Sdkmesh::LoadSdkmeshIndexBuffer(std::ifstream& inputStream, std::streampos fileSize)
{

}

Sdkmesh::Sdkmesh(std::ifstream& inputStream, std::streampos fileSize)
{
	LoadSdkmeshHeader(inputStream, fileSize);
	LoadSdkmeshVertexBufferHeader(inputStream, fileSize);
	LoadSdkemshIndexBufferHeader(inputStream, fileSize);
	LoadSdkmeshMesh(inputStream, fileSize);
	LoadSdkmeshSubset(inputStream, fileSize);
	LoadSdkmeshFrame(inputStream, fileSize);
	LoadSdkmeshMaterial(inputStream, fileSize);

	LoadSdkmeshVertexBuffer(inputStream, fileSize);
	LoadSdkmeshIndexBuffer(inputStream, fileSize);
}

void Sdkmesh::CreateFromFile(std::ifstream& inputStream, std::streampos fileSize)
{

}