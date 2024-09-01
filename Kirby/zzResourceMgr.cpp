#include "zzResourceMgr.h"
#include "zzSound.h"

namespace zz
{
	std::map<std::wstring, Resource*> ResourceMgr::mResources = {};

	void ResourceMgr::StopSound()
	{
		for (auto pair : mResources)
		{
			Sound* sound = dynamic_cast<Sound*>(pair.second);

			if (sound != nullptr)
			{
				if (sound->GetName() == L"BGM")
					continue;
				sound->Stop(false);
			}
		}
	}

}