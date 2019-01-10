#include "Patcher.h"

DWORD oldProtect;

/*
	destinationAddress - адрес дл€ установки доступа
	newProtect - какой режим доступа будет?
	bytesCount - на сколько байт распростран€етс€ установка
*/
DLL_EI void setAddressProtection(DWORD destinationAddress, DWORD newProtect, unsigned int bytesCount)
{
	VirtualProtect((LPVOID)destinationAddress, bytesCount, newProtect, &oldProtect);
}

/*
	¬осстанавливает флаги доступа после последнего вызова setAddressProtection.
	¬ызывает setAddressProtection. oldProtect также измен€етс€ ввиду этого.
	destinationAddress - адрес дл€ установки доступа
	bytesCount - на сколько байт распростран€етс€ установка
*/
DLL_EI void restoreLastProtection(DWORD destinationAddress, unsigned int bytesCount)
{
	setAddressProtection(destinationAddress, oldProtect, bytesCount);
}

/*
	¬ызывающа€ программа должна чистить пам€ть за собой!!!
	sourceAddress - откуда берем байты
	count - количество байт дл€ чтени€
*/
DLL_EI char* getBytes(DWORD sourceAddress, unsigned int count)
{
	setAddressProtection(sourceAddress, PAGE_EXECUTE_READWRITE, count);
	char* byteArray = malloc(count+1);
	ZeroMemory(byteArray, count);
	for (int offset = 0; offset < count; offset++)
	{
		byteArray[offset] = *(char*)(sourceAddress + offset);
	}
	restoreLastProtection(sourceAddress, count);
	byteArray[count] = '\0';
	return byteArray;
}

/*
	destinationAddress - адрес дл€ патча байт
	newBytes - новые байты
	size - количество байт дл€ патча(размер newBytes)
*/
DLL_EI void patchBytes(DWORD destinationAddress, const char newBytes[], unsigned int size)
{
	setAddressProtection(destinationAddress, PAGE_EXECUTE_READWRITE, size);
	for (int offset = 0; offset < size; offset++)
	{
		*((char*)(destinationAddress+offset)) = newBytes[offset];
	}
	restoreLastProtection(destinationAddress, size);
}
