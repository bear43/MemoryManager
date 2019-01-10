#include "Patcher.h"

DWORD oldProtect;

/*
	destinationAddress - ����� ��� ��������� �������
	newProtect - ����� ����� ������� �����?
	bytesCount - �� ������� ���� ���������������� ���������
*/
DLL_EI void setAddressProtection(DWORD destinationAddress, DWORD newProtect, unsigned int bytesCount)
{
	VirtualProtect((LPVOID)destinationAddress, bytesCount, newProtect, &oldProtect);
}

/*
	��������������� ����� ������� ����� ���������� ������ setAddressProtection.
	�������� setAddressProtection. oldProtect ����� ���������� ����� �����.
	destinationAddress - ����� ��� ��������� �������
	bytesCount - �� ������� ���� ���������������� ���������
*/
DLL_EI void restoreLastProtection(DWORD destinationAddress, unsigned int bytesCount)
{
	setAddressProtection(destinationAddress, oldProtect, bytesCount);
}

/*
	���������� ��������� ������ ������� ������ �� �����!!!
	sourceAddress - ������ ����� �����
	count - ���������� ���� ��� ������
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
	destinationAddress - ����� ��� ����� ����
	newBytes - ����� �����
	size - ���������� ���� ��� �����(������ newBytes)
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
