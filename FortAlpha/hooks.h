#include "frontend.h"

void* __fastcall ProcessEventHook(UObject* _Object, UObject* Object, UObject* Function, void* Params)
{
    if (Object && Function)
    {
        std::wstring ObjectName = GetObjectFirstName(_Object);
        std::wstring FunctionName = GetObjectFirstName(Function);
        
        if (FunctionName.find(L"ShowStoreChanged") != std::string::npos)
            return NULL;
        if (FunctionName.find(L"PlayZoneChanged") != std::string::npos)
            return NULL;
        if (FunctionName.find(L"ShowHeroListChanged") != std::string::npos)
            return NULL;
        if (FunctionName.find(L"ShowVaultChanged") != std::string::npos)
        {
            Frontend::DestroyBuildingTooltips();
            return NULL;
        }
        if (FunctionName.find(L"ShowDailyRewardsChanged") != std::string::npos)
            return NULL;
        if (FunctionName.find(L"Party Bar Feature Changed") != std::string::npos)
        {
            Frontend::GiveAccountItems();
            Frontend::SetupHeroMenu();
            Frontend::SetRatings();
            return NULL;
        }
        if (FunctionName.find(L"ShowHomeBaseChanged") != std::string::npos)
            return NULL;
        if (FunctionName.find(L"HomeBaseOverviewFeature") != std::string::npos)
            return NULL;
        
        if (ObjectName.find(L"S_HB_OnboardingCloudCover_C") != std::string::npos && FunctionName.find(L"UserConstructionScript") != std::string::npos)
        {
            ControlCloudsUpdate();
            SetActorHiddenInGame(_Object, true);
        }

        // Scuffed as hell but it looks clean
        if (ObjectName.find(L"HB_") != std::string::npos && FunctionName.find(L"ReceiveBeginPlay") != std::string::npos)
                return NULL;

        if (ObjectName.find(L"HomeBaseRatingWidget") != std::string::npos && FunctionName.find(L"Update") != std::string::npos)
            return NULL;

        if (FunctionName.find(L"BuyOnePack") != std::string::npos)
        {
            OpenLlama();
            SetShowHUD(false);
            return NULL;
        }

        if (FunctionName.find(L"TL-ChangeLighting__FinishedFunc") != std::string::npos)
            SetShowHUD(true);
    }

    return ProcessEvent(_Object, Object, Function, Params);
}

namespace Hooks
{
    void Init()
    {
        MH_Initialize();
        
        MH_CreateHook(reinterpret_cast<PVOID*>(Offsets::ProcessEventAddress), ProcessEventHook, reinterpret_cast<PVOID*>(&ProcessEvent));
        MH_EnableHook(reinterpret_cast<PVOID*>(Offsets::ProcessEventAddress));
    }
}