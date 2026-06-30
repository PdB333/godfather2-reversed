#include <cstdint>

using ushort = std::uint16_t;
using uint = std::uint32_t;

#pragma pack(push, 1)
struct DAT_01161380_Record
{
    ushort next;      // +0x0
    ushort bits;      // +0x2
    int owner;        // +0x4
};
#pragma pack(pop)

extern DAT_01161380_Record DAT_01161380[];
extern ushort DAT_0110ae8c;

void FUN_004029a0(ushort* param_1)
{
    ushort* puVar1;
    ushort in_AX;
    ushort uVar2;
    uint uVar3;
    uint uVar4;
    int unaff_EDI;

    uVar2 = *param_1;
    uVar4 = 0xffff;
    if (uVar2 != 0xffff) {
        while (true) {
            uVar3 = (uint)uVar2;
            puVar1 = &(&DAT_01161380[0].next)[uVar3 * 4];
            if (*(int*)(&DAT_01161380[0].owner + uVar3 * 2) == unaff_EDI) break;
            uVar4 = (uint)uVar2;
            uVar2 = *puVar1;
            if (uVar2 == 0xffff) {
                return;
            }
        }
        *(ushort*)(&DAT_01161380[0].bits + uVar3 * 4) =
            *(ushort*)(&DAT_01161380[0].bits + uVar3 * 4) & (ushort)~in_AX;
        if (*(short*)(&DAT_01161380[0].bits + uVar3 * 4) == 0) {
            if ((short)uVar4 == -1) {
                *param_1 = *puVar1;
                *puVar1 = DAT_0110ae8c;
                DAT_0110ae8c = uVar2;
                return;
            }
            (&DAT_01161380[0].next)[uVar4 * 4] = *puVar1;
            *puVar1 = DAT_0110ae8c;
            DAT_0110ae8c = uVar2;
        }
    }
    return;
}