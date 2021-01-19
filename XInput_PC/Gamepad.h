#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")

extern DWORD XINPUT[];

class XPad
{
public:

	XPad();
	XPad(int index);
	~XPad();

	void InitState();
	XINPUT_STATE GetState();

	void updateState();
	void refreshState();

	int GetControllerID();
	bool isConnected();
	bool Key_IsDown(int btn);
	bool Key_IsPressed(int btn);

	void Rumble(float L, float R);
	void Rumble(int L, int R);


private:
	int controllerIndex;
	XINPUT_STATE input;
	bool button[14];
	bool lastButton[14];
};

extern XPad gamepad;

#endif // GAMEPAD_H