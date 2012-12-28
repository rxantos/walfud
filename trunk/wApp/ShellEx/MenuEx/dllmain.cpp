// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "MenuEx_i.h"
#include "dllmain.h"

CMenuExModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// 2. Save the module address.
	_AtlModule.SetModuleInstance(hInstance);
	return _AtlModule.DllMain(dwReason, lpReserved); 
}

CMenuExModule::CMenuExModule()
	: m_instance(NULL)
{}
CMenuExModule::~CMenuExModule()
{}

// Interface.
HINSTANCE CMenuExModule::GetModuleInstance() const
{ return m_instance; }
void CMenuExModule::SetModuleInstance(HINSTANCE instance)
{ m_instance = instance; }