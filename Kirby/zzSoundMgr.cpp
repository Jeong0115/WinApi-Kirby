#include "zzSoundMgr.h"
#include "zzApplication.h"

namespace zz
{
	LPDIRECTSOUND8 SoundMgr::mSoundDevice;

	bool SoundMgr::Initialize()
	{
		if (FAILED(DirectSoundCreate8(NULL, &mSoundDevice, NULL)))
		{
			MessageBox(NULL, L"�������̽���������", L"SYSTEM ERROR", MB_OK);
			return false;
		}

		// ���� ����̽� �������� ����.
		HWND hWnd = Application::GetHwnd();
		if (FAILED(mSoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
		{
			MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
			return false;
		}

		return true;
	}
}