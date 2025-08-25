// Copyright 2023-2024 Metaseven. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScreenFadeSubsystem.generated.h"

class SWidget;
class UGameViewportClient;
struct FScreenFadeParams;

UCLASS()
class UScreenFadeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void AddFadeWidget(const FScreenFadeParams& FadeParams, const APlayerController* OwningPlayer = nullptr, const int32 ZOrder = 100);

private:
	void RemoveFadeWidget(const APlayerController* OwningPlayer, const int32 ControllerID);
	void RemoveFadeWidget(const int32 ControllerID);

	UFUNCTION()
	void OnWorldDestroyed(class UWorld* World);
	UGameViewportClient* GetGameViewport() const;
	int32 GetPlayerControllerID(const APlayerController* PlayerController) const;
	APlayerController* GetPlayerControllerFromID(const int32 ControllerID) const;

	TMap<int32, TWeakPtr<SWidget>> FadeWidgetsForID;
};
