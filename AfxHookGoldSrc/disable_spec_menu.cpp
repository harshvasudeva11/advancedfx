#include "stdafx.h"

#include "hooks/HookHw.h"
#include "cmdregister.h"
#include "hl_addresses.h"
#include <shared/detours.h>
#include "hlsdk.h"

float g_OldHud_draw_value;
bool g_DisableSpecMenu = false;

typedef int (__stdcall *TeamFortressViewport_UpdateSpectatorPanel_t)(DWORD *this_ptr);

TeamFortressViewport_UpdateSpectatorPanel_t g_Old_TeamFortressViewport_UpdateSpectatorPanel;

void __stdcall New_TeamFortressViewport_UpdateSpectatorPanel(DWORD *this_ptr)
{
	if(!g_DisableSpecMenu)
	{
		g_Old_TeamFortressViewport_UpdateSpectatorPanel(this_ptr);
		return;
	}

	g_OldHud_draw_value = pEngfuncs->pfnGetCvarFloat("hud_draw");
	
	pEngfuncs->Cvar_SetValue("hud_draw", 0.0f);

	g_Old_TeamFortressViewport_UpdateSpectatorPanel(this_ptr);

	pEngfuncs->Cvar_SetValue("hud_draw", g_OldHud_draw_value);
}

bool Hook_TeamFortressViewport_UpdateSpectatorPanel_tfc(void)
{
	if(!HL_ADDR_GET(tfc_TeamFortressViewport_UpdateSpecatorPanel) || !HL_ADDR_GET(tfc_TeamFortressViewport_UpdateSpecatorPanel_DSZ))
		return false;

	g_Old_TeamFortressViewport_UpdateSpectatorPanel = (TeamFortressViewport_UpdateSpectatorPanel_t)DetourClassFunc((BYTE *)HL_ADDR_GET(tfc_TeamFortressViewport_UpdateSpecatorPanel), (BYTE *)New_TeamFortressViewport_UpdateSpectatorPanel, (int)HL_ADDR_GET(tfc_TeamFortressViewport_UpdateSpecatorPanel_DSZ));
	return true;
}

bool Hook_TeamFortressViewport_UpdateSpectatorPanel_valve(void)
{
	if(!HL_ADDR_GET(valve_TeamFortressViewport_UpdateSpecatorPanel) || !HL_ADDR_GET(valve_TeamFortressViewport_UpdateSpecatorPanel_DSZ))
		return false;

	g_Old_TeamFortressViewport_UpdateSpectatorPanel = (TeamFortressViewport_UpdateSpectatorPanel_t)DetourClassFunc((BYTE *)HL_ADDR_GET(valve_TeamFortressViewport_UpdateSpecatorPanel), (BYTE *)New_TeamFortressViewport_UpdateSpectatorPanel, (int)HL_ADDR_GET(valve_TeamFortressViewport_UpdateSpecatorPanel_DSZ));
	return true;
}

bool Hook_TeamFortressViewport_UpdateSpectatorPanel(void)
{
	static bool firstResult = false;
	static bool firstRun = true;
	if(!firstRun) return firstResult;
	firstRun = false;

	const char *gameDir = pEngfuncs->pfnGetGameDirectory();
	
	if(gameDir)
	{	
		if(!strcmp("tfc",gameDir))
		{
			firstResult = Hook_TeamFortressViewport_UpdateSpectatorPanel_tfc();
		}
		else if(!strcmp("valve",gameDir))
		{
			firstResult = Hook_TeamFortressViewport_UpdateSpectatorPanel_valve();
		}
	}

	return firstResult;
}

REGISTER_CMD_FUNC(disable_specmenu)
{
	if(!Hook_TeamFortressViewport_UpdateSpectatorPanel())
	{
		pEngfuncs->Con_Printf(
			"Error: Hook not installed.\n"
			"Maybe your modification \"%s\" is not supported?\n",
			pEngfuncs->pfnGetGameDirectory()
		);
		return;
	}

	int argc = pEngfuncs->Cmd_Argc();

	if(2 == argc)
	{
		g_DisableSpecMenu = 0 != atoi(pEngfuncs->Cmd_Argv(1));
		return;
	}

	pEngfuncs->Con_Printf(
		PREFIX "disable_specmenu 0|1 (currently: %i)\n",
		g_DisableSpecMenu ? 1 : 0
	);
}