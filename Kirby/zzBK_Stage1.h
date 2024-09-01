#pragma once

#include "zzGameObject.h"
#include "zzTexture.h"

namespace zz
{
	class BK_Stage1 : public GameObject
	{
	public:
		BK_Stage1();
		virtual ~BK_Stage1();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void SetFix(bool b) { mbFix = b; }

	private:
		Texture* mTex;
		bool mbFix;
	};

}
