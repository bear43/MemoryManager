#include "Hooker.h"

/*
	Устанавливает jmp destinationAddress на адрес инструкции, откуда нужен хук.
	Возвращает оригинальные байты
	hookAddress - Адрес для замены байтами прыжка - jmp destionationAddress
	Чистим память!!!
*/
DLL_EI char* setHook(DWORD hookAddress, DWORD destinationAddress)
{
	char* originalBytes = getBytes(hookAddress, 5);
	/*
		jmp destinationAddress
		E9 AA BB CC DD
	*/
	const char newByte[] = { 0xE9, destinationAddress >> 24, (destinationAddress >> 16) & 0xFF, (destinationAddress >> 8) & 0xFF, destinationAddress & 0xFF };
	patchBytes(hookAddress, newByte, 5);
	return originalBytes;
}

/*
	Просто возвращает hookAddress + 5 
	=)
*/
DLL_EI DWORD getAddressToOriginalCode(DWORD hookAddress)
{
	return hookAddress + 5;
}