#ifndef __HOOKER_C_
#define __HOOKER_C_
#include "..\Patcher\Patcher.h"

/*
	������������� jmp (hookAddress-destinationAddress+5) �� ����� ����������, ������ ����� ���.
	���������� ������������ �����
	hookAddress - ����� ��� ������ ������� ������ - jmp destionationAddress
	������ ������!!!
*/
DLL_EI char* setHook(DWORD hookAddress, DWORD destinationAddress);

DLL_EI DWORD getAddressToOriginalCode(DWORD hookAddress);

#endif