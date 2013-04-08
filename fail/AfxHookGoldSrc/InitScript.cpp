#include "stdafx.h"

// Copyright (c) by advancedfx.org
//
// Last changes:
// 2011-01-03 dominik.matrixstorm.com
///
// First changes:
// 2010-03-17 by dominik.matrixstorm.com

#include "InitScript.h"

#include <shared/vcpp/AfxAddr.h>
#include <shared/vcpp/Expressions/Expressions.h>

#include "hooks/HookHw.h"
#include "AfxGoldSrcComClient.h"
#include "Xpress.h"
#include "cmdregister.h"

#include <string>


using namespace Afx;
using namespace Afx::Expressions;


#define INIT_SCRIPT_FILE "AfxHookGoldSrc_init.x.txt"
#define SCRIPT_FOLDER "scripts\\"
#define DLL_NAME	"AfxHookGoldSrc.dll"


class AddressProperty : public FunctionHost
{
public:
	AddressProperty(AfxAddr * addr)
	: m_Addr(addr)
	{

	}

	IntT GetAddr (Arguments args)
	{
		return *m_Addr;
	}

	VoidT SetAddr (Arguments args) {
		*m_Addr = (AfxAddr)args[0].Int->EvalInt();
	}

private:
	AfxAddr * m_Addr;
};


class GoldSrcAddresses
{
public:
	GoldSrcAddresses()
	{
#ifdef _DEBUG
		MessageBox(0, "GoldSrcAddresses", "MDT_DEBUG", MB_OK|MB_ICONINFORMATION);
#endif

		m_Bubble = IBubble::New();
		m_Bubble->Ref()->AddRef();

		IBubble::AddStandardFunctions(m_Bubble);
		m_Bubble->Add(StringValue::CopyFrom("OnHwDllLoaded"), (m_OnHwDllLoaded = new VoidEvent(m_Bubble->Compiler())));
		m_Bubble->Add(StringValue::CopyFrom("OnClientDllLoaded"), (m_OnClientDllLoaded = new VoidEvent(m_Bubble->Compiler())));
	}

	~GoldSrcAddresses()
	{
		m_Bubble->Ref()->Release();
	}

	void BubbleAddresses()
	{
		for(unsigned int ui = 0; ui < AfxAddr_Debug_GetCount(); ui++)
		{
			AfxAddr addr;
			char const * name;

			if(AfxAddr_Debug_GetAt(ui, addr, name))
			{
				AfxAddr * padr = AfxAddr_GetByName(name);

				if(padr)
				{
					AddressProperty * adrProp = new AddressProperty(padr);
					adrProp->AddRef();

					m_Bubble->Add(StringValue::CopyFrom(name), Delegate::New(adrProp, (IntFunction)&AddressProperty::GetAddr, ArgumentsT::New()));
					m_Bubble->Add(StringValue::CopyFrom(name), Delegate::New(adrProp, (VoidFunction)&AddressProperty::SetAddr, ArgumentsT::New(1, A_Int)));

					adrProp->Release();
				}
			}
		}
	}

	bool BubbleCode(char const * code)
	{
		ICompiled * compiled = m_Bubble->Compile(StringValue::CopyFrom(code));

		compiled->Ref()->AddRef();

		bool bOk =
			0 != compiled->GetBool()
		;

		if(bOk) bOk = compiled->GetBool()->EvalBool();

		compiled->Ref()->Release();

		return bOk;
	}

	void OnHwDllLoaded()
	{
		m_OnHwDllLoaded->EvalVoid();
	}

	void OnClientDllLoaded()
	{
		m_OnClientDllLoaded->EvalVoid();
	}

private:
	IBubble * m_Bubble;
	VoidEvent * m_OnHwDllLoaded;
	VoidEvent * m_OnClientDllLoaded;

} g_GoldSrcAddresses;


void InitEvent_OnHwDllLoaded()
{
	g_GoldSrcAddresses.OnHwDllLoaded();
}


void InitEvent_OnClientDllLoaded()
{
	g_GoldSrcAddresses.OnClientDllLoaded();
}

std::string g_strFolder;

bool RunInitScript()
{
	char hookPath[1025];
	bool bCfgres = false;
	HMODULE hHookDll = GetModuleHandle(DLL_NAME);

	hookPath[0]=NULL;

	g_GoldSrcAddresses.BubbleAddresses();
	
	if (hHookDll)
	{
		GetModuleFileName(hHookDll, hookPath, sizeof(hookPath)/sizeof(*hookPath) -1);

		g_strFolder = (hookPath);
		size_t fp = g_strFolder.find_last_of('\\');
		if(std::string::npos != fp)
		{
			g_strFolder.resize(fp+1);
		}

		g_strFolder += SCRIPT_FOLDER;

		std::string scriptFile(g_strFolder);
		scriptFile += INIT_SCRIPT_FILE;

		std::string code("(ceval (stringFromFile (s ");

		for(std::string::iterator it = scriptFile.begin(); it != scriptFile.end(); it++)
		{
			char val = (*it);

			switch(val)
			{
			case '\\':
			case '(':
			case ')':
				code += "\\";
				code += val;
				break;
			default:
				code += val;
				break;
			}
		}

		code += ")))";

		bCfgres = g_GoldSrcAddresses.BubbleCode(code.c_str());

		if(!bCfgres) {
			string strError;
			strError += "Failed to load:\n\"" +scriptFile +"\".";

			MessageBox(0, strError.c_str(), "MDT_ERROR",MB_OK|MB_ICONHAND);
		}
	}

	return bCfgres;
}

_REGISTER_CMD("xexec", xexec_cmd)
void xexec_cmd()
{
	if(2 == pEngfuncs->Cmd_Argc())
	{
		std::string strCode;

		std::string scriptFile(g_strFolder);
		scriptFile += pEngfuncs->Cmd_Argv(1);

		std::string code("(ceval (stringFromFile (s ");

		for(std::string::iterator it = scriptFile.begin(); it != scriptFile.end(); it++)
		{
			char val = (*it);

			switch(val)
			{
			case '\\':
			case '(':
			case ')':
				code += "\\";
				code += val;
				break;
			default:
				code += val;
				break;
			}
		}

		code += ")))";

		pEngfuncs->Con_Printf("%s\n", code.c_str());

		xpress_execute(code.c_str());

		return;
	}

	pEngfuncs->Con_Printf(
		"Compiles a Xpress file to a Void function and evaluates it (upon success)."
		"Usage: xpress_exec <scriptName.x.txt>\n"
	);
}