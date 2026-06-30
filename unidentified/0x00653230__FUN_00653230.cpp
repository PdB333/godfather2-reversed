#include <cstdint>
#include <cstdlib>

using undefined4 = std::uint32_t;
using undefined = std::uint8_t;

extern "C" char FUN_00653da0();
extern "C" void FUN_0064b810(std::uint32_t value, void* data);
extern "C" char FUN_0064b7c0();

extern std::uint32_t DAT_00e2dd14;

struct BitstreamWriter {
    undefined pad00[0x0c];
    std::uint8_t* buffer;      // 0x0c
    undefined pad10[0x08];
    std::uint32_t bitIndex;    // 0x18
    undefined pad1c[0x14];
    std::uint32_t capacity;    // 0x30
};

struct OwnerSubobject {
    undefined pad00[100];
    std::int32_t endPtr;       // 0x64
};

struct EncoderState {
    undefined pad00[0x10];
    undefined4 recentValues[32]; // 0x10
    undefined pad90[0x90 - 0x10 - sizeof(recentValues)];
    std::int32_t currentPtr;      // 0x90
    undefined pad94[0x04];
    undefined4 entryCount;        // 0x98
    undefined4 payloadWords[1];   // 0x9c, variable-length payload begins here
    undefined padA0_to_1A4[0x1a4 - 0xa0];
    OwnerSubobject* owner;        // 0x1a4
};

extern "C" void __fastcall FUN_00653230(EncoderState* self, BitstreamWriter* writer, undefined4* param_2)
{
    undefined4* local_8;
    undefined4 local_4;
    std::int32_t local_c;
    std::uint32_t uVar5;
    undefined4* puVar6;
    std::uint32_t uVar7;
    std::uint32_t uVar8;

    const char cVar4 = FUN_00653da0();
    if ((cVar4 != '\0') && (param_2 == nullptr)) {
#if defined(_MSC_VER) && defined(_M_IX86)
        __debugbreak();
#else
        std::raise(SIGTRAP);
#endif
        return;
    }

    puVar6 = reinterpret_cast<undefined4*>(
        (static_cast<std::uint32_t>((self->currentPtr - *reinterpret_cast<std::int32_t*>(
            reinterpret_cast<std::uint8_t*>(self) + 0xa0)) + 7U)) >> 3
    );

    if (param_2 == nullptr) {
        self->entryCount = self->entryCount + 1;
    }

    local_8 = param_2;
    FUN_0064b810(2, &local_8);

    local_8 = reinterpret_cast<undefined4*>(self->entryCount);
    FUN_0064b810(5, &local_8);

    if (writer->capacity < writer->bitIndex + 1U) {
        const char grew = FUN_0064b7c0();
        if (grew == '\0') {
            goto LAB_006532cd;
        }
    }

    {
        std::uint8_t* const pbVar1 =
            reinterpret_cast<std::uint8_t*>((writer->bitIndex >> 3) + reinterpret_cast<std::uintptr_t>(writer->buffer));
        *pbVar1 = static_cast<std::uint8_t>(
            *pbVar1 | (static_cast<std::uint8_t>(1U << (static_cast<std::uint8_t>(writer->bitIndex) & 7)))
        );
        writer->bitIndex = writer->bitIndex + 1;
    }

LAB_006532cd:
    local_8 = reinterpret_cast<undefined4*>(self->entryCount >> 5);
    FUN_0064b810(6, &local_8);

    local_8 = reinterpret_cast<undefined4*>(self->currentPtr);
    FUN_0064b810(10, &local_8);

    local_8 = nullptr;
    FUN_0064b810(0, &local_8);

    local_8 = puVar6;
    FUN_0064b810(static_cast<std::uint8_t>(static_cast<std::int8_t>(DAT_00e2dd14 >> 0x17) + static_cast<std::int8_t>(-0x7e)), &local_8);

    uVar7 = (static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(puVar6)) + 3U) >> 2;
    uVar8 = 0;
    if (uVar7 != 0) {
        local_8 = reinterpret_cast<undefined4*>(reinterpret_cast<std::uint8_t*>(self) + 0x9c);
        local_c = 0;
        do {
            if (uVar8 == uVar7 - 1) {
                uVar5 = static_cast<std::uint32_t>(
                    (static_cast<std::int32_t>(reinterpret_cast<std::intptr_t>(puVar6)) - local_c) * 8
                );
            } else {
                uVar5 = 0x20;
            }

            local_4 = *local_8;
            FUN_0064b810(uVar5 & 0xff, &local_4);

            local_c = local_c + 4;
            local_8 = local_8 + 1;
            uVar8 = uVar8 + 1;
        } while (uVar8 < uVar7);
    }

    {
        std::uint32_t param_1 = static_cast<std::uint32_t>(
            self->owner->endPtr - *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(self) + 0x0c)
        );

        if (0x7ff < param_1) {
            param_1 = 0x7ff;
        }

        param_1 = param_1 >> 3;
        FUN_0064b810(8, &param_1);
    }

    if (param_2 == nullptr) {
        self->recentValues[self->entryCount & 0x1f] = static_cast<undefined4>(self->currentPtr);
    }
}