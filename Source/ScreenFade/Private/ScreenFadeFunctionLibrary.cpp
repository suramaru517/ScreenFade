// Copyright 2023-2024 Metaseven. All Rights Reserved.

#include "ScreenFadeFunctionLibrary.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "ScreenFadeSubsystem.h"

void UScreenFadeFunctionLibrary::Fade(const UObject* WorldContextObject, const FScreenFadeParams& FadeParams, const APlayerController* OwningPlayer, const int32 ZOrder)
{
	if (GEngine)
	{
		if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UScreenFadeSubsystem* Subsystem = World->GetGameInstance()->GetSubsystem<UScreenFadeSubsystem>();
			Subsystem->AddFadeWidget(FadeParams, OwningPlayer, ZOrder);
		}
	}
}

void UScreenFadeFunctionLibrary::FadeIn(const UObject* WorldContextObject, const float Time, const FLinearColor& FromColor, const FScreenFadeDelegate& OnFinished, const bool bFadeAudio, const bool bFadeWhenPaused, const APlayerController* OwningPlayer, const int32 ZOrder)
{
	const FScreenFadeParams FadeParams(Time, FromColor, FLinearColor::Transparent, OnFinished, bFadeAudio, bFadeWhenPaused);
	Fade(WorldContextObject, FadeParams, OwningPlayer, ZOrder);
}

void UScreenFadeFunctionLibrary::FadeOut(const UObject* WorldContextObject, const float Time, const FLinearColor& ToColor, const FScreenFadeDelegate& OnFinished, const bool bFadeAudio, const bool bFadeWhenPaused, const APlayerController* OwningPlayer, const int32 ZOrder)
{
	const FScreenFadeParams FadeParams(Time, FLinearColor::Transparent, ToColor, OnFinished, bFadeAudio, bFadeWhenPaused);
	Fade(WorldContextObject, FadeParams, OwningPlayer, ZOrder);
}

void UScreenFadeFunctionLibrary::K2_FadeIn(const UObject* WorldContextObject, const float Time, const FLinearColor FromColor, const FScreenFadeDynamicDelegate& OnFinished, const bool bFadeAudio, const bool bFadeWhenPaused, const APlayerController* OwningPlayer, const int32 ZOrder)
{
	const FScreenFadeParams FadeParams(Time, FromColor, FLinearColor::Transparent, OnFinished, bFadeAudio, bFadeWhenPaused);
	Fade(WorldContextObject, FadeParams, OwningPlayer, ZOrder);
}

void UScreenFadeFunctionLibrary::K2_FadeOut(const UObject* WorldContextObject, const float Time, const FLinearColor ToColor, const FScreenFadeDynamicDelegate& OnFinished, const bool bFadeAudio, const bool bFadeWhenPaused, const APlayerController* OwningPlayer, const int32 ZOrder)
{
	const FScreenFadeParams FadeParams(Time, FLinearColor::Transparent, ToColor, OnFinished, bFadeAudio, bFadeWhenPaused);
	Fade(WorldContextObject, FadeParams, OwningPlayer, ZOrder);
}
