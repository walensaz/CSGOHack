#include "Memory.h"
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>
#include "Things.h"
#include "Offsets.h"
#include "Utils.h"

#define FL_ONGROUND (1 << 0)

//End of offsets
int x;
int y;
int z;

bool Run = false;
bool Invis = false;
bool bot = false;

Vector GetBonePosition(int boneId) {
	Vector bone;
	DWORD boneMatrix = Mem->Read<DWORD>(Mem->ClientDLL_Base + Offsets::m_dwBoneMatrix);
	bone.x = Mem->Read<float>(boneMatrix + (0x30 * boneId) + 0x0C);
	bone.y = Mem->Read<float>(boneMatrix + (0x30 * boneId) + 0x1C);
	bone.z = Mem->Read<float>(boneMatrix + (0x30 * boneId) + 0x2C);
	return bone;
}

Vector GetBonePositionOther(DWORD player, int boneId) {
	Vector bone;
	DWORD boneMatrix = Mem->Read<DWORD>(player + Offsets::m_dwBoneMatrix);
	bone.x = Mem->Read<float>(boneMatrix + (0x30 * boneId) + 0x0C);
	bone.y = Mem->Read<float>(boneMatrix + (0x30 * boneId) + 0x1C);
	bone.z = Mem->Read<float>(boneMatrix + (0x30 * boneId) + 0x2C);
	return bone;
}



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

void justgo(DWORD client_dll, int i) {
	unknown();
	DWORD LocalPlayer_Base = Mem->Read<DWORD>(Mem->ClientDLL_Base + Offsets::m_dwLocalPlayer);
	int LocalPlayer_inCross = Mem->Read<int>(LocalPlayer_Base + Offsets::m_iCrossHairID);
	int LocalPlayer_Team = Mem->Read<int>(LocalPlayer_Base + Offsets::m_iTeamNum);

	unknown();
	//DWORD entity = Mem->ReadMemory<DWORD>((Mem->ClientDLL_Base + m_dwEntityList) + (i * 0x10));
	DWORD dwGlowPointer = Mem->ReadMemory<DWORD>(client_dll + Offsets::m_dwGlowObject); //The Adress of the glow object
	int iObjectCount = Mem->ReadMemory<DWORD>(client_dll + Offsets::m_dwGlowObject + 0x4); //Object count
	unknown();
	if (dwGlowPointer != NULL && iObjectCount > 0) {

		unknown();
		for (int i = 0; i < iObjectCount; i++)
		{
			thefuck SickObject = Mem->ReadMemory<thefuck>(dwGlowPointer + i * 0x38);
			DWORD Sick_base = Mem->Read<DWORD>(dwGlowPointer + i * 0x38);
			DWORD Sick_guy = Mem->Read<DWORD>(Mem->ClientDLL_Base + Offsets::m_dwEntityList + i * 0x10 - 1);
			int Sick_health = Mem->Read<int>(Sick_base + Offsets::m_iHealth);
			int Sick_team = Mem->Read<int>(Sick_base + Offsets::m_iTeamNum);
			bool Sick_dormant = Mem->Read<bool>(Sick_base + 0xE9);
			//if (Sick_base == Sick_guy) {
			if (SickObject.dwBase != NULL) {
				if (Sick_team == LocalPlayer_Team) {
					if (!Sick_dormant) {
						SickBro(SickObject, i, dwGlowPointer, 0.0f, 5.0f, 95.0f); //r,g,b
					}
				}
				else if (Sick_team != 0) {
					if (!Sick_dormant) {
						if (Sick_health <= 30) {
							SickBro(SickObject, i, dwGlowPointer, 155.0f, 0.0f, 155.0f); //r,g,b
						}
						else {
							SickBro(SickObject, i, dwGlowPointer, 95.0f, 0.0f, 0.0f);
						}
					}
				}

				//}
			}
		}
	}
}


void theinvis()
{
	while (Invis) {
		unknown();
		justgo(Mem->ClientDLL_Base, 32);
		Sleep(50);
	}
}

void Running()
{
	unknown();
	while (Run)
	{
		//Retrieve player information
		DWORD myGuy = Mem->Read<DWORD>(Mem->ClientDLL_Base + Offsets::m_dwLocalPlayer);
		int inTheCross = Mem->Read<int>(myGuy + Offsets::m_iCrossHairID);
		unknown();
		int teamythingy = Mem->Read<int>(myGuy + Offsets::m_iTeamNum);
		unknown();
		DWORD theotherguy = Mem->Read<DWORD>(Mem->ClientDLL_Base + Offsets::m_dwEntityList + ((inTheCross - 1) * 0x10));
		int otherteamy = Mem->Read<int>(theotherguy + Offsets::m_iTeamNum);
		unknown();
		bool dead = Mem->Read<bool>(theotherguy + 0xE9);
		if ((inTheCross > 0 && inTheCross <= 64) && (otherteamy != teamythingy))
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
			mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
			Sleep(100);
		}


		Sleep(3);

	}

}

void Aimbot()
{
	int count = 0;
	while (bot) {
		Vector bestAimAngle;
		float bestFov = 75;
		DWORD local = Mem->Read<DWORD>(Mem->ClientDLL_Base + Offsets::m_dwLocalPlayer);
		for (int i = 0; i < 64; i++) {
			DWORD player = Mem->Read<DWORD>(Mem->ClientDLL_Base + Offsets::m_dwEntityList + ((i - 1) * 0x10));
			if (Mem->Read<int>(player + Offsets::m_iHealth) <= 0)
				continue;
			if (Mem->Read<int>(player + Offsets::m_iTeamNum) == Mem->Read<int>(local + Offsets::m_iTeamNum))
				continue;
			Vector headPosition = GetBonePositionOther(player, 8);
			if (headPosition.IsEmpty())
				continue;
			Vector aimAngle;
			Utils::CalcAngle(GetEyePosition(), headPosition, aimAngle);
			float fov = Utils::GetFov(GetViewAngles(), aimAngle);
			if (fov < bestFov) {
				bestAimAngle = aimAngle;
				bestFov = fov;
			}
		}
		if (!bestAimAngle.IsEmpty()) {
			Vector newViewAngles;
			Utils::Clamp(bestAimAngle);
			Vector delta = GetViewAngles() - bestAimAngle;
			Utils::Clamp(delta);
			newViewAngles = GetViewAngles();
			if (Utils::Clamp(newViewAngles))
				SetViewAngles(newViewAngles);
			if (count != 1000) {
				count++;
			}
			else {
				std::cout << GetEyePosition().x << std::endl;
				std::cout << newViewAngles.x << std::endl;
				std::cout << "Best aim angle:" << std::endl;
				std::cout << bestAimAngle.x << std::endl;
				std::cout << bestAimAngle.z << std::endl;
				std::cout << bestAimAngle.y << std::endl;
				count = 0;
			}
		}
	}
	Sleep(5);
}

void play() {
	while (true) {

		if (GetAsyncKeyState(VK_F4)) {
			Run = !Run;
			if (Run) { std::cout << "Running now ON" << std::endl; CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Running, 0, 0, 0); }
			else {
				std::cout << "Running now OFF" << std::endl;
			}
			Sleep(500);

		}
		else if (GetAsyncKeyState(VK_F2)) {
			Invis = !Invis;
			if (Invis) { std::cout << "Invis now ON" << std::endl; CreateThread(0, 0, (LPTHREAD_START_ROUTINE)theinvis, 0, 0, 0); }
			else {
				std::cout << "Invis now OFF" << std::endl;
			}
			Sleep(500);
		}
		/*else if () {
			bot = !bot;
			if (bot) { std::cout << "aim now ON" << std::endl; CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Aimbot, 0, 0, 0); }
			else {
				std::cout << "aim now OFF" << std::endl;
			}
			Sleep(500);
		}*/


		Sleep(50);

	}
}

int main()
{
	Mem = new Rememberme(); //Execute the constructor code
	std::cout << "Skype.exe has been started!" << std::endl;
	//MY_ReadInformation(Mem->ClientDLL_Base);
	play();
	delete Mem; //Don't forget to delete MemoryManager pointer, so it executes destructor and closes correctly the handle
	return 0;
}




