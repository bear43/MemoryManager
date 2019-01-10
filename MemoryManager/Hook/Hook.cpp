#include "Hook.h"

void Hook::releaseOriginalBytes()
{
	if (originalBytes != nullptr)
	{
		delete originalBytes;
		originalBytes = nullptr;
	}
}

DLL_EI Hook::Hook(DWORD hookAddress, DWORD userFunctionAddress) : hookAddress(hookAddress), userFunctionAddress(userFunctionAddress)
{}

DLL_EI Hook::Hook(DWORD hookAddress, void * userFunctionAddress) : Hook(hookAddress, (DWORD)userFunctionAddress)
{}

DLL_EI void Hook::set()
{
	if (!hooked)
	{
		originalBytes = setHook(hookAddress, userFunctionAddress);
		hooked = true;
	}
}

DLL_EI void Hook::unset()
{
	if (hooked)
	{
		patchBytes(hookAddress, originalBytes, 5);
		releaseOriginalBytes();
		hooked = false;
	}
}

DLL_EI Hook::~Hook()
{
	//Чистим память после себя, если, конечно же, мы её загрязняли
	releaseOriginalBytes();
}
