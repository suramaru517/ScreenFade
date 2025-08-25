// Copyright 2023-2024 Metaseven. All Rights Reserved.

#include "ScreenFadeSubsystem.h"
#include "ScreenFadeWidget.h"
#include "Engine/GameViewportClient.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"

void UScreenFadeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (GEngine)
	{
		GEngine->OnWorldDestroyed().AddUObject(this, &UScreenFadeSubsystem::OnWorldDestroyed);
	}
}

void UScreenFadeSubsystem::Deinitialize()
{
	if (GEngine)
	{
		GEngine->OnWorldDestroyed().RemoveAll(this);
	}

	FadeWidgetsForID.Empty();
	Super::Deinitialize();
}

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
	if (!FadeWidgetsForID.Contains(ControllerID))
	{
		return;
	}

	TSharedPtr<SWidget> FadeWidgetPtr = FadeWidgetsForID[ControllerID].Pin();
	FadeWidgetsForID.Remove(ControllerID);

	if (!FadeWidgetPtr.IsValid())
	{
		return;
	}

	TSharedRef<SWidget> FadeWidget = FadeWidgetPtr.ToSharedRef();

	if (UGameViewportClient* GameViewport = GetGameViewport())
	{
		if (OwningPlayer && IsValid(OwningPlayer) && OwningPlayer->GetLocalPlayer())
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
void UScreenFadeSubsystem::OnWorldDestroyed(UWorld* World)
{
	TArray<int32> ControllerIDsToRemove;
	
	for (auto& Pair : FadeWidgetsForID)
	{
		if (!Pair.Value.IsValid())
		{
			ControllerIDsToRemove.Add(Pair.Key);
		}
	}
	
	for (int32 ControllerID : ControllerIDsToRemove)
	{
		FadeWidgetsForID.Remove(ControllerID);
	}
}
