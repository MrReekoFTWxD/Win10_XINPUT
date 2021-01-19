// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"


DWORD main(HMODULE hMod)
{
	while (true)
	{
		if (gamepad.Key_IsPressed(XINPUT_GAMEPAD_A))
			printf("Button Pressed A\r\n");
		if (gamepad.Key_IsPressed(XINPUT_GAMEPAD_B))
			printf("Button Pressed B\r\n");
		if (gamepad.Key_IsPressed(XINPUT_GAMEPAD_X))
			printf("Button Pressed X\r\n");
		if (gamepad.Key_IsPressed(XINPUT_GAMEPAD_Y))
			printf("Button Pressed Y\r\n");

		if (gamepad.Key_IsDown(XINPUT_GAMEPAD_A))
			printf("Button isDown A\r\n");
		if (gamepad.Key_IsDown(XINPUT_GAMEPAD_B))
			printf("Button isDown B\r\n");
		if (gamepad.Key_IsDown(XINPUT_GAMEPAD_X))
			printf("Button isDown X\r\n");
		if (gamepad.Key_IsDown(XINPUT_GAMEPAD_Y))
			printf("Button isDown Y\r\n");

		if (gamepad.Key_IsPressed(XINPUT_GAMEPAD_LEFT_THUMB) && gamepad.Key_IsPressed(XINPUT_GAMEPAD_RIGHT_THUMB))
			gamepad.Rumble(1.0f, 1.0f); 


		if (!gamepad.isConnected())
		{
			printf("Controller failed!\nPlease check connection and reload module!\r\n");
			break;
		}
	}

	FreeConsole();
	FreeLibraryAndExitThread(hMod, 0);
	return S_OK;
}

BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
  if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
		AllocConsole();
		freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
		SetConsoleTitleA("XINPUT Output");

		if (gamepad.isConnected())
			printf("Controller Index %i\r\n", gamepad.GetControllerID());

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, hModule, NULL, NULL);
    }
    return TRUE;
}

