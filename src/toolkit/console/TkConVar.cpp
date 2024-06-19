#include <toolkit/console/TkConManager.h>
#include <toolkit/console/TkConVar.h>

#pragma region Constructors

cTkConVar<u8>::cTkConVar(cTkString lsName, cTkString lsDescription, u8 lDefaultValue, eTkConFlags lxFlags)
    : cTkConObject(lsName, lsDescription, lxFlags), mValue(lDefaultValue)
{
    cTkConManager &gConManager = cTkConManager::GetInstance();

    gConManager.AddCVar<u8>(this);
}

cTkConVar<u16>::cTkConVar(cTkString lsName, cTkString lsDescription, u16 lDefaultValue, eTkConFlags lxFlags)
    : cTkConObject(lsName, lsDescription, lxFlags), mValue(lDefaultValue)
{
    cTkConManager &gConManager = cTkConManager::GetInstance();

    gConManager.AddCVar<u16>(this);
}

cTkConVar<u32>::cTkConVar(cTkString lsName, cTkString lsDescription, u32 lDefaultValue, eTkConFlags lxFlags)
    : cTkConObject(lsName, lsDescription, lxFlags), mValue(lDefaultValue)
{
    cTkConManager &gConManager = cTkConManager::GetInstance();

    gConManager.AddCVar<u32>(this);
}

cTkConVar<u64>::cTkConVar(cTkString lsName, cTkString lsDescription, u64 lDefaultValue, eTkConFlags lxFlags)
    : cTkConObject(lsName, lsDescription, lxFlags), mValue(lDefaultValue)
{
    cTkConManager &gConManager = cTkConManager::GetInstance();

    gConManager.AddCVar<u64>(this);
}

cTkConVar<i8>::cTkConVar(cTkString lsName, cTkString lsDescription, i8 lDefaultValue, eTkConFlags lxFlags)
    : cTkConObject(lsName, lsDescription, lxFlags), mValue(lDefaultValue)
{
    cTkConManager &gConManager = cTkConManager::GetInstance();

    gConManager.AddCVar<i8>(this);
}

cTkConVar<i16>::cTkConVar(cTkString lsName, cTkString lsDescription, i16 lDefaultValue, eTkConFlags lxFlags)
    : cTkConObject(lsName, lsDescription, lxFlags), mValue(lDefaultValue)
{
    cTkConManager &gConManager = cTkConManager::GetInstance();

    gConManager.AddCVar<i16>(this);
}

cTkConVar<i32>::cTkConVar(cTkString lsName, cTkString lsDescription, i32 lDefaultValue, eTkConFlags lxFlags)
    : cTkConObject(lsName, lsDescription, lxFlags), mValue(lDefaultValue)
{
    cTkConManager &gConManager = cTkConManager::GetInstance();

    gConManager.AddCVar<i32>(this);
}

cTkConVar<i64>::cTkConVar(cTkString lsName, cTkString lsDescription, i64 lDefaultValue, eTkConFlags lxFlags)
    : cTkConObject(lsName, lsDescription, lxFlags), mValue(lDefaultValue)
{
    cTkConManager &gConManager = cTkConManager::GetInstance();

    gConManager.AddCVar<i64>(this);
}

cTkConVar<f32>::cTkConVar(cTkString lsName, cTkString lsDescription, f32 lDefaultValue, eTkConFlags lxFlags)
    : cTkConObject(lsName, lsDescription, lxFlags), mValue(lDefaultValue)
{
    cTkConManager &gConManager = cTkConManager::GetInstance();

    gConManager.AddCVar<f32>(this);
}

cTkConVar<f64>::cTkConVar(cTkString lsName, cTkString lsDescription, f64 lDefaultValue, eTkConFlags lxFlags)
    : cTkConObject(lsName, lsDescription, lxFlags), mValue(lDefaultValue)
{
    cTkConManager &gConManager = cTkConManager::GetInstance();

    gConManager.AddCVar<f64>(this);
}

cTkConVar<cTkString>::cTkConVar(cTkString lsName, cTkString lsDescription, cTkString lDefaultValue, eTkConFlags lxFlags)
    : cTkConObject(lsName, lsDescription, lxFlags), mValue(lDefaultValue)
{
    cTkConManager &gConManager = cTkConManager::GetInstance();

    gConManager.AddCVar<cTkString>(this);
}

#pragma endregion