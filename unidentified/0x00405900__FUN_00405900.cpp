#include <cstdint>

using DestructorFn = void(__cdecl*)(std::int32_t);

void __cdecl FUN_00402e90(void* outContext, std::int32_t param_2, std::uint32_t param_3);
std::int32_t __cdecl FUN_004d4b20(const void* context);
std::int32_t __cdecl FUN_00405650();

struct FUN_00405900_LocalContext
{
    std::int32_t value0;
    std::int32_t value1;
    std::int32_t value2;
    DestructorFn destructor;
};

struct FUN_00405900_ResultHolder
{
    std::uint8_t gap_00[0x1c];
    std::uint32_t value; // [0x1c]
};

struct FUN_00405900_Object
{
    std::uint8_t gap_00[0x80];
    FUN_00405900_ResultHolder* resultHolder; // [0x80]
};

std::uint32_t __thiscall FUN_00405900(FUN_00405900_Object* this_, std::int32_t param_2, std::uint32_t param_3)
{
    if (param_2 == 0)
    {
        return 0;
    }

    FUN_00405900_LocalContext localContext{};
    FUN_00402e90(&localContext, param_2, param_3);

    FUN_00405900_ResultHolder* resultHolder;
    if (this_->resultHolder == nullptr)
    {
        resultHolder = reinterpret_cast<FUN_00405900_ResultHolder*>(FUN_00405650());
        if (resultHolder == nullptr)
        {
            resultHolder = reinterpret_cast<FUN_00405900_ResultHolder*>(FUN_00405650());
            if (resultHolder == nullptr)
            {
                if (localContext.value0 != 0)
                {
                    localContext.destructor(localContext.value0);
                }
                return 0;
            }
        }
    }
    else
    {
        const std::int32_t lookupResult = FUN_004d4b20(&localContext);
        resultHolder = this_->resultHolder;
        if ((lookupResult != 0) || (resultHolder == nullptr))
        {
            resultHolder = reinterpret_cast<FUN_00405900_ResultHolder*>(FUN_00405650());
            if (resultHolder == nullptr)
            {
                resultHolder = reinterpret_cast<FUN_00405900_ResultHolder*>(FUN_00405650());
                if (resultHolder == nullptr)
                {
                    if (localContext.value0 != 0)
                    {
                        localContext.destructor(localContext.value0);
                    }
                    return 0;
                }
            }
        }
    }

    const std::uint32_t result = resultHolder->value;

    if (localContext.value0 != 0)
    {
        localContext.destructor(localContext.value0);
    }

    return result;
}