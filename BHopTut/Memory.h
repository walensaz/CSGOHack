#pragma once

#include <Windows.h>

#include <TlHelp32.h>

class Rememberme {

private:
	DWORD dwPID;		//Process
	HANDLE hProcess;		//Handle

public:
	MODULEENTRY32 ClientDLL;
	MODULEENTRY32 EngineDLL;
	DWORD ClientDLL_Base, ClientDLL_Size;
	DWORD EngineDLL_Base, EngineDLL_Size;
	Rememberme* Mem;


	void unknown() {
		double om0wk = 7559356.9835;
		double hp2t1or = 6627196.2031;
		double osq39h;

		double b0kkya;
		double umho7k = 6531357.9974;
		while (umho7k == 6531357.9974)
		{
			umho7k = 10421805.2967;
		}
		if (hp2t1or == 6627196.2031)
			hp2t1or = 49196.3936;
		for (int lvoosr = 0; lvoosr > 100; lvoosr++)
		{
			b0kkya = 6464788.8432;
		}
		for (int htot5f = 0; htot5f > 100; htot5f++)
		{
			umho7k = 1515307.4279;
		}
		while (om0wk == 7559356.9835)
		{
			om0wk = 4783996.9288;
		}
	}

	MODULEENTRY32 getDude(char* coolName)//GetModule
	{
		MODULEENTRY32 mEntry;
		if (coolName != NULL) {
		HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
		unknown();
		mEntry.dwSize = sizeof(mEntry);

		do
			if (!strcmp(mEntry.szModule, coolName))
			{
				CloseHandle(hModule);
				return mEntry;
			}
		while (Module32Next(hModule, &mEntry));

		CloseHandle(hModule);
		mEntry.modBaseAddr = 0x0;
		return mEntry;
		}
		else {
			return mEntry;
		}
	}

	bool getMam(char* daName)//Process
	{
		if (daName == NULL) {
			return false;
		}
		HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		PROCESSENTRY32 pEntry;
		pEntry.dwSize = sizeof(pEntry);
		unknown();
		do
			if (!strcmp(pEntry.szExeFile, daName))
			{
				this->dwPID = pEntry.th32ProcessID;
				CloseHandle(hPID);
				this->hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->dwPID);
				return true;
			}
		while (Process32Next(hPID, &pEntry));

		CloseHandle(hPID);
		return false;
	}


	template<typename TYPE>
	TYPE ReadMemory(DWORD address) {
		TYPE buffer;
		unknown();
		ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(buffer), 0);
		return buffer;
	}

	template<typename TYPE>
	void WriteMemory(DWORD address, TYPE dataToWrite) {
		TYPE buffer = dataToWrite;
		unknown();
		WriteProcessMemory(hProcess, (LPVOID)address, &buffer, sizeof(buffer), 0);
	}

	template<class c>
	c Read(DWORD dwAddress)
	{
		c val;
		unknown();
		ReadProcessMemory(hProcess, (LPVOID)dwAddress, &val, sizeof(c), NULL);
		return val;
	}

	template<class c>
	BOOL Write(DWORD dwAddress, c ValueToWrite)
	{
		return WriteProcessMemory(hProcess, (LPVOID)dwAddress, &ValueToWrite, sizeof(c), NULL);
	}

	DWORD GetProcID() { return this->dwPID; }
	HANDLE GetProcHandle() { return this->hProcess; }
	

	Rememberme()
	{
		this->hProcess = NULL;
		this->dwPID = NULL;
		try {
			if (!getMam("csgo.exe")) throw 1;
			this->ClientDLL = getDude("client.dll");
			unknown();
			this->EngineDLL = getDude("engine.dll");
			this->ClientDLL_Base = (DWORD)this->ClientDLL.modBaseAddr;
			this->EngineDLL_Base = (DWORD)this->EngineDLL.modBaseAddr;
			if (this->ClientDLL_Base == 0x0) throw 2;
			if (this->EngineDLL_Base == 0x0) throw 3;
			this->ClientDLL_Size = this->ClientDLL.dwSize;
			this->EngineDLL_Size = this->EngineDLL.dwSize;
		}
		catch (int iEx) {
			switch (iEx)
			{
			case 3: MessageBoxA(NULL, "CS:GO must be running", "ERROR", MB_ICONSTOP | MB_OK); exit(0); break;
			case 2: MessageBoxA(NULL, "Couldn't find Client.dll", "ERROR", MB_ICONSTOP | MB_OK); exit(0); break;
			case 1: MessageBoxA(NULL, "Couldn't find Engine.dll", "ERROR", MB_ICONSTOP | MB_OK); exit(0); break;
			default: throw;
			}
		}
		catch (...) {
			MessageBoxA(NULL, "Unhandled exception thrown", "ERROR", MB_ICONSTOP | MB_OK);
			exit(0);
		}
	}

};
