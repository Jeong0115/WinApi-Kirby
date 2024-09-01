#pragma once

#include "zzEngine.h"

namespace zz
{
	enum class eKeyCode
	{
		LEFT, RIGHT, UP, DOWN,
		Z, X, A, P, Q, W, ENTER, ESC, LBTN, RBTN, LAST
	};

	enum class eKeyState
	{
		DOWN,
		PRESSED,
		UP,
		NONE
	};

	class Key
	{
	public:
		struct KeyInfo
		{
			eKeyCode	key;
			eKeyState	state;
			bool		bPressed;
		};

		static void Initialize();
		static void Update();

		__forceinline static eKeyState GetKeyState(eKeyCode keyCode) { return mKeysInfo[(UINT)keyCode].state; }
		__forceinline static Vector2 GetMousePos() { return mMousePos; }

	private:
		static std::vector<KeyInfo> mKeysInfo;
		static Vector2				mMousePos;
	};
}

