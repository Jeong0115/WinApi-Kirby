#include "zzEndingVideo.h"
#include "zzTexture.h"
#include "zzAnimator.h"
#include "zzSceneMgr.h"
#include "zzSound.h"
#include "zzKey.h"
#include "zzApplication.h"

namespace zz
{
	EndingVideo::EndingVideo()
	{
		SetPos(Vector2(127.f, 382.f));

		
		mAni = AddComponent<Animator>();
		mAni->SetFix();
		mAni->CreateAnimations(L"..\\Resources\\Video\\Ending", 0.0444931f);
		
		
		sound = ResourceMgr::Load<Sound>(L"Ending", L"..\\Resources\\Sound\\Theme\\Ending.wav");
		mAni->GetCompleteEvent(L"VideoEnding") = std::bind(&EndingVideo::destroy, this);
		
		
	}
	EndingVideo::~EndingVideo()
	{
		
	}
	void EndingVideo::Initialize()
	{
		Sound* mStage4BGM = ResourceMgr::Load<Sound>(L"Stage4BGM", L"..\\Resources\\Sound\\Theme\\Stage4Boss.wav");
		mStage4BGM->Stop(true);
		ResourceMgr::StopSound();	
		mAni->PlayAnimation(L"VideoEnding", true);
		sound->Play(false);
	}
	void EndingVideo::Update()
	{
		mAni->Update();
	}
	void EndingVideo::Render(HDC hdc)
	{
		mAni->Render(hdc);
	}
	void EndingVideo::destroy()
	{
		DestroyWindow(Application::GetHwnd());
	}
}