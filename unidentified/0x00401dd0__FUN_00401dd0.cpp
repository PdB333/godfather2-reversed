#include <cstddef>

extern void FUN_004d41f0(void* param_1, const char* param_2, int param_3, int param_4);

void __fastcall FUN_00401dd0(unsigned int /*param_1*/, char* param_2, unsigned int /*param_3*/, void* param_4)
{
    if (param_2 != nullptr) {
        char* pcVar2 = param_2;
        char cVar1;

        do {
            cVar1 = *pcVar2;
            pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');

        FUN_004d41f0(param_4, param_2, 0, static_cast<int>(pcVar2 - (param_2 + 1)));
        return;
    }

    FUN_004d41f0(param_4, nullptr, 0, 0);
    return;
}