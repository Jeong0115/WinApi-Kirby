#pragma once

#include "CommonInclude.h"

namespace zz
{
	class SoundMgr
	{
	public:
		static bool Initialize();
		static LPDIRECTSOUND8 GetDevice() { return mSoundDevice; }

	private:
		static LPDIRECTSOUND8 mSoundDevice;
	};
}

