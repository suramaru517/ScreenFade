// Copyright Metaseven. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ScreenFadeTypes.h"
#include "ScreenFadeAsyncAction.generated.h"

class APlayerController;

UCLASS()
class UScreenFadeAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

private:
	/**
	 * Fade the screen from a color to another.
	 * @param FadeParams - Parameters to set fade.
	 * @param OwningPlayer - The player to add the fade widget to.
	 * @param ZOrder - The Z-order index for this fade widget. Larger values will cause the widget to appear on top of widgets with lower values.
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "ScreenFade", meta = (DisplayName = "Fade (Latent)", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", AdvancedDisplay = 2))
	static UScreenFadeAsyncAction* AsyncFade(
		UObject* WorldContextObject,
		const FScreenFadeParams& FadeParams,
		const APlayerController* OwningPlayer = nullptr,
		const int32 ZOrder = 100
	);

	/**
	 * Fade the screen from a color to transparent.
	 * @param Time - How long the fade should take, in seconds.
	 * @param FromColor - Color to fade from.
	 * @param bFadeAudio - True to fade audio volume along with the alpha of the color.
	 * @param bFadeWhenPaused - True to continue to fade when the game is paused.
	 * @param OwningPlayer - The player to add the fade widget to.
	 * @param ZOrder - The Z-order index for this fade widget. Larger values will cause the widget to appear on top of widgets with lower values.
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "ScreenFade", meta = (DisplayName = "Fade In (Latent)", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", AdvancedDisplay = 3))
	static UScreenFadeAsyncAction* AsyncFadeIn(
		UObject* WorldContextObject,
		const float Time = 1.0f,
		const FLinearColor FromColor = FLinearColor::Black,
		const bool bFadeAudio = true,
		const bool bFadeWhenPaused = true,
		const APlayerController* OwningPlayer = nullptr,
		const int32 ZOrder = 100
	);

	/**
	 * Fade the screen from transparent to a color.
	 * @param Time - How long the fade should take, in seconds.
	 * @param ToColor - Color to fade to.
	 * @param bFadeAudio - True to fade audio volume along with the alpha of the color.
	 * @param bFadeWhenPaused - True to continue to fade when the game is paused.
	 * @param OwningPlayer - The player to add the fade widget to.
	 * @param ZOrder - The Z-order index for this fade widget. Larger values will cause the widget to appear on top of widgets with lower values.
	 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "ScreenFade", meta = (DisplayName = "Fade Out (Latent)", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", AdvancedDisplay = 3))
	static UScreenFadeAsyncAction* AsyncFadeOut(
		UObject* WorldContextObject,
		const float Time = 1.0f,
		const FLinearColor ToColor = FLinearColor::Black,
		const bool bFadeAudio = true,
		const bool bFadeWhenPaused = true,
		const APlayerController* OwningPlayer = nullptr,
		const int32 ZOrder = 100
	);

	void OnFadeFinished();

	TWeakObjectPtr<const UObject> WorldContextObject;
	FScreenFadeParams FadeParams;
	TWeakObjectPtr<const APlayerController> OwningPlayer;
	int32 ZOrder = 0;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishedDelegate);

	/** Called when the fade is finished. */
	UPROPERTY(BlueprintAssignable)
	FFinishedDelegate Finished;
};
