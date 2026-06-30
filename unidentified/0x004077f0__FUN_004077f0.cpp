#include <cstdint>

extern "C" int FUN_009c8e80(std::uint32_t size);
extern "C" void FUN_009c8f10(int ptr);

extern "C" void __thiscall FUN_004077f0(int* self, std::uint32_t param_1)
{
    int iVar1;
    std::uint32_t* puVar2;
    std::uint32_t* puVar3;
    std::uint32_t uVar4;

    if (static_cast<std::uint32_t>(self[2]) < param_1) {
        iVar1 = FUN_009c8e80(param_1 * 0x14);

        if (*self != 0) {
            uVar4 = 0;

            if (self[1] != 0) {
                puVar2 = reinterpret_cast<std::uint32_t*>(iVar1 + 8);

                do {
                    puVar3 = reinterpret_cast<std::uint32_t*>(
                        (int)puVar2 + *self + (-8 - iVar1)
                    );

                    if (puVar2 != reinterpret_cast<std::uint32_t*>(0x8)) {
                        puVar2[-2] = puVar3[0];
                        puVar2[-1] = puVar3[1];
                        puVar2[0]  = puVar3[2];
                        puVar2[1]  = puVar3[3];
                        puVar2[2]  = puVar3[4];
                    }

                    uVar4 = uVar4 + 1;
                    puVar2 = puVar2 + 5;
                } while (uVar4 < static_cast<std::uint32_t>(self[1]));
            }

            FUN_009c8f10(*self);
        }

        *self = iVar1;
        self[2] = static_cast<int>(param_1);
    }
}