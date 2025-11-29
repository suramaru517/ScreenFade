// Copyright 2023-2024 Metaseven. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Images/SImage.h"
#include "ScreenFadeTypes.h"

class UWorld;

class SScreenFadeWidget : public SImage
{
public:
	SLATE_BEGIN_ARGS(SScreenFadeWidget)
	{
	}
	SLATE_ARGUMENT(FScreenFadeParams, FadeParams)
	SLATE_EVENT(FScreenFadeDelegate, OnFadeFinished)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	void StartFade();

private:
	void FinishFade();
	void ApplyFade(const FLinearColor& NextColor);

	UWorld* GetWorld() const;
	bool IsGamePaused() const;
	void SetAudioVolume(const float Volume);

	FScreenFadeParams FadeParams;
	FScreenFadeDelegate OnFadeFinished;

	float TimeRemaining = 0.0f;
};
