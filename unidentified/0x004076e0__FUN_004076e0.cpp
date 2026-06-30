#include <cstdint>

extern "C" void FUN_009c8eb0(void* ptr);

struct FUN_004076e0_Object
{
    void* instance;                                   // [0x00]
    std::uint32_t field_0x04;                         // [0x04]
    std::uint32_t field_0x08;                         // [0x08]
    void (__thiscall* destroy)(void* instance);       // [0x0C]
};

extern "C" FUN_004076e0_Object* __thiscall FUN_004076e0(
    FUN_004076e0_Object* param_1,
    std::uint8_t param_2)
{
    if (param_1->instance != nullptr) {
        param_1->destroy(param_1->instance);
    }

    if ((param_2 & 1) != 0) {
        FUN_009c8eb0(param_1);
    }

    return param_1;
}