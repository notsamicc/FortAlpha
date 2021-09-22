#include "ue4.h"

namespace Offsets
{
	DWORD ViewportConsoleOffset;
	DWORD CurrentTotalValueOffset;
	DWORD CurrentSelfValueOffset;
	DWORD CurrentTeamValueOffset;
	DWORD OwningGameInstanceOffset;
	DWORD LocalPlayersOffset;
	DWORD PlayerControllerOffset;
	DWORD HeroLevelOffset;
	DWORD HeroXPOffset;
	DWORD HeroNameOffset;
	DWORD HeroGenderOffset;
	DWORD bTutorialCompletedOffset;
	DWORD ProcessEventAddress;

	UObject* GameplayStatics;
	UObject* PlayerController;
	UObject* FrontendContext;
	UObject* GameViewportClient;
	UObject* StorePinataMaster;
	
	UObject* SpawnObjectFunc;
	UObject* GivePlayerLocalAccountItemFunc;
	UObject* SetPersonalHeroChoiceFunc;
	UObject* ControlCloudsUpdateFunc;
	UObject* SetActorHiddenInGameFunc;
	UObject* DestroyComponentFunc;
	UObject* StartPackOpenFunc;
	UObject* SetShowHUDFunc;

	void Init()
	{
		GObjects = (FUObjectArray*)(Util::BaseAddress() + 0x2DC3AAC);
		ProcessEventAddress = Util::BaseAddress() + 0x9A9E70;
		ProcessEvent = (fProcessEvent)(ProcessEventAddress);
		GetObjectName_Internal = (fGetObjectName_Internal)(Util::BaseAddress() + 0x132C400);
		Free_Internal = (fFree_Internal)(Util::BaseAddress() + 0x89CAD0);

		HeroLevelOffset = FindOffset(L"IntProperty /Script/FortniteGame.FortAccountItem.Level");
		HeroXPOffset = FindOffset(L"IntProperty /Script/FortniteGame.FortAccountItem.XP");
		HeroNameOffset = FindOffset(L"StrProperty /Script/FortniteGame.FortHero.Hero_Name");
		HeroGenderOffset = FindOffset(L"IntProperty /Script/FortniteGame.FortWorker.Gender");
		ViewportConsoleOffset = FindOffset(L"ObjectProperty /Script/Engine.GameViewportClient.ViewportConsole");
		bTutorialCompletedOffset = FindOffset(L"BoolProperty /Script/FortniteGame.FortPlayerController.bTutorialCompleted");

		GameplayStatics = FindObject(L"GameplayStatics /Script/Engine.Default__GameplayStatics");
		PlayerController = FindObject(L"FortPlayerControllerFrontEnd /Game/Maps/FortniteEntry.FortniteEntry.PersistentLevel.FortPlayerControllerFrontEnd_0");
		FrontendContext = FindObject(L"FortFrontEndContext /Engine/Transient.FortEngine_0.FortLocalPlayer_0.FortFrontEndContext_0");
		GameViewportClient = FindObject(L"FortGameViewportClient /Engine/Transient.FortEngine_0.FortGameViewportClient_0");

		SpawnObjectFunc = FindObject(L"Function /Script/Engine.GameplayStatics.SpawnObject");
		GivePlayerLocalAccountItemFunc = FindObject(L"Function /Script/FortniteGame.FortPlayerController.ClientGivePlayerLocalAccountItem");
		FrontendContext = FindObject(L"FortFrontEndContext /Engine/Transient.FortEngine_0.FortLocalPlayer_0.FortFrontEndContext_0");
		SetPersonalHeroChoiceFunc = FindObject(L"Function /Script/FortniteUI.FortFrontEndContext.SetPersonalHeroChoice");
		ControlCloudsUpdateFunc = FindObject(L"Function /Game/Environments/Homebase/Blueprints/Onboarding/S_HB_OnboardingCloudCover.S_HB_OnboardingCloudCover_C.Control_Clouds_Phase02__UpdateFunc");
		SetActorHiddenInGameFunc = FindObject(L"Function /Script/Engine.Actor.SetActorHiddenInGame");
		DestroyComponentFunc = FindObject(L"Function /Script/Engine.ActorComponent.K2_DestroyComponent");
		StartPackOpenFunc = FindObject(L"Function /Game/FrontEnd/Store/Pinata/Blueprints/StorePinataMaster_BP.StorePinataMaster_BP_C.StartPackOpen");
		SetShowHUDFunc = FindObject(L"Function /Script/FortniteGame.FortPlayerController.SetShowHUD");
	}
}