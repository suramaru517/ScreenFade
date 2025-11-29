# ScreenFade

## Blueprint

<img width="3840" height="2160" alt="ScreenFade" src="https://github.com/user-attachments/assets/e354e7ec-3c65-45e5-938a-93413e4489c1" />

## C++

```cpp
static void Fade(
	const UObject* WorldContextObject,
	const FScreenFadeParams& FadeParams,
	const APlayerController* OwningPlayer = nullptr,
	const int32 ZOrder = 100
);

static void FadeIn(
	const UObject* WorldContextObject,
	const float Time = 1.0f,
	const FLinearColor& FromColor = FLinearColor::Black,
	const FScreenFadeDelegate& OnFinished = FScreenFadeDelegate(),
	const bool bFadeAudio = true,
	const bool bFadeWhenPaused = true,
	const APlayerController* OwningPlayer = nullptr,
	const int32 ZOrder = 100
);

static void FadeOut(
	const UObject* WorldContextObject,
	const float Time = 1.0f,
	const FLinearColor& ToColor = FLinearColor::Black,
	const FScreenFadeDelegate& OnFinished = FScreenFadeDelegate(),
	const bool bFadeAudio = true,
	const bool bFadeWhenPaused = true,
	const APlayerController* OwningPlayer = nullptr,
	const int32 ZOrder = 100
);

static void ClearFade(
	const UObject* WorldContextObject,
	const APlayerController* OwningPlayer = nullptr
);

static bool IsFading(
	const UObject* WorldContextObject,
	const APlayerController* OwningPlayer = nullptr
);
```

### Example:

MyProject.Build.cs

```cs
PublicDependencyModuleNames.Add("ScreenFade");
```

MyActor.cpp

```cpp
#include "MyActor.h"
#include "ScreenFadeFunctionLibrary.h"

void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	UScreenFadeFunctionLibrary::FadeIn(this, 1.0f, FLinearColor::Black, FScreenFadeDelegate::CreateUObject(this, &AMyActor::OnFadeInFinished));
}

void AMyActor::OnFadeInFinished()
{
	UScreenFadeFunctionLibrary::FadeOut(this, 1.0f, FLinearColor::Black, FScreenFadeDelegate::CreateWeakLambda(this, []()
	{
		UE_LOG(LogTemp, Log, TEXT("Finished"));
	}));
}
```
