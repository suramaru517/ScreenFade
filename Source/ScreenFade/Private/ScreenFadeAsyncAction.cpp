// Copyright 2023-2024 Metaseven. All Rights Reserved.

#include "ScreenFadeAsyncAction.h"

#include "GameFramework/PlayerController.h"
#include "ScreenFadeFunctionLibrary.h"
#include "ScreenFadeTypes.h"

void UScreenFadeAsyncAction::Activate()
{
	Super::Activate();
	UScreenFadeFunctionLibrary::Fade(WorldContextObject.Get(), FadeParams, OwningPlayer.Get(), ZOrder);
}

UScreenFadeAsyncAction* UScreenFadeAsyncAction::AsyncFade(UObject* WorldContextObject, const FScreenFadeParams& FadeParams, const APlayerController* OwningPlayer, const int32 ZOrder)
{
	UScreenFadeAsyncAction* AsyncAction = NewObject<UScreenFadeAsyncAction>();

	AsyncAction->RegisterWithGameInstance(WorldContextObject);
	AsyncAction->WorldContextObject = WorldContextObject;
	AsyncAction->FadeParams = FadeParams;
	AsyncAction->FadeParams.OnFinished.BindUObject(AsyncAction, &UScreenFadeAsyncAction::OnFadeFinished);
	AsyncAction->OwningPlayer = OwningPlayer;
	AsyncAction->ZOrder = ZOrder;

	return AsyncAction;
}

UScreenFadeAsyncAction* UScreenFadeAsyncAction::AsyncFadeIn(UObject* WorldContextObject, const float Time, const FLinearColor FromColor, const bool bFadeAudio, const bool bFadeWhenPaused, const APlayerController* OwningPlayer, const int32 ZOrder)
{
	const FScreenFadeParams FadeParams(Time, FromColor, FLinearColor::Transparent, FScreenFadeDelegate(), bFadeAudio, bFadeWhenPaused);
	return AsyncFade(WorldContextObject, FadeParams, OwningPlayer, ZOrder);
}

UScreenFadeAsyncAction* UScreenFadeAsyncAction::AsyncFadeOut(UObject* WorldContextObject, const float Time, const FLinearColor ToColor, const bool bFadeAudio, const bool bFadeWhenPaused, const APlayerController* OwningPlayer, const int32 ZOrder)
{
	const FScreenFadeParams FadeParams(Time, FLinearColor::Transparent, ToColor, FScreenFadeDelegate(), bFadeAudio, bFadeWhenPaused);
	return AsyncFade(WorldContextObject, FadeParams, OwningPlayer, ZOrder);
}

void UScreenFadeAsyncAction::OnFadeFinished()
{
	Finished.Broadcast();
	SetReadyToDestroy();
}
