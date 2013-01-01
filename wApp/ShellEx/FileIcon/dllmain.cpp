// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "FileIcon_i.h"
#include "dllmain.h"

CFileIconModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	_AtlModule.SetModuleInstance(hInstance);
	return _AtlModule.DllMain(dwReason, lpReserved); 
}

CFileIconModule::CFileIconModule()
	: m_instance(nullptr)
{}
CFileIconModule::~CFileIconModule()
{}

// Interface.
HINSTANCE CFileIconModule::GetModuleInstance() const
{ return m_instance; }
void CFileIconModule::SetModuleInstance(HINSTANCE instance)
{ m_instance = instance; }