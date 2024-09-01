#pragma once

#include "zzComponent.h"
#include "zzAnimation.h"

namespace zz
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}

			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};

	public:
		Animator();
		virtual ~Animator();

	public:
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	public:
		void CreateAnimation(Texture* tex, const std::wstring& key
			, Vector2 startPos, Vector2 texSize, Vector2 interval, float delay, UINT texCnt ,std::vector<Vector2> offset = {});

		void CreateAnimations(const std::wstring& path, float duration, Vector2 size = {256.f, 384.f});

		Animation* FindAnimation(const std::wstring& key);
		void PlayAnimation(const std::wstring& name, bool loop);
		void StopAnimation();
		void SetFix() { mbFix = true; }
		void SetAlpha(bool b) { mbAlpha = b; }
		void SetBlink(bool b) { mbBlink = b; }
		void SetScale(float scale);

		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);

		bool IsComplete() { return mCurAnimation->IsFinish(); }

	private:
		std::map<std::wstring, Animation*>		mAnimations;
		std::map<std::wstring, Events*>			mEvents;
		Animation*								mCurAnimation;
		Texture*								mSpriteSheet;

		bool									mbLoop;
		bool									mbFix;
		bool									mbAlpha;
		bool									mbBlink;
	};

}