#include <cstdint>

std::int32_t __cdecl FUN_004025a0(std::uint32_t param_1);

struct FUN_00405870_Entry
{
    std::uint8_t gap_00[0x8];
    std::uint8_t* value; // [0x8]
};

std::uint8_t DAT_0120546e;

std::uint8_t* __cdecl FUN_00405870(std::uint32_t param_1)
{
    const std::int32_t entryAddress = FUN_004025a0(param_1);

    if (entryAddress == 0)
    {
        return nullptr;
    }

    std::uint8_t* result = reinterpret_cast<FUN_00405870_Entry*>(entryAddress)->value;
    if (result == nullptr)
    {
        return &DAT_0120546e;
    }

    return result;
}