#include <cstdint>

struct FUN_00407b50_AllocatorVTable;

struct FUN_00407b50_Allocator
{
    FUN_00407b50_AllocatorVTable* vtable;                          // [0x00]
};

using FUN_00407b50_Allocate = std::uint32_t* (__thiscall*)(std::uint32_t, std::uint32_t);

struct FUN_00407b50_AllocatorVTable
{
    void* field_0x00;                                              // [0x00]
    FUN_00407b50_Allocate allocate;                                // [0x04]
};

struct FUN_00407b50_State
{
    std::uint32_t field_0x00;                                      // [0x00]
    std::uint32_t field_0x04;                                      // [0x04]
    std::uint32_t* headValue;                                      // [0x08]
    std::uint32_t field_0x0C;                                      // [0x0C]
    std::uint32_t field_0x10;                                      // [0x10]
    std::int32_t availableCount;                                   // [0x14]
    std::uint32_t lowWatermark;                                    // [0x18]
    FUN_00407b50_Allocator* allocator;                             // [0x1C]
};

extern "C" FUN_00407b50_State* DAT_01205204;

extern "C" std::uint32_t* FUN_00407b50()
{
    FUN_00407b50_State* const state = DAT_01205204;
    std::uint32_t* result = state->headValue;

    if (result != nullptr) {
        const std::uint32_t value = *result;

        state->availableCount = state->availableCount + -1;
        state->headValue = reinterpret_cast<std::uint32_t*>(static_cast<std::uintptr_t>(value));

        if (static_cast<std::uint32_t>(state->availableCount) < state->lowWatermark) {
            state->lowWatermark = static_cast<std::uint32_t>(state->availableCount);
        }

        return result;
    }

    if (state->allocator != nullptr) {
        return state->allocator->vtable->allocate(state->field_0x0C, state->field_0x10);
    }

    return nullptr;
}