#include <cstdint>

using VectorConstructorCallback = void(__thiscall*)(void*);

extern "C" void __stdcall _vector_constructor_iterator_(
    void* param_1,
    std::uint32_t param_2,
    int param_3,
    VectorConstructorCallback param_4)
{
    (void)param_1;
    (void)param_2;

    void* unaff_ESI;
    int iVar1 = param_3 + -1;

    for (; -1 < iVar1; iVar1 = iVar1 + -1) {
        param_4(unaff_ESI);
    }
}