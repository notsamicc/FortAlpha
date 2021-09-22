#include "functions.h"

namespace Frontend
{
	void UnlockConsole()
	{
		auto NewConsole = SpawnObject(FindObject(L"Class /Script/Engine.Console"), Offsets::GameViewportClient);
		*(UObject**)(DWORD(Offsets::GameViewportClient) + Offsets::ViewportConsoleOffset) = NewConsole;
	}

	void SetupHeroMenu()
	{
		auto FortHero = FindObject(L"FortHero /Engine/Transient.FortHero_0");
		
		*(int*)(DWORD(FortHero) + Offsets::HeroLevelOffset) = 25;
		*(int*)(DWORD(FortHero) + Offsets::HeroXPOffset) = 300;
		*(FString*)(DWORD(FortHero) + Offsets::HeroNameOffset) = L"Rescue Trooper Ramirez";
		*(int*)(DWORD(FortHero) + Offsets::HeroGenderOffset) = 2;
		
		SetPersonalHeroChoice(FortHero);
	}

	void SetRatings()
	{
		auto HomeBaseRatingWidget = FindObject(L"HomeBaseRatingWidget_C /Engine/Transient.FortEngine_0.FortGameInstance_0.HomeBase_C_0.WidgetTree_1.TopBar.WidgetTree_475.HomeBaseRatingWidget");
		auto MtxCurrencyWidget = FindObject(L"MtxCurrency_Widget_C /Engine/Transient.FortEngine_0.FortGameInstance_0.HomeBase_C_0.WidgetTree_1.TopBar.WidgetTree_475.TopBar_MtxCurrency_Widget");

		Offsets::CurrentSelfValueOffset = FindOffset(L"IntProperty /Game/UI/HomeBase/HomeBaseRatingWidget.HomeBaseRatingWidget_C.CurrentSelfValue");
		Offsets::CurrentTeamValueOffset = FindOffset(L"IntProperty /Game/UI/HomeBase/HomeBaseRatingWidget.HomeBaseRatingWidget_C.CurrentTeamValue");
		Offsets::CurrentTotalValueOffset = FindOffset(L"IntProperty /Game/UI/HomeBase/HomeBaseRatingWidget.HomeBaseRatingWidget_C.CurrentTotalValue");

		*(int*)(DWORD(HomeBaseRatingWidget) + Offsets::CurrentSelfValueOffset) = 7921;
		*(int*)(DWORD(HomeBaseRatingWidget) + Offsets::CurrentTeamValueOffset) = 5684;
		*(int*)(DWORD(HomeBaseRatingWidget) + Offsets::CurrentTotalValueOffset) = 13605;

		UpdateRatingWidget(HomeBaseRatingWidget);
		UpdateMtxWidget(MtxCurrencyWidget, 500);

		*(bool*)(DWORD(Offsets::PlayerController) + Offsets::bTutorialCompletedOffset) = true;
	}

	// I tried to load all the account items with JonLHack but I got the memory error 💀. Try it if you want or put all the items you want in a llama
	void GiveAccountItems()
	{
		for (int i = 0; i < GObjects->ObjObjects.NumElements; i++)
		{
			auto Object = GObjects->ObjObjects.Objects[i].Object;
			auto ClassName = GetName(Object->Class);
			if (ClassName == L"Class /Script/FortniteGame.FortHeroType" ||
				ClassName == L"Class /Script/FortniteGame.FortWorkerType" ||
				ClassName == L"Class /Script/FortniteGame.FortPersistentResourceItemDefinition" ||
				ClassName == L"Class /Script/FortniteGame.FortSchematicItemDefinition")
			{
				if (!(GetName(Object).find(L"Default") != std::string::npos))
				GivePlayerLocalAccountItem(Object);
			}
		}
	}

	void DestroyBuildingTooltips()
	{		
		struct Params
		{
			UObject* Object;
		};
#
		Params params;

		for (int i = 0; i < GObjects->ObjObjects.NumElements; i++)
		{
			auto Object = GObjects->ObjObjects.Objects[i].Object;

			if (Object)
			{
				if (GetName(Object).find(L"HB_") != std::string::npos && GetName(Object).find(L"WidgetComponent") != std::string::npos)
				{
					params.Object = Object;
					ProcessEvent(Object, Object, Offsets::DestroyComponentFunc, &params);
				}
			}
		}
	}

	void OpenLlama()
	{
		ProcessEvent(Offsets::StorePinataMaster, Offsets::StorePinataMaster, Offsets::StartPackOpenFunc, nullptr);
	}
}