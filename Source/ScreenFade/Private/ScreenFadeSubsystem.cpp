// Copyright 2023-2024 Metaseven. All Rights Reserved.

#include "ScreenFadeSubsystem.h"

#include "Engine/GameViewportClient.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "ScreenFadeTypes.h"
#include "ScreenFadeWidget.h"
#include "Widgets/SWidget.h"

void UScreenFadeSubsystem::AddFadeWidget(const FScreenFadeParams& FadeParams, const APlayerController* OwningPlayer, const int32 ZOrder)
{
	const int32 ControllerId = GetPlayerControllerId(OwningPlayer);

	if (FadeWidgetByControllerId.Contains(ControllerId))
	{
		RemoveFadeWidget(OwningPlayer, ControllerId);
	}

	FScreenFadeDelegate OnFadeFinished;

	if (FadeParams.ToColor.A <= 0.0f)
	{
		OnFadeFinished.BindUObject(this, &UScreenFadeSubsystem::RemoveFadeWidget, ControllerId);
	}

	const TSharedRef<SScreenFadeWidget> FadeWidget = SNew(SScreenFadeWidget).FadeParams(FadeParams).OnFadeFinished(OnFadeFinished);

	if (UGameViewportClient* GameViewport = GetGameViewport())
	{
		if (OwningPlayer)
		{
			GameViewport->AddViewportWidgetForPlayer(OwningPlayer->GetLocalPlayer(), FadeWidget, ZOrder);
		}
		else
		{
			GameViewport->AddViewportWidgetContent(FadeWidget, ZOrder + 10);
		}
	}

	FadeWidgetByControllerId.Emplace(ControllerId, FadeWidget);
	FadeWidget->StartFade();
}

void UScreenFadeSubsystem::RemoveFadeWidget(const APlayerController* OwningPlayer, const int32 ControllerId)
{
	TSharedRef<SWidget> FadeWidget = FadeWidgetByControllerId[ControllerId].Pin().ToSharedRef();
	FadeWidgetByControllerId.Remove(ControllerId);

	if (UGameViewportClient* GameViewport = GetGameViewport())
	{
		if (OwningPlayer)
		{
			GameViewport->RemoveViewportWidgetForPlayer(OwningPlayer->GetLocalPlayer(), FadeWidget);
		}
		else
		{
			GameViewport->RemoveViewportWidgetContent(FadeWidget);
		}
	}
}

void UScreenFadeSubsystem::RemoveFadeWidget(const int32 ControllerId)
{
	RemoveFadeWidget(GetPlayerControllerFromId(ControllerId), ControllerId);
}

UGameViewportClient* UScreenFadeSubsystem::GetGameViewport() const
{
	if (const UWorld* World = GetWorld())
	{
		if (UGameViewportClient* GameViewport = World->GetGameViewport())
		{
			return GameViewport;
		}
	}

	return nullptr;
}

int32 UScreenFadeSubsystem::GetPlayerControllerId(const APlayerController* PlayerController) const
{
	if (PlayerController)
	{
		if (const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			return LocalPlayer->GetControllerId();
		}
	}

	return 0x80000000;
}

APlayerController* UScreenFadeSubsystem::GetPlayerControllerFromId(const int32 ControllerId) const
{
	if (ControllerId == 0x80000000)
	{
		return nullptr;
	}

	if (const UWorld* World = GetWorld())
	{
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			APlayerController* PlayerController = It->Get();

			if (GetPlayerControllerId(PlayerController) == ControllerId)
			{
				return PlayerController;
			}
		}
	}

	return nullptr;
}
