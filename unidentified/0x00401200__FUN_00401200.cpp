#include <cstdint>

// No verified project type information was provided for the object at param_1,
// so preserve the original symbol name and model the write exactly as a raw
// member store at offset 0x40.
void __thiscall FUN_00401200(std::uintptr_t param_1, std::uint32_t param_2)
{
    *reinterpret_cast<std::uint32_t*>(param_1 + 0x40) = param_2;
}