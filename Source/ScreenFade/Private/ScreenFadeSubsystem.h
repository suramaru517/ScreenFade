// Copyright Metaseven. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScreenFadeSubsystem.generated.h"

class APlayerController;
class SWidget;
class UGameViewportClient;
struct FScreenFadeParams;

UCLASS()
class UScreenFadeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void AddFadeWidget(const FScreenFadeParams& FadeParams, const APlayerController* OwningPlayer = nullptr, const int32 ZOrder = 100);
	void RemoveFadeWidget(const APlayerController* OwningPlayer);
	bool FadeWidgetExists(const APlayerController* OwningPlayer) const;

private:
	void RemoveFadeWidget(const APlayerController* OwningPlayer, const int32 ControllerId);
	void RemoveFadeWidget(const int32 ControllerId);

	UGameViewportClient* GetGameViewport() const;
	int32 GetPlayerControllerId(const APlayerController* PlayerController) const;
	APlayerController* GetPlayerControllerFromId(const int32 ControllerId) const;

	TMap<int32, TWeakPtr<SWidget>> FadeWidgetByControllerId;
};
