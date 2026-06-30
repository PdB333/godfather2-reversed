#include <cstdint>

struct FUN_00405c70_SourceEntry
{
    std::int32_t nameOrId;   // [0x00]
    std::int32_t hashedKey;  // [0x04]
    std::int32_t value;      // [0x08]
    std::int32_t unk0C;      // [0x0C]
    std::int32_t unk10;      // [0x10]
};

struct FUN_00405c70_TargetEntry
{
    std::int32_t handle;     // [0x00]
    std::int32_t namePtr;    // [0x04]
    std::uint16_t unk08;     // [0x08]
    std::uint8_t flags0A;    // [0x0A]
    std::uint8_t pad0B;      // [0x0B]
    std::int32_t value0C;    // [0x0C]
};

struct FUN_00405c70_TargetTable
{
    std::uint8_t pad00[0x08];
    std::uint16_t entryCount;    // [0x08]
    std::uint8_t pad0A[0x06];
    FUN_00405c70_TargetEntry entries[1]; // [0x10]
};

struct FUN_00405c70_Object
{
    std::uint8_t pad00[0x44];
    FUN_00405c70_SourceEntry* entries44; // [0x44]
    std::uint32_t entryCount48;          // [0x48]
};

extern "C" std::int32_t __cdecl FUN_004a8180(std::int32_t param_1, std::int32_t param_2);
extern "C" char DAT_00e2f0a0[4];

void __thiscall FUN_00405c70(FUN_00405c70_Object* this_, FUN_00405c70_TargetTable* param_2)
{
    std::uint32_t local_c = 0;

    if (this_->entryCount48 != 0)
    {
        std::int32_t local_10 = 0;

        do
        {
            auto* piVar8 = reinterpret_cast<FUN_00405c70_SourceEntry*>(
                reinterpret_cast<std::uint8_t*>(this_->entries44) + local_10);

            if (piVar8->nameOrId == 0)
            {
                auto* piVar4 = reinterpret_cast<std::int32_t*>(&param_2->entries[0]);

                do
                {
                    auto* piVar3 = piVar4;

                    if ((reinterpret_cast<std::int32_t*>(&param_2->entries[0]) +
                         static_cast<std::uint32_t>(param_2->entryCount) * 5 <= piVar3) ||
                        (*reinterpret_cast<std::int32_t*>(*piVar3) != 0))
                    {
                        goto LAB_00405d6b;
                    }

                    if (piVar8->hashedKey == 0)
                    {
                        break;
                    }

                    auto* pbVar7 = reinterpret_cast<std::uint8_t*>(
                        reinterpret_cast<std::int32_t*>(*piVar3)[1]);
                    std::int32_t iVar6 = 0;

                    if (pbVar7 != nullptr)
                    {
                        std::uint8_t bVar1 = *pbVar7;

                        while (bVar1 != 0)
                        {
                            std::uint32_t uVar5 = static_cast<std::uint32_t>(bVar1);
                            pbVar7 = pbVar7 + 1;

                            if (uVar5 - 0x41 < 0x1a)
                            {
                                uVar5 = uVar5 + 0x20;
                            }

                            iVar6 = iVar6 * 0x1003f + static_cast<std::int32_t>(uVar5);
                            bVar1 = *pbVar7;
                        }
                    }

                    pbVar7 = reinterpret_cast<std::uint8_t*>(&DAT_00e2f0a0);

                    do
                    {
                        std::uint32_t uVar5 = static_cast<std::uint32_t>(*pbVar7);

                        if (uVar5 - 0x41 < 0x1a)
                        {
                            uVar5 = uVar5 + 0x20;
                        }

                        pbVar7 = pbVar7 + 1;
                        iVar6 = iVar6 * 0x1003f + static_cast<std::int32_t>(uVar5);
                    } while (pbVar7 < reinterpret_cast<std::uint8_t*>(&DAT_00e2f0a0 + 4));

                    piVar4 = piVar3 + 5;
                } while (iVar6 != piVar8->hashedKey);

                const std::int32_t iVar6 = piVar8->value;
                reinterpret_cast<FUN_00405c70_TargetEntry*>(piVar3)->flags0A =
                    static_cast<std::uint8_t>(
                        reinterpret_cast<FUN_00405c70_TargetEntry*>(piVar3)->flags0A | 0x20);
                reinterpret_cast<FUN_00405c70_TargetEntry*>(piVar3)->value0C = iVar6;
            }
            else
            {
                const std::int32_t iVar6 = FUN_004a8180(piVar8->nameOrId, 0);

                if (iVar6 != 0)
                {
                    const std::int32_t iVar2 = piVar8->value;
                    *reinterpret_cast<std::uint8_t*>(iVar6 + 10) =
                        static_cast<std::uint8_t>(*reinterpret_cast<std::uint8_t*>(iVar6 + 10) | 0x20);
                    *reinterpret_cast<std::int32_t*>(iVar6 + 0x0c) = iVar2;
                }
            }

        LAB_00405d6b:
            local_10 = local_10 + 0x14;
            local_c = local_c + 1;
        } while (local_c < this_->entryCount48);
    }
}