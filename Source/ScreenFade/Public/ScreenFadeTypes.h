// Copyright 2023 Metaseven. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ScreenFadeTypes.generated.h"

DECLARE_DELEGATE(FScreenFadeDelegate);
DECLARE_DYNAMIC_DELEGATE(FScreenFadeDynamicDelegate);

USTRUCT(BlueprintType)
struct FScreenFadeParams
{
	GENERATED_BODY()

	/** How long the fade should take, in seconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScreenFade")
	float Time;

	/** Color to fade from. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScreenFade")
	FLinearColor FromColor;

	/** Color to fade to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScreenFade")
	FLinearColor ToColor;

	/** Delegate executed when the fade is finished. */
	FScreenFadeDelegate OnFinished;

	/** Event called when the fade is finished. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "On Finished", Category = "ScreenFade")
	FScreenFadeDynamicDelegate OnFinishedDynamic;

	/** True to fade audio volume along with the alpha of the color. */
	UPROPERTY(AdvancedDisplay, EditAnywhere, BlueprintReadWrite, Category = "ScreenFade")
	bool bFadeAudio;

	/** True to continue to fade when the game is paused. */
	UPROPERTY(AdvancedDisplay, EditAnywhere, BlueprintReadWrite, Category = "ScreenFade")
	bool bFadeWhenPaused;

	FScreenFadeParams()
		: Time(0.0f)
		, FromColor(FLinearColor::Transparent)
		, ToColor(FLinearColor::Transparent)
		, bFadeAudio(true)
		, bFadeWhenPaused(true)
	{
	}

	FScreenFadeParams(const float InTime, const FLinearColor& InFromColor, const FLinearColor& InToColor, const FScreenFadeDelegate& InOnFinished, const bool bInFadeAudio, const bool bInFadeWhenPaused)
		: Time(InTime)
		, FromColor(InFromColor)
		, ToColor(InToColor)
		, OnFinished(InOnFinished)
		, bFadeAudio(bInFadeAudio)
		, bFadeWhenPaused(bInFadeWhenPaused)
	{
	}

	FScreenFadeParams(const float InTime, const FLinearColor& InFromColor, const FLinearColor& InToColor, const FScreenFadeDynamicDelegate& InOnFinished, const bool bInFadeAudio, const bool bInFadeWhenPaused)
		: Time(InTime)
		, FromColor(InFromColor)
		, ToColor(InToColor)
		, OnFinishedDynamic(InOnFinished)
		, bFadeAudio(bInFadeAudio)
		, bFadeWhenPaused(bInFadeWhenPaused)
	{
	}
};
