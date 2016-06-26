#pragma once

// Copyright (c) advancedfx.org
//
// Last changes:
// 2016-06-26 dominik.matrixstorm.com
//
// First changes:
// 2010-09-27 dominik.matrixstorm.com

#include <shared/vcpp/AfxAddr.h>

AFXADDR_DECL(csgo_C_BasePlayer_OFS_m_skybox3d_scale)
AFXADDR_DECL(csgo_CUnknown_GetPlayerName)
AFXADDR_DECL(csgo_CUnknown_GetPlayerName_DSZ)
AFXADDR_DECL(csgo_CHudDeathNotice_FireGameEvent)
AFXADDR_DECL(csgo_CHudDeathNotice_FireGameEvent_DSZ)
AFXADDR_DECL(csgo_CHudDeathNotice_UnkAddDeathNotice)
AFXADDR_DECL(csgo_CHudDeathNotice_UnkAddDeathNotice_DSZ)
AFXADDR_DECL(csgo_CHudDeathNotice_UnkAddDeathNotice_AddMovie_AfterModTime)
//AFXADDR_DECL(csgo_CScaleformSlotInitControllerClientImpl_UnkCheckSwf)
//AFXADDR_DECL(csgo_CScaleformSlotInitControllerClientImpl_UnkCheckSwf_DSZ)
AFXADDR_DECL(csgo_CSkyboxView_Draw)
AFXADDR_DECL(csgo_CSkyboxView_Draw_DSZ)
//AFXADDR_DECL(csgo_CViewRender_Render)
//AFXADDR_DECL(csgo_CViewRender_Render_DSZ)
AFXADDR_DECL(csgo_CViewRender_RenderView_AfterVGui_DrawHud)
AFXADDR_DECL(csgo_CViewRender_RenderSmokeOverlay_OnStoreAlpha)
AFXADDR_DECL(csgo_DS_CanRecord_ConsoleOpenCall)
AFXADDR_DECL(csgo_SplineRope_CShader_vtable)
AFXADDR_DECL(csgo_Spritecard_CShader_vtable)
AFXADDR_DECL(csgo_UnlitGeneric_CShader_vtable)
AFXADDR_DECL(csgo_VertexLitGeneric_CShader_vtable)
AFXADDR_DECL(csgo_S_StartSound_StringConversion)
AFXADDR_DECL(csgo_Scaleformui_CUnkown_Loader)
AFXADDR_DECL(csgo_Scaleformui_CUnkown_Loader_DSZ)
AFXADDR_DECL(csgo_gpGlobals_OFS_curtime)
AFXADDR_DECL(csgo_gpGlobals_OFS_interpolation_amount)
AFXADDR_DECL(csgo_gpGlobals_OFS_interval_per_tick)
AFXADDR_DECL(csgo_pLocalPlayer)
AFXADDR_DECL(csgo_snd_mix_timescale_patch)
AFXADDR_DECL(csgo_snd_mix_timescale_patch_DSZ)
AFXADDR_DECL(csgo_view)
AFXADDR_DECL(csgo_writeWaveConsoleOpenJNZ)
AFXADDR_DECL(cstrike_gpGlobals_OFS_absoluteframetime)
AFXADDR_DECL(cstrike_gpGlobals_OFS_curtime)
AFXADDR_DECL(cstrike_gpGlobals_OFS_interpolation_amount)
AFXADDR_DECL(cstrike_gpGlobals_OFS_interval_per_tick)

void Addresses_InitEngineDll(AfxAddr engineDll, bool isCsgo);
void Addresses_InitScaleformuiDll(AfxAddr scaleformuiDll, bool isCsgo);
void Addresses_InitClientDll(AfxAddr clientDll, bool isCsgo);
void Addresses_InitStdshader_dx9Dll(AfxAddr stdshader_dx9Dll, bool isCsgo);
