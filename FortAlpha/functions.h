#include "offsets.h"

static UObject* SpawnObject(UObject* Class, UObject* Outer)
{
	struct Params
	{
		UObject* ObjectClass;
		UObject* Outer;
		UObject* ReturnValue;
	};

	Params params;
	params.ObjectClass = Class;
	params.Outer = Outer;

	ProcessEvent(Offsets::GameplayStatics, Offsets::GameplayStatics, Offsets::SpawnObjectFunc, &params);

	return params.ReturnValue;
}

static void GivePlayerLocalAccountItem(UObject* ItemDefinition, int Count = 1)
{
	struct Params
	{
		UObject* ItemDefinition;
		int Count;
	};

	Params params;
	params.Count = Count;
	params.ItemDefinition = ItemDefinition;

	ProcessEvent(Offsets::PlayerController, Offsets::PlayerController, Offsets::GivePlayerLocalAccountItemFunc, &params);
}

static void SetPersonalHeroChoice(UObject* Hero)
{
	struct Params
	{
		UObject* Hero;
	};

	Params params;
	params.Hero = Hero;

	ProcessEvent(Offsets::FrontendContext, Offsets::FrontendContext, Offsets::SetPersonalHeroChoiceFunc, &params);
}

static void ControlCloudsUpdate()
{
	auto OnboardingCloudCover = FindObject(L"S_HB_OnboardingCloudCover_C /Game/Maps/FortniteEntry.FortniteEntry.PersistentLevel.S_HB_OnboardingCloudCover_C_0");

	ProcessEvent(OnboardingCloudCover, OnboardingCloudCover, Offsets::ControlCloudsUpdateFunc, nullptr);
}

static void SetActorHiddenInGame(UObject* Actor, bool bNewHidden)
{
	struct Params
	{
		bool bNewHidden;
	};

	Params params;
	params.bNewHidden = bNewHidden;

	ProcessEvent(Actor, Actor, Offsets::SetActorHiddenInGameFunc, &params);
}

void UpdateRatingWidget(UObject* HomeBaseRatingWidget)
{
	auto UpdateFunc = FindObject(L"Function /Game/UI/HomeBase/HomeBaseRatingWidget.HomeBaseRatingWidget_C.Update");
	ProcessEvent(HomeBaseRatingWidget, HomeBaseRatingWidget, UpdateFunc, nullptr);
}

void UpdateMtxWidget(UObject* MtxWidget, int Value)
{
	auto SetMtxValueFunc = FindObject(L"Function /Game/UI/Global_Elements/MtxCurrency_Widget.MtxCurrency_Widget_C.Set_MtxValue_from_Int");

	struct Params
	{
		int Value;
	};

	Params params;
	params.Value = Value;

	ProcessEvent(MtxWidget, MtxWidget, SetMtxValueFunc, &params);
}

void SetShowHUD(bool bNewShowHUD)
{
	struct Params
	{
		bool bNewShowHUD;
	};

	Params params;
	params.bNewShowHUD = bNewShowHUD;

	ProcessEvent(Offsets::PlayerController, Offsets::PlayerController, Offsets::SetShowHUDFunc, &params);
}

void OpenLlama()
{
	auto StorePinataMaster = FindObject(L"StorePinataMaster_BP_C /Game/Maps/FrontEnd/Maps/FrontEndStore.FrontEndStore.PersistentLevel.StorePinataMaster_BP_C_0");
	ProcessEvent(StorePinataMaster, StorePinataMaster, Offsets::StartPackOpenFunc, nullptr);
}

TArray<UObject*> JonLHack(FString Path, UObject* Class)
{
	static auto FortKismetLibrary = SpawnObject(FindObject(L"Class /Script/FortniteGame.FortKismetLibrary"), FindObject(L"Package /Script/FortniteGame"));
	static auto JonLHackFunc = FindObject(L"Function /Script/FortniteGame.FortKismetLibrary.JonLHack_GetAllObjectsOfClassFromPath");

	struct Params
	{
		FString Path;
		UObject* Class;
		TArray<UObject*> ReturnValue;
	};

	Params params;
	params.Path = Path;
	params.Class = Class;

	ProcessEvent(FortKismetLibrary, FortKismetLibrary, JonLHackFunc, &params);

	return params.ReturnValue;
}