#ifndef __HOOKER_C_
#define __HOOKER_C_
#include "..\Patcher\Patcher.h"

/*
	������������� jmp destinationAddress �� ����� ����������, ������ ����� ���.
	���������� ������������ �����
	hookAddress - ����� ��� ������ ������� ������ - jmp destionationAddress
	������ ������!!!
*/
DLL_EI char* setHook(DWORD hookAddress, DWORD destinationAddress);

/*
	������ ���������� hookAddress + 5
	=)
*/
DLL_EI DWORD getAddressToOriginalCode(DWORD hookAddress);

#endif