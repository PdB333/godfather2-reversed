#include <cstddef>
#include <cstdint>

extern "C" std::int32_t FUN_004a8180(std::int32_t param_1, std::int32_t param_2);
extern "C" void FUN_004077f0(std::int32_t param_1);

struct FUN_004064d0_StringEntry
{
    const char* name;          // [0x00]
    std::uint32_t value;       // [0x04]
    std::uint32_t unknown_08;  // [0x08]
    std::uint32_t unknown_0c;  // [0x0C]
};

struct FUN_004064d0_RuntimeObject
{
    std::byte pad00[0x0A];
    std::uint8_t flags;              // [0x0A]
    std::byte pad0b[0x01];
    std::uint32_t stringEntryIndex;  // [0x0C]
};

struct FUN_004064d0_Record
{
    std::int32_t param_2_value;  // [0x00]
    std::int32_t param_4_value;  // [0x04]
    std::uint32_t entryIndex;    // [0x08]
    std::int32_t param_5_value;  // [0x0C]
    std::uint32_t param_6_value; // [0x10]
};

struct FUN_004064d0_State
{
    std::byte pad00[0x44];
    FUN_004064d0_Record* records;            // [0x44]
    std::int32_t recordCount;                // [0x48]
    std::int32_t recordCapacity;             // [0x4C]
    std::byte pad50[0xD4];
    std::uint32_t runtimeObjectRetryCount;   // [0x124]
    std::byte pad128[0x2C];
    FUN_004064d0_StringEntry* stringEntries; // [0x154]
    std::uint32_t stringEntryCount;          // [0x158]
};

std::uint32_t FUN_004064d0(
    std::int32_t param_1,
    std::int32_t param_2,
    FUN_004064d0_StringEntry* param_3,
    std::int32_t param_4,
    std::int32_t param_5,
    std::uint32_t param_6)
{
    FUN_004064d0_StringEntry* puVar1;
    std::uint8_t bVar2;
    std::uint8_t* pbVar3;
    std::int32_t iVar4;
    FUN_004064d0_Record* piVar5;
    std::uint8_t* pbVar6;
    FUN_004064d0_StringEntry* puVar7;
    std::uint32_t uVar8;
    std::uint32_t uVar9;
    bool bVar10;

    auto* const self = reinterpret_cast<FUN_004064d0_State*>(param_1);

    puVar1 = param_3;
    uVar8 = 0;
    param_3 = nullptr;
    uVar9 = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(param_3));
    if (self->stringEntryCount != 0) {
        puVar7 = self->stringEntries;
        do {
            if (puVar7[1].value == puVar1[1].value) {
                uVar9 = uVar8;
                if (puVar7[1].value == 0) {
                    break;
                }
                pbVar6 = reinterpret_cast<std::uint8_t*>(const_cast<char*>(puVar1->name));
                pbVar3 = reinterpret_cast<std::uint8_t*>(const_cast<char*>(puVar7->name));
                do {
                    bVar2 = *pbVar3;
                    bVar10 = bVar2 < *pbVar6;
                    if (bVar2 != *pbVar6) {
LAB_00406523:
                        iVar4 = (1 - static_cast<std::int32_t>(bVar10)) -
                                static_cast<std::int32_t>(bVar10 != false);
                        goto LAB_00406528;
                    }
                    if (bVar2 == 0) {
                        break;
                    }
                    bVar2 = pbVar3[1];
                    bVar10 = bVar2 < pbVar6[1];
                    if (bVar2 != pbVar6[1]) {
                        goto LAB_00406523;
                    }
                    pbVar3 = pbVar3 + 2;
                    pbVar6 = pbVar6 + 2;
                } while (bVar2 != 0);
                iVar4 = 0;
LAB_00406528:
                if (iVar4 == 0) {
                    break;
                }
            }
            uVar8 = uVar8 + 1;
            puVar7 = puVar7 + 4;
            uVar9 = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(param_3));
        } while (uVar8 < self->stringEntryCount);
    }

    param_3 = reinterpret_cast<FUN_004064d0_StringEntry*>(static_cast<std::uintptr_t>(uVar9));

    uVar9 = 0;
    do {
        if (self->runtimeObjectRetryCount <= uVar9) {
            break;
        }
        iVar4 = FUN_004a8180(param_2, 0);
        if (iVar4 != 0) {
            auto* const runtimeObject = reinterpret_cast<FUN_004064d0_RuntimeObject*>(iVar4);
            runtimeObject->flags = static_cast<std::uint8_t>(runtimeObject->flags | 0x20);
            runtimeObject->stringEntryIndex =
                static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(param_3));
        }
        uVar9 = uVar9 + 1;
    } while (iVar4 == 0);

    uVar9 = 0;
    if (static_cast<std::uint32_t>(self->recordCount) != 0) {
        piVar5 = self->records;
        do {
            if (((piVar5->param_2_value == param_2) && (piVar5->param_4_value == param_4)) &&
                (piVar5->param_5_value == param_5)) {
                if (piVar5->param_6_value < param_6) {
                    piVar5->entryIndex =
                        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(param_3));
                    piVar5->param_6_value = param_6;
                }
                return (static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(piVar5)) & 0xFFFFFF00U) | 1U;
            }
            uVar9 = uVar9 + 1;
            piVar5 = reinterpret_cast<FUN_004064d0_Record*>(reinterpret_cast<std::uint8_t*>(piVar5) + 0x14);
        } while (uVar9 < static_cast<std::uint32_t>(self->recordCount));
    }

    iVar4 = self->recordCapacity;
    if (self->recordCount == iVar4) {
        if (iVar4 == 0) {
            iVar4 = 1;
        }
        else {
            iVar4 = iVar4 * 2;
        }
        FUN_004077f0(iVar4);
    }

    puVar1 = reinterpret_cast<FUN_004064d0_StringEntry*>(
        reinterpret_cast<std::uintptr_t>(self->records) +
        static_cast<std::uintptr_t>(self->recordCount) * 0x14U);
    if (puVar1 != nullptr) {
        *reinterpret_cast<std::uint32_t*>(puVar1) = 0xFE16702FU;
    }

    piVar5 = reinterpret_cast<FUN_004064d0_Record*>(
        reinterpret_cast<std::uintptr_t>(self->records) +
        static_cast<std::uintptr_t>(self->recordCount) * 0x14U);
    self->recordCount = self->recordCount + 1;
    piVar5->param_4_value = param_4;
    piVar5->entryIndex = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(param_3));
    piVar5->param_2_value = param_2;
    piVar5->param_5_value = param_5;
    piVar5->param_6_value = param_6;
    return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(piVar5)) & 0xFFFFFF00U;
}