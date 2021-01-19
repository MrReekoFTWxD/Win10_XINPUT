#include "pch.h"


XPad gamepad;

DWORD XINPUT[] =
{
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK
};

XPad::XPad()
{
	controllerIndex = 0;
}

XPad::XPad(int index)
{
	this->controllerIndex = index;
}

XPad::~XPad()
{
	this->controllerIndex = NULL;
}

void XPad::InitState()
{
	ZeroMemory(&input, sizeof XINPUT_STATE);
	XInputGetState(controllerIndex, &input);
}

XINPUT_STATE XPad::GetState()
{
	return input;
}

void XPad::updateState()
{
	for (int i = 0; i < 14; i++)
	{
		button[i] = (input.Gamepad.wButtons & XINPUT[i]) == XINPUT[i];
	}
}

void XPad::refreshState()
{
	memcpy(lastButton, button, sizeof(lastButton));
}

int XPad::GetControllerID()
{
	return controllerIndex;
}

bool XPad::isConnected()
{
	ZeroMemory(&input, sizeof XINPUT_STATE);
	DWORD response = XInputGetState(controllerIndex, &input);

	if (response == ERROR_SUCCESS)
		return true;
	return false;
}

bool XPad::Key_IsDown(int btn)
{
	return !lastButton[btn] && button[btn];
}

bool XPad::Key_IsPressed(int btn)
{
	auto state = input.Gamepad.wButtons;

	if (state & XINPUT[btn])
		return true;
	return false;
}

void XPad::Rumble(float L, float R)
{
	XINPUT_VIBRATION vib;
	ZeroMemory(&vib, sizeof XINPUT_VIBRATION);

	int left = int(L * 65535.0f);
	int right = int(L * 65535.0f);

	vib.wLeftMotorSpeed = left;
	vib.wRightMotorSpeed = right;
}

void XPad::Rumble(int L, int R)
{
	XINPUT_VIBRATION vib;
	ZeroMemory(&vib, sizeof XINPUT_VIBRATION);

	vib.wLeftMotorSpeed = L;
	vib.wRightMotorSpeed = R;
}
