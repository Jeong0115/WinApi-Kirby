#include "zzAnimator.h"
#include "zzGameObject.h"
#include "zzResourceMgr.h"

namespace zz
{

	Animator::Animator()
		: Component(eCompType::ANIMATOR)
		, mCurAnimation(nullptr)
		, mbLoop(false)
		, mbFix(false)
		, mbAlpha(false)
		, mbBlink(false)
		, mSpriteSheet(nullptr)
	{
	}

	Animator::~Animator()
	{
		for (auto pair : mAnimations)
		{
			delete pair.second;
			pair.second = nullptr;
		}

		for (auto pair : mEvents)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}

	void Animator::Update()
	{
		if(mCurAnimation!=nullptr)
		{
			if(mbFix)
			{
				mCurAnimation->Update(GetOwner()->GetPos());
			}
			else
			{
				mCurAnimation->Update(Camera::GetRenderPos(GetOwner()->GetPos()));
			}

			if (mCurAnimation->IsFinish())
			{
				Animator::Events* events = FindEvents(mCurAnimation->GetName());

				if (events != nullptr)
					events->mCompleteEvent();
			}
			if (mbLoop && mCurAnimation->IsFinish())
			{
				Animator::Events* events = FindEvents(mCurAnimation->GetName());
				if (events != nullptr)
					events->mStartEvent();
				mCurAnimation->Repeat(0);
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mCurAnimation != nullptr)
		{
			mCurAnimation->Render(hdc, mbAlpha, mbBlink);
		}
	}

	void Animator::Release()
	{
	}

	void Animator::CreateAnimation(Texture* tex, const std::wstring& name
		, Vector2 startPos, Vector2 texSize, Vector2 interval, float delay, UINT texCnt, std::vector<Vector2> offset)
	{
		if (FindAnimation(name) != nullptr)
			assert(true);

		Animation* ani = new Animation;
		ani->SetName(name);
		mAnimations.insert(std::make_pair(name, ani));

		Events* event = new Events();
		mEvents.insert(std::make_pair(name, event));

		ani->CreateAnimation(tex, startPos, texSize, interval, delay, texCnt, offset);
	}

	void Animator::CreateAnimations(const std::wstring& path, float duration, Vector2 size)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Texture*> textures = {};
		for (const auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = path + L"\\" + fileName;

			const std::wstring ext = p.path().extension();
			if (ext == L".png")
				continue;

			Texture* tex = ResourceMgr::Load<Texture>(fileName, fullName);
			textures.push_back(tex);

			if (width < tex->GetWidth())
			{
				width = tex->GetWidth();
			}
			if (height < tex->GetHeight())
			{
				height = tex->GetHeight();
			}
			fileCount++;
		}

		std::wstring key = fs.parent_path().filename();
		key += fs.filename();
		mSpriteSheet = Texture::Create(key, width * fileCount, height);

		//
		int index = 0;
		for (Texture* tex : textures)
		{
			//int centerX = (width - tex->GetWidth()) / 2;
			//int centerY = (height - tex->GetHeight());

			BitBlt(mSpriteSheet->GetHdc()
				, width * index /*+ centerX*/
				, 0 /*+ centerY*/
				, tex->GetWidth(), tex->GetHeight()
				, tex->GetHdc(), 0, 0, SRCCOPY);

			index++;
		}

		CreateAnimation(mSpriteSheet, key, Vector2(0.f, 0.f), size, Vector2(256.f, 0.f), duration, index);
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter = mAnimations.find(name);
	
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		if (mCurAnimation != nullptr)
		{
			Animator::Events* prevEvents
				= FindEvents(mCurAnimation->GetName());

			if (prevEvents != nullptr)
				prevEvents->mEndEvent();
		}

		mCurAnimation = FindAnimation(name);
		mCurAnimation->Repeat(0);
		mbLoop = loop;

		Animator::Events* events
			= FindEvents(name);

		if (events != nullptr)
			events->mStartEvent();
	}

	void Animator::StopAnimation()
	{
		mCurAnimation->SetFinish(true);
		mbLoop = false;
	}

	void Animator::SetScale(float scale)
	{
		std::map<std::wstring, Animation*>::iterator iter = mAnimations.begin();

		for (; iter != mAnimations.end(); iter++)
		{
			iter->second->SetScale(scale);
		}
	}

	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter = mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		return FindEvents(name)->mStartEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		return FindEvents(name)->mCompleteEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		return FindEvents(name)->mEndEvent.mEvent;
	}
}