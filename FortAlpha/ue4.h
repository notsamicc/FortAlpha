#include "util.h"

template<class T>
struct TArray
{
    friend struct FString;

public:
    inline TArray()
    {
        Data = nullptr;
        Count = Max = 0;
    };

    inline int Num() const
    {
        return Count;
    };

    inline T& operator[](int i)
    {
        return Data[i];
    };

    inline const T& operator[](int i) const
    {
        return Data[i];
    };

    inline bool IsValidIndex(int i) const
    {
        return i < Num();
    }

    void Add(T InputData)
    {
        Data = (T*)realloc(Data, sizeof(T) * (Count + 1));
        Data[Count++] = InputData;
        Max = Count;
    };

    T* Data;
    int32_t Count;
    int32_t Max;
};

struct FString : private TArray<wchar_t>
{
    FString()
    {
        Data = nullptr;

        Max = Count = 0;
    }

    FString(const wchar_t* Value)
    {
        Max = Count = *Value ? std::wcslen(Value) + 1 : 0;

        if (Count)
        {
            Data = const_cast<wchar_t*>(Value);
        }
    };

    inline bool IsValid()
    {
        return Data != nullptr;
    }

    inline wchar_t* c_str()
    {
        return Data;
    }

    std::string ToString() const
    {
        size_t length = std::wcslen(Data);
        std::string str(length, '\0');
        std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

        return str;
    }
};

struct FName
{
public:
    int32_t ComparisonIndex;
    int32_t Number;
};

struct UObject
{
    void** VTable;
    int32_t ObjectFlags;
    int32_t InternalIndex;
    UObject* Class;
    FName Name;
    UObject* Outer;
};

class FUObjectItem
{
public:
    UObject* Object;
    int32_t ClusterIndex;
    int32_t SerialNumber;
};

class TUObjectArray
{
public:
    FUObjectItem* Objects;
    int32_t MaxElements;
    int32_t NumElements;
};

class FUObjectArray
{
public:
    TUObjectArray ObjObjects;
};

FUObjectArray* GObjects;

typedef void* (__fastcall* fProcessEvent)(UObject* _Object, UObject* Object, UObject* Function, void* Params);
fProcessEvent ProcessEvent;

typedef FString(__cdecl* fGetObjectName_Internal)(UObject* Object);
static fGetObjectName_Internal GetObjectName_Internal;

typedef void(__cdecl* fFree_Internal)(void* Buffer);
static fFree_Internal Free_Internal;

static std::wstring GetObjectName(UObject* Object)
{
    std::wstring sName(L"");

    for (auto i = 0; Object; Object = Object->Outer, ++i)
    {
        FString objName = GetObjectName_Internal(Object);

        if (objName.IsValid())
        {
            sName = objName.c_str() + std::wstring(i > 0 ? L"." : L"") + sName;

            Free_Internal(objName.c_str());
        }
    }

    return sName;
}

static std::wstring GetObjectFirstName(UObject* Object)
{
    std::wstring sName(L"");

    FString objName = GetObjectName_Internal(Object);

    if (objName.IsValid())
    {
        sName = objName.c_str();

        Free_Internal(objName.c_str());
    }

    return sName;
}

std::wstring GetName(UObject* obj)
{
    std::wstring name;

    if (obj->Class != nullptr)
    {
        name = GetObjectFirstName((UObject*)obj->Class);
        name += L" ";
        name += GetObjectName(obj);
    }

    return name;
}

static UObject* FindObject(std::wstring name)
{
    for (int i = 0; i < GObjects->ObjObjects.NumElements; i++)
    {
        auto Object = GObjects->ObjObjects.Objects[i].Object;

        if (Object)
        {
            if (GetName(Object) == name)
            {
                return Object;
            }
        }
    }

    std::wcout << "Failed to find " << name << std::endl;
    return nullptr;
}

static DWORD FindOffset(std::wstring Offset)
{
    auto Object = FindObject(Offset);

    if (Object)
    {
        return *(DWORD*)(DWORD(Object) + 0x3C);
    }

    return 0;
}