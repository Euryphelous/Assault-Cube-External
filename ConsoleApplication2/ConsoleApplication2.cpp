﻿// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include  "stdafx.h"
#include  <iostream>
#include  <Windows.h>
#include  <tlhelp32.h>
#include  "Offsets.h"


#pragma region CommentLine
//This is a simple external C++ hack for Assault Cube.
//Author: Euryphelous
//......................................
#pragma endregion


//for base adress
uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

#pragma region Functions
void PlayerInfo(HANDLE handle)
{
	//Name
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	ReadProcessMemory(handle, (LPVOID*)(lAdress + NAME), &sName, sizeof(sName), NULL);
	std::cout << std::endl << "Name: " << sName;
	//Client Number
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	ReadProcessMemory(handle, (LPVOID*)(lAdress + CM), &sCM, sizeof(sCM), NULL);
	std::cout << std::endl << "Client Number: " << sCM;
	//HP
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	ReadProcessMemory(handle, (LPVOID*)(lAdress + HP), &sHP, sizeof(sHP), NULL);
	std::cout << std::endl << "HP: " << sHP;
	//Armor
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	ReadProcessMemory(handle, (LPVOID*)(lAdress + AP), &sAP, sizeof(sAP), NULL);
	std::cout << std::endl << "Armor :" << sAP;
	//X
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	ReadProcessMemory(handle, (LPVOID*)(lAdress + X), &sX, sizeof(sX), NULL);
	std::cout << std::endl << "X :" << sX;
	//Y
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	ReadProcessMemory(handle, (LPVOID*)(lAdress + Y), &sY, sizeof(sY), NULL);
	std::cout << std::endl << "Y :" << sY;
	//Z
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	ReadProcessMemory(handle, (LPVOID*)(lAdress + Z), &sZ, sizeof(sZ), NULL);
	std::cout << std::endl << "Z :" << sZ;
	//Grenade
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	ReadProcessMemory(handle, (LPVOID*)(lAdress + Grenade), &sGrenade, sizeof(sGrenade), NULL);
	std::cout << std::endl << "Grenade :" << sGrenade;
	//Current Weapon
	//Get the base
	assault_cube_base = GetModuleBaseAddress(procID, L"ac_client.exe");
	//Calculate
	DWORD ItemsBase = assault_cube_base + 0x0010FC84;
	//Add offsets + Read
	ReadProcessMemory(handle, (void*)ItemsBase, &baseAdress, sizeof(baseAdress), NULL);
	ReadProcessMemory(handle, (void*)(baseAdress + 0x0), &firstAdress, sizeof(firstAdress), NULL);
	ReadProcessMemory(handle, (void*)(firstAdress + 0x28C), &secondAdress, sizeof(secondAdress), NULL);
	if (secondAdress == 0)
	{
		std::cout << std::endl << "Current Weapon: Knife";
	}
	if (secondAdress == 1)
	{
		std::cout << std::endl << "Current Weapon: Pistol";
	}
	if (secondAdress == 2)
	{
		std::cout << std::endl << "Current Weapon: M&A Carbine";
	}
	if (secondAdress == 3)
	{
		std::cout << std::endl << "Current Weapon: Combat Shotgun";
	}
	if (secondAdress == 4)
	{
		std::cout << std::endl << "Current Weapon: Submachine";
	}
	if (secondAdress == 5)
	{
		std::cout << std::endl << "Current Weapon: Sniper Rifle";
	}
	if (secondAdress == 6)
	{
		std::cout << std::endl << "Current Weapon: MTP-57";
	}
	if (secondAdress == 8)
	{
		std::cout << std::endl << "Current Weapon: Grenade";
	}
	if (secondAdress == 9)
	{
		std::cout << std::endl << "Current Weapon: Dual Gun";
	}
}

void InfinityHP(HANDLE handle)
{
	//Read
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	//Local Player + HP offset
	lAdress += 0xF8;
	//Write
	newHP = 1337;
	WriteProcessMemory(handle, (LPVOID*)lAdress, &newHP, sizeof(newHP), NULL);
}

void NormalHP(HANDLE handle)
{
	//Read
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	//Local Player + HP offset
	lAdress += 0xF8;
	//Write
	newHP = 100;
	WriteProcessMemory(handle, (LPVOID*)lAdress, &newHP, sizeof(newHP), NULL);
}

void InfinityAP(HANDLE handle)
{
	//Read
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	//Local Player + AP offset
	lAdress += 0xFC;
	//Write
	newAP = 1337;
	WriteProcessMemory(handle, (LPVOID*)lAdress, &newAP, sizeof(newAP), NULL);
}

void InfinityGrenade(HANDLE handle)
{
	//Read
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	//Local Player + Grenade offset
	lAdress += 0x158;
	//Write
	newGrenade = 1337;
	WriteProcessMemory(handle, (LPVOID*)lAdress, &newGrenade, sizeof(newGrenade), NULL);
}

void EditMode(HANDLE handle)
{
	//Items
	//Get the base
	assault_cube_base = GetModuleBaseAddress(procID, L"ac_client.exe");
	//Calculate
	DWORD ItemsBase = assault_cube_base + 0x0003D3A4;
	//Read
	ReadProcessMemory(handle, (void*)ItemsBase, &baseAdress, sizeof(baseAdress), NULL);
	//Add Offset
	baseAdress += 0x108;
	//new
	newBase = 16777472;
	WriteProcessMemory(handle, (void*)baseAdress, &newBase, sizeof(newBase), NULL);
	//Ghost
	//Get the base
	assault_cube_base = GetModuleBaseAddress(procID, L"ac_client.exe");
	//Calculate
	DWORD GhostBase = assault_cube_base + 0x00109B74;
	//Read
	ReadProcessMemory(handle, (void*)GhostBase, &baseAdress, sizeof(baseAdress), NULL);
	//Add Offset
	baseAdress += 0x80;
	//new
	newBase = 262144;
	WriteProcessMemory(handle, (void*)baseAdress, &newBase, sizeof(newBase), NULL);
}

void SmallPlayer(HANDLE handle)
{
	//Read
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	//Local Player + Small Player offset
	lAdress += 0x5C;
	//Write
	newSmallPlayer = 1065353216;
	WriteProcessMemory(handle, (LPVOID*)lAdress, &newSmallPlayer, sizeof(newSmallPlayer), NULL);
}

void TeleportXCoord(HANDLE handle)
{
	//Read
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	//Local Player + X offset
	lAdress += 0x34;
	//Write
	newTeleportX = TeleportX;
	WriteProcessMemory(handle, (LPVOID*)lAdress, &newTeleportX, sizeof(newTeleportX), NULL);
}

void TeleportYCoord(HANDLE handle)
{
	//Read
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	//Local Player + Y offset
	lAdress += 0x38;
	//Write
	newTeleportY = TeleportY;
	WriteProcessMemory(handle, (LPVOID*)lAdress, &newTeleportY, sizeof(newTeleportY), NULL);
}

void TeleportZCoord(HANDLE handle)
{
	//Read
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	//Local Player + Z offset
	lAdress += 0x3C;
	//Write
	newTeleportZ = TeleportZ;
	WriteProcessMemory(handle, (LPVOID*)lAdress, &newTeleportZ, sizeof(newTeleportZ), NULL);
}

void FlyHack(HANDLE handle)
{
	//Read
	ReadProcessMemory(handle, (LPVOID*)LOCAL_PLAYER, &lAdress, sizeof(lAdress), NULL);
	//Local Player + Fly offset
	lAdress += FLY;
	//Write
	newFly = 5;
	WriteProcessMemory(handle, (LPVOID*)lAdress, &newFly, sizeof(newFly), NULL);
}
#pragma endregion

int main()
{ 
	//Find target and stuff
	HWND hwnd = FindWindow(NULL, L"AssaultCube");
	if (!hwnd)
	{
		std::cout << "I can't find AssaultCube. Try again." << std::endl << std::endl;
		system("pause");
		return 0;
	}
	else
	{
		DWORD target = GetWindowThreadProcessId(hwnd, &procID);
		if (!target)
		{
			std::cout << "I can't find procces id. Try again." << std::endl << std::endl;
			system("pause");
			return 0;
		}
		else
		{
			std::cout << "Successful. Press SPACE to continue." << std::endl << std::endl;
			//Getting handle and open access
			HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, 0, procID);
			//Main Loop
		 while (true)
		 { 
			if (GetAsyncKeyState((VK_SPACE)) && space == false)
			{
				space = true;
				system("cls");
				std::cout << "Welcome to the simple Assault Cube hack.";
				Sleep(1000);
				std::cout << std::endl << "You are at the player info screen, please press SPACE again to show available features." << std::endl << std::endl;
				Sleep(3000);
			    returnPlayerInfo:
				while (true)
				{
				if (GetAsyncKeyState(VK_SPACE) && space_2 == false)
				{
					hackEnabled = true;
					space_2 = true;
					space_3 = true;
				while(hackEnabled == true)
				{ 
					system("cls");
					std::cout << "List of available features." << std::endl << std::endl << "Numpad 0 - Exit" << std::endl << "Numpad 1 - Infinity HP" << std::endl << "Numpad 2 - Infinity AP" << std::endl << "Numpad 3 - Infinity Grenade" << std::endl << "Numpad 4 - Edit Mode" << std::endl << "Numpad 5 - Small Player" << std::endl << "Numpad 6 - Teleport" << std::endl << "Numpad 7 - Fly Hack" << std::endl << "Numpad 8 - Info Screen";
					if (GetAsyncKeyState(VK_NUMPAD0))
					{
						CloseHandle(handle);
						return 0;
					}
					if (GetAsyncKeyState(VK_NUMPAD1))
					{
						InfinityHP(handle);
					}
					if (GetAsyncKeyState(VK_NUMPAD2))
					{
						InfinityAP(handle);
					}
					if (GetAsyncKeyState(VK_NUMPAD3))
					{
						InfinityGrenade(handle);
					}
					if (GetAsyncKeyState(VK_NUMPAD4))
					{
						EditMode(handle);
					}
					if (GetAsyncKeyState(VK_NUMPAD5))
					{
						SmallPlayer(handle);
					}
					if (GetAsyncKeyState(VK_NUMPAD6))
					{
						system("cls");

						std::cout << "X: " << std::endl;
						std::cin >> TeleportX;
						TeleportXCoord(handle);

						std::cout << "Y: " << std::endl;
						std::cin >> TeleportY;
						TeleportYCoord(handle);

						std::cout << "Z: " << std::endl;
						std::cin >> TeleportZ;
						TeleportZCoord(handle);
					}
					if (GetAsyncKeyState(VK_NUMPAD7))
					{
                                                FlyHack(handle);
					}
					if (GetAsyncKeyState(VK_NUMPAD8))
					{
						space_2 = false;
						goto returnPlayerInfo;
					}
					Sleep(10);
				}

			    }
				else if (!GetAsyncKeyState(VK_SPACE))
				{
					PlayerInfo(handle);
					Sleep(10);
					system("cls");
				}
			  }
			}
		 }
	   }
	}
	system("pause");
}

