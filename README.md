# ScreenFade

## This Fork Includes:
- **Level Load Crash Fix**: Prevents crashes when level loading interrupts fade transitions
- **Enhanced Safety**: Added null pointer validation and world validity checks

## Blueprint Nodes

![ScreenFade_Nodes](https://github.com/suramaru517/ScreenFade/assets/50897830/4ca3e356-4013-4d6e-b807-4b58ac5d737b)

### Example:

![ScreenFade_Example](https://github.com/suramaru517/ScreenFade/assets/50897830/2847003b-df47-4853-a367-e08f53c99378)

## C++ Functions

ScreenFadeFunctionLibrary.h

```cpp
static void Fade(
	const UObject* WorldContextObject,
	const FScreenFadeParams& FadeParams,
	const APlayerController* OwningPlayer = nullptr,
	const int32 ZOrder = 100);

static void FadeIn(
	const UObject* WorldContextObject,
	const float Time = 1.0f,
	const FLinearColor& FromColor = FLinearColor::Black,
	const FScreenFadeDelegate& OnFinished = FScreenFadeDelegate(),
	const bool bFadeAudio = true,
	const bool bFadeWhenPaused = true,
	const APlayerController* OwningPlayer = nullptr,
	const int32 ZOrder = 100);

static void FadeOut(
	const UObject* WorldContextObject,
	const float Time = 1.0f,
	const FLinearColor& ToColor = FLinearColor::Black,
	const FScreenFadeDelegate& OnFinished = FScreenFadeDelegate(),
	const bool bFadeAudio = true,
	const bool bFadeWhenPaused = true,
	const APlayerController* OwningPlayer = nullptr,
	const int32 ZOrder = 100);
```

### Example:

MyProject.Build.cs

```cs
PublicDependencyModuleNames.AddRange(new string[] { "ScreenFade" });
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
	UE_LOG(LogTemp, Log, TEXT("Fade in finished"));

	UScreenFadeFunctionLibrary::FadeOut(this, 1.0f, FLinearColor::Black, FScreenFadeDelegate::CreateLambda([]()
	{
		UE_LOG(LogTemp, Log, TEXT("Fade out finished"));
	}));
}
```
