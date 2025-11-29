// Copyright Metaseven. All Rights Reserved.

#include "ScreenFadeWidget.h"

#include "AudioDevice.h"
#include "AudioDeviceManager.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "Misc/EngineVersionComparison.h"

void SScreenFadeWidget::Construct(const FArguments& InArgs)
{
	FadeParams = InArgs._FadeParams;
	OnFadeFinished = InArgs._OnFadeFinished;
}

void SScreenFadeWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (!FadeParams.bFadeWhenPaused && IsGamePaused())
	{
		return;
	}

	TimeRemaining = FMath::Max(TimeRemaining - InDeltaTime, 0.0f);

	if (TimeRemaining == 0.0f)
	{
		FinishFade();
		return;
	}

	const FLinearColor NextColor = FadeParams.ToColor - (FadeParams.ToColor - FadeParams.FromColor) * TimeRemaining / FadeParams.Time;
	ApplyFade(NextColor);
}

void SScreenFadeWidget::StartFade()
{
	SetImage(FCoreStyle::Get().GetBrush("WhiteBrush"));

	if (FadeParams.Time <= 0.0f)
	{
		FinishFade();
		return;
	}

	TimeRemaining = FadeParams.Time;
	ApplyFade(FadeParams.FromColor);

	SetCanTick(true);
}

void SScreenFadeWidget::FinishFade()
{
	ApplyFade(FadeParams.ToColor);

	OnFadeFinished.ExecuteIfBound();
	FadeParams.OnFinished.ExecuteIfBound();
	FadeParams.OnFinishedDynamic.ExecuteIfBound();

	SetCanTick(false);
}

void SScreenFadeWidget::ApplyFade(const FLinearColor& NextColor)
{
	SetColorAndOpacity(NextColor);

	if (FadeParams.bFadeAudio)
	{
		SetAudioVolume(1.0f - NextColor.A);
	}
}

UWorld* SScreenFadeWidget::GetWorld() const
{
	if (GEngine)
	{
		if (const UGameViewportClient* GameViewport = GEngine->GameViewport)
		{
			return GameViewport->GetWorld();
		}
	}

	return nullptr;
}

bool SScreenFadeWidget::IsGamePaused() const
{
	if (const UWorld* World = GetWorld())
	{
		return World->IsPaused();
	}

	return false;
}

void SScreenFadeWidget::SetAudioVolume(const float Volume)
{
	if (UWorld* World = GetWorld())
	{
		if (FAudioDeviceHandle AudioDevice = World->GetAudioDevice())
		{
#if UE_VERSION_OLDER_THAN(5, 1, 0)
			AudioDevice->SetTransientMasterVolume(Volume);
#else
			AudioDevice->SetTransientPrimaryVolume(Volume);
#endif
		}
	}
}
