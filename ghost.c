#include "ghost.h"

BYTE *ReadDataFromFile(WCHAR* FileName) {
	HANDLE file = NULL;
	BOOL  result = FALSE;
	DWORD read = 0;
	file = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE) {
		printf("erro ao abrir o arquivo");
	}
	DWORD filesize = GetFileSize(file, 0);
	if (filesize == INVALID_FILE_SIZE) {
		printf("errp size");
		return NULL;
	} BYTE* FileContents = (BYTE*)malloc(filesize);
	ZeroMemory(FileContents, filesize);
	result = ReadFile(file, FileContents, filesize, &read,0);
	if (result == FALSE) {
		printf("errp ap lero arquivo");
		return(NULL);
	}
	CloseHandle(file);
	return(FileContents);
}

DWORD SizeFile(WCHAR *FileName) {
	HANDLE file = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD fileSize = GetFileSize(file, 0);
	if (fileSize == INVALID_FILE_SIZE) {
		printf("size");
		return NULL;
	}

	CloseHandle(file);
	return fileSize;
}
BOOL ReadRemotePEB(HANDLE proc, PPROCESS_BASIC_INFORMATION pi, OUT PPEB peb_copy) {
	memset(peb_copy, 0, sizeof(PEB));
	PPEB remote_peb_addr = pi->PebBaseAddress;
	HINSTANCE hinstStub = GetModuleHandle("ntdll.dll");

	_NtReadVirtualMemory NtReadVirtualMemory= (_NtReadVirtualMemory)GetProcAddress(hinstStub, "NtReadVirtualMemory");
 NTSTATUS sta=	NtReadVirtualMemory(proc, remote_peb_addr, peb_copy, sizeof(PEB), NULL);
if(sta!= STATUS_SUCCESS){

	return(!TRUE);
}
return(TRUE);

}