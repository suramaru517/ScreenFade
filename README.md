# ScreenFade

## Blueprint Nodes

![ScreenFade_Nodes](https://github.com/suramaru517/ScreenFade/assets/50897830/4ca3e356-4013-4d6e-b807-4b58ac5d737b)

### Example:

![ScreenFade_Example](https://github.com/suramaru517/ScreenFade/assets/50897830/2847003b-df47-4853-a367-e08f53c99378)

## C++ Functions

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
