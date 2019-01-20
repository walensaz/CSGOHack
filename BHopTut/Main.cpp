/*#include "Memory.h"
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>
#include "Things.h"

#define FL_ONGROUND (1 << 0)

/*Rememberme* Mem;

// Offsets
#define iTeamthing 0xF0
				
#define Player 0xAA7AB4
#define CrossHair 0xB2A4
#define ListoEnts 0x4A8246C
#define GlowObj 0x4F9F800
//#define GlowInd 0xA310
#define Health 0xFC
#define ViewModel 0x32DC

//End of offsets
int x;
int y;
int z;


bool Run = false;
bool Invis = false;

Vector GetBonePosition(int boneId) {
	Vector bone;
	DWORD boneMatrix = Mem->Read<DWORD>(Mem->ClientDLL_Base + Offsets::);

	bone.x = Mem->Read<float>(boneMatrix + (0x30 * boneId) + 0x0C);
	bone.y = Mem->Read<float>(boneMatrix + (0x30 * boneId) + 0x1C);
	bone.z = Mem->Read<float>(boneMatrix + (0x30 * boneId) + 0x2C);
	return bone;
}

struct thefuck
{
	DWORD dwBase;
	float r;
	float g;
	float b;
	float a;
	uint8_t unk1[16];
	bool m_bRenderWhenOccluded;//rwo
	bool m_bRenderWhenUnoccluded;//rwuo
	bool m_bFullBloom;
	uint8_t unk2[10];
};

void SickBro(thefuck glowObject, int i, DWORD dwGlowPointer, float In_r, float In_g, float In_b) {
	glowObject.r = In_r;
	glowObject.b = In_b;
	glowObject.g = In_g;
	glowObject.a = 1.0f;
	glowObject.m_bRenderWhenOccluded = true;
	glowObject.m_bRenderWhenUnoccluded = false;
	Mem->WriteMemory(dwGlowPointer + i * 0x38, glowObject);
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
	DWORD LocalPlayer_Base = Mem->Read<DWORD>(Mem->ClientDLL_Base + Player);
	int LocalPlayer_inCross = Mem->Read<int>(LocalPlayer_Base + CrossHair);
	int LocalPlayer_Team = Mem->Read<int>(LocalPlayer_Base + iTeamthing);
	

	//DWORD entity = Mem->ReadMemory<DWORD>((Mem->ClientDLL_Base + m_dwEntityList) + (i * 0x10));
	DWORD dwGlowPointer = Mem->ReadMemory<DWORD>(client_dll + GlowObj); //The Adress of the glow object
	int iObjectCount = Mem->ReadMemory<DWORD>(client_dll + GlowObj + 0x4); //Object count

	if (dwGlowPointer != NULL && iObjectCount > 0) {

		unknown();
		for (int i = 0; i < iObjectCount; i++)
		{
			thefuck SickObject = Mem->ReadMemory<thefuck>(dwGlowPointer + i * 0x38);
			DWORD Sick_base = Mem->Read<DWORD>(dwGlowPointer + i * 0x38);
			DWORD Sick_guy = Mem->Read<DWORD>(Mem->ClientDLL_Base + ListoEnts + i * 0x10 - 1);
			int Sick_health = Mem->Read<int>(Sick_base + Health);
			int Sick_team = Mem->Read<int>(Sick_base + iTeamthing);
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



struct GlowObjectDefinition_t
{
	void* pEntity;
	float r;
	float g;
	float b;
	float a;
	uint8_t unk1[16];
	bool m_bRenderWhenOccluded;
	bool m_bRenderWhenUnoccluded;
	bool m_bFullBloom;
	uint8_t unk2[10];
};

void theinvis()
{
	while (Invis) {
		unknown();
		justgo(Mem->ClientDLL_Base,32);
		Sleep(50);
	}

}

void Running()
{	
	unknown();
	while (Run)
	{
		//Retrieve player information
		unknown();
		DWORD myGuy = Mem->Read<DWORD>(Mem->ClientDLL_Base + Player);
		int inTheCross = Mem->Read<int>(myGuy + CrossHair);
		int teamythingy = Mem->Read<int>(myGuy + iTeamthing);
		DWORD theotherguy = Mem->Read<DWORD>(Mem->ClientDLL_Base + ListoEnts + ((inTheCross - 1) * 0x10));
		int otherteamy = Mem->Read<int>(theotherguy + iTeamthing);
		bool dead = Mem->Read<bool>(theotherguy + 0xE9);
		unknown();
		if ((inTheCross > 0 && inTheCross <= 64) &&(otherteamy != teamythingy))
		{
			/*POINT cursorPos;
			GetCursorPos(&cursorPos);
			int x = cursorPos.x;
			int y = cursorPos.y;
			// can customize the delays
			mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
			mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
			Sleep(100);
		}


		Sleep(1);
		
	}

}

Vector Player::GetEyePosition()
{
	if (eyePosition.IsEmpty()) {
		eyePosition = GetPosition();
		eyePosition.z += Mem->Read<Vector>(BaseAddr + Offsets::viewOffset).z;
	}
	return eyePosition;
}

void AimAtPos(float x, float y)
{
	//By fredaikis
	float ScreenCenterX = (this.Width / 2);
	float ScreenCenterY = (this.Height / 2);
	float TargetX = 0;
	float TargetY = 0;
	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}
	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}
	if (!smooth)
	{
		mouse_event(0x0001, (uint)(TargetX), (uint)(TargetY), NULL, NULLPTR);
		return;
	}
	TargetX /= 10;
	TargetY /= 10;
	if (Math.Abs(TargetX) < 1)
	{
		if (TargetX > 0)
		{
			TargetX = 1;
		}
		if (TargetX < 0)
		{
			TargetX = -1;
		}
	}
	if (Math.Abs(TargetY) < 1)
	{
		if (TargetY > 0)
		{
			TargetY = 1;
		}
		if (TargetY < 0)
		{
			TargetY = -1;
		}
	}
	mouse_event(0x0001, (uint)TargetX, (uint)TargetY, NULL, NULLPTR);
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


		Sleep(50);
		
	}
}

int main()
{
	x = 15 * 20 + 15;
	y = 20 * 15 * 20;
	if (x > 10 && y > 10) {
	Mem = new Rememberme(); //Execute the constructor code
	std::cout << "Skype.exe has been started!" << std::endl;
	//MY_ReadInformation(Mem->ClientDLL_Base);
	play();
	}
	delete Mem; //Don't forget to delete MemoryManager pointer, so it executes destructor and closes correctly the handle
	return 0;
}


*/

