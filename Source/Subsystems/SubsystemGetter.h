// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tools/Toolbox.h"

template <class SubsystemClass>
class CASTLEDEFENDER_API TSubsystemGetter
{
public:

	static SubsystemClass* Get(const UObject* WorldContextObject)
	{
		return UToolbox::GetSubsystem<SubsystemClass>(WorldContextObject);
	}
};
