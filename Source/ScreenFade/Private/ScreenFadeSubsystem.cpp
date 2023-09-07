// Copyright 2023 Metaseven. All Rights Reserved.

#include "ScreenFadeSubsystem.h"
#include "ScreenFadeWidget.h"
#include "Engine/GameViewportClient.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void UScreenFadeSubsystem::AddFadeWidget(const FScreenFadeParams& FadeParams, const APlayerController* OwningPlayer, const int32 ZOrder)
{
	const int32 ControllerID = GetPlayerControllerID(OwningPlayer);

	if (FadeWidgetsForID.Contains(ControllerID))
	{
		RemoveFadeWidget(OwningPlayer, ControllerID);
	}

	FScreenFadeDelegate OnFadeFinished;

	if (FadeParams.ToColor.A <= 0.0f)
	{
		OnFadeFinished.BindUObject(this, &UScreenFadeSubsystem::RemoveFadeWidget, ControllerID);
	}

	TSharedRef<SScreenFadeWidget> FadeWidget = SNew(SScreenFadeWidget).FadeParams(FadeParams).OnFadeFinished(OnFadeFinished);

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

	FadeWidgetsForID.Emplace(ControllerID, FadeWidget);
	FadeWidget->StartFade();
}

void UScreenFadeSubsystem::RemoveFadeWidget(const APlayerController* OwningPlayer, const int32 ControllerID)
{
	TSharedRef<SWidget> FadeWidget = FadeWidgetsForID[ControllerID].Pin().ToSharedRef();
	FadeWidgetsForID.Remove(ControllerID);

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

void UScreenFadeSubsystem::RemoveFadeWidget(const int32 ControllerID)
{
	RemoveFadeWidget(GetPlayerControllerFromID(ControllerID), ControllerID);
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

int32 UScreenFadeSubsystem::GetPlayerControllerID(const APlayerController* PlayerController) const
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

APlayerController* UScreenFadeSubsystem::GetPlayerControllerFromID(const int32 ControllerID) const
{
	if (ControllerID == 0x80000000)
	{
		return nullptr;
	}

	if (const UWorld* World = GetWorld())
	{
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PlayerController = Iterator->Get();

			if (GetPlayerControllerID(PlayerController) == ControllerID)
			{
				return PlayerController;
			}
		}
	}

	return nullptr;
}
