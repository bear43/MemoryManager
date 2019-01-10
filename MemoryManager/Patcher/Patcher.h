#ifndef __PATCHER_C__
#define __PATCHER_C__
#include <Windows.h>

#define __DLL__

#ifdef __DLL__
#define DLL_EI __declspec(dllexport)
#else
#define DLL_EI __declspec(dllimport)
#endif

/*
	destinationAddress - ����� ��� ��������� �������
	newProtect - ����� ����� ������� �����?
	bytesCount - �� ������� ���� ���������������� ���������
*/
DLL_EI void setAddressProtection(DWORD destinationAddress, DWORD newProtect, unsigned int bytesCount);

/*
	��������������� ����� ������� ����� ���������� ������ setAddressProtection.
	�������� setAddressProtection. oldProtect ����� ���������� ����� �����.
	destinationAddress - ����� ��� ��������� �������
	bytesCount - �� ������� ���� ���������������� ���������
*/
DLL_EI void restoreLastProtection(DWORD destinationAddress, unsigned int bytesCount);

/*
	���������� ��������� ������ ������� ������ �� �����!!!
	sourceAddress - ������ ����� �����
	count - ���������� ���� ��� ������
*/
DLL_EI char* getBytes(DWORD sourceAddress, unsigned int count);

/*
	destinationAddress - ����� ��� ����� ����
	newBytes - ����� �����
	size - ���������� ���� ��� �����(������ newBytes)
*/
DLL_EI void patchBytes(DWORD destinationAddress, const char newBytes[], unsigned int size);

#endif