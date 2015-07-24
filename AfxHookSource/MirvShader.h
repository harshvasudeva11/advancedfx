#pragma once

// Copyright (c) advancedfx.org
//
// Last changes:
// 2015-07-20 by dominik.matrixstorm.com
//
// First changes:
// 2010-04-22 by dominik.matrixstorm.com

#include <d3d9.h>

class MirvShader
{
public:
	MirvShader();
	~MirvShader();

	void BeginDevice(IDirect3DDevice9 * device);
	void EndDevice();

	bool OnSetVertexShader(IDirect3DVertexShader9 * pShader, HRESULT &outResult);
	bool OnSetPixelShader(IDirect3DPixelShader9 * pShader, HRESULT &outResult);

	void DebugDepthFixDraw();

private:
	IDirect3DDevice9 * m_Device;
	IDirect3DPixelShader9 * m_PixelShader;
	char * m_PsoFileName;
	bool m_ReloadPixelShader;
	bool m_ReloadVertexShader;
	IDirect3DVertexShader9 * m_VertexShader;
	char * m_VsoFileName;

	void LoadPso(char const * fileName);
	void LoadVso(char const * fileName);

	DWORD * LoadShaderFileInMemory(char const * fileName);

	void LoadShader();
	void LoadPixelShader();
	void LoadVertexShader();
	
	void UnloadShader();
	void UnloadPixelShader();
	void UnloadVertexShader();

};

extern MirvShader g_MirvShader;