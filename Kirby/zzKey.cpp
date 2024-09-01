#include "zzKey.h"
#include "zzApplication.h"

namespace zz
{
	std::vector<Key::KeyInfo> Key::mKeysInfo;
	Vector2 Key::mMousePos = {};

	int ASCII[(UINT)eKeyCode::LAST] =
	{
		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		'Z', 'X', 'A', 'P', 'Q', 'W', VK_RETURN, VK_ESCAPE, VK_LBUTTON, VK_RBUTTON
	};

	void Key::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::LAST; i++)
		{
			mKeysInfo.push_back(KeyInfo{ (eKeyCode)i, eKeyState::NONE, false });
		}
	}
	
	void Key::Update()
	{
		HWND hWnd = Application::GetHwnd();
		HWND nowHwnd = GetFocus();

		if (hWnd == nowHwnd)
		{
			for (UINT i = 0; i < (UINT)eKeyCode::LAST; i++)
			{
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					if (mKeysInfo[i].bPressed)
						mKeysInfo[i].state = eKeyState::PRESSED;
					else
						mKeysInfo[i].state = eKeyState::DOWN;

					mKeysInfo[i].bPressed = true;
				}
				else
				{
					if (mKeysInfo[i].bPressed)
						mKeysInfo[i].state = eKeyState::UP;
					else
						mKeysInfo[i].state = eKeyState::NONE;

					mKeysInfo[i].bPressed = false;
				}
			}

			POINT pos = {};
			POINT resolution = Application::GetResolution();
			Vector2 curPos;
			GetCursorPos(&pos);

			ScreenToClient(Application::GetHwnd(), &pos);

			curPos = (Vector2((float)pos.x, (float)pos.y));
			RECT rect;

			HWND hwnd = Application::GetHwnd();

			GetClientRect(hwnd, &rect);

			curPos.x -= rect.right / 2 - ((rect.bottom / resolution.y * resolution.x) / 2);

			curPos.x /= ((float)rect.bottom / resolution.y);
			curPos.y /= ((float)rect.bottom / resolution.y);

			mMousePos = curPos;
		}
		else
		{
			for (UINT i = 0; i < (UINT)eKeyCode::LAST; i++)
			{
				mKeysInfo[i].bPressed = false;

				if (mKeysInfo[i].state == eKeyState::DOWN || mKeysInfo[i].state == eKeyState::PRESSED)
				{
					mKeysInfo[i].state = eKeyState::UP;
				}
				else if (mKeysInfo[i].state == eKeyState::UP)
				{
					mKeysInfo[i].state = eKeyState::NONE;
				}
			}
		}
	}
}