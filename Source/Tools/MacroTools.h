// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Engine/Engine.h>

#define STRINGIFY(x) #x
#define MAKESTRING(l)  STRINGIFY(l)

#define SCREEN_LOG(Duration, Format, ...) do { if (GEngine) { GEngine->AddOnScreenDebugMessage(INDEX_NONE, Duration, FColor::Orange, FString::Printf(TEXT(Format), ##__VA_ARGS__), false); } } while(0)

static void LogEnsure(const TCHAR* _File, const TCHAR* _Line, const TCHAR* _Format, ...)
{
	va_list Args;
	va_start(Args, _Format);
	TCHAR Buffer[4096];
	FCString::GetVarArgs(Buffer, UE_ARRAY_COUNT(Buffer), _Format, Args);
	va_end(Args);

	FString FileName = FPaths::GetCleanFilename(_File); 
	FString LogMsg = FString::Printf(TEXT("%s (%s) => ENSURE : %s"), *FileName, _Line, Buffer);

	UE_LOG(LogOutputDevice, Error, TEXT("%s"), *LogMsg);

	if (GEngine) 
	{
#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30, FColor::Red, LogMsg, false);
#endif
	} 
}

#define ENSURE_IMPL(Capture, Once, InExpression, Format, ...) \
		(LIKELY(!!(InExpression)) || (DispatchCheckVerify<bool>([Capture] () FORCENOINLINE UE_DEBUG_SECTION \
		{ \
			static bool bExecuted = false; \
			if (!bExecuted && FPlatformMisc::IsEnsureAllowed()) \
			{ \
				bExecuted = Once; \
				LogEnsure(TEXT(__FILE__), TEXT(MAKESTRING(__LINE__)), Format, ##__VA_ARGS__); \
				if (FPlatformMisc::IsDebuggerPresent()) \
				{ \
					PLATFORM_BREAK(); \
				} \
			} \
			return false; \
		})))

#if WITH_EDITOR
	#define EnsureMsg(InExpression, InFormat, ...) ENSURE_IMPL(&,true, InExpression, InFormat, ##__VA_ARGS__)
#else
	#define EnsureMsg(InExpression, InFormat, ...) (!!(InExpression))
#endif
