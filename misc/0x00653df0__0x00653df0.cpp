#include <cstdint>

extern "C" int FUN_0065bf40();
extern "C" void FUN_00653150(int streamState);
extern "C" std::uint32_t FUN_00658230(int destination, std::uint32_t source, std::uint32_t qwordCount, int flags);
extern "C" void FUN_00654f70(std::uint32_t owner, void* bufferRegion, int streamState, int mode);

extern float DAT_00e2b05c;
extern double _DAT_00e44708;
extern double _DAT_00e448a8;

struct StreamState {
    std::uint8_t pad_00[0x0c];
    std::uint32_t source;            // 0x0c
    std::uint8_t pad_10[0x08];
    int length;                      // 0x18
    std::uint8_t flag1c;             // 0x1c
    std::uint8_t flag1d;             // 0x1d
    std::uint8_t pad_1e[0x0e];
    std::uint32_t alignedLength;     // 0x2c
    std::uint32_t field30;           // 0x30
    std::uint32_t field34;           // 0x34
    std::uint8_t flag38;             // 0x38
};

struct Object653DF0 {
    std::uint8_t pad_00[0xc8];
    int transferMode;                // 0x0c8
    float readyTimeSeconds;          // 0x0cc
    std::uint8_t pad_d0[0x30];
    std::uint8_t bufferRegion[0x24]; // 0x100
    int resetRequested;              // 0x124
    std::uint8_t pad_128[0x80];
    std::uint32_t owner;             // 0x1a4
};

extern "C" std::uint32_t __fastcall FUN_00653df0(StreamState* streamState, Object653DF0* self)
{
    if (self->readyTimeSeconds != DAT_00e2b05c) {
        const int tickCount = FUN_0065bf40();

        double tickCountAsDouble = static_cast<double>(tickCount);
        if (tickCount < 0) {
            tickCountAsDouble = tickCountAsDouble + _DAT_00e44708;
        }

        if (tickCountAsDouble * _DAT_00e448a8 < static_cast<double>(self->readyTimeSeconds)) {
            return 0;
        }
    }

    if (self->resetRequested != 0) {
        const int previousLength = streamState->length;

        streamState->length = 0;
        streamState->flag1c = 0;
        streamState->flag1d = 0;
        streamState->flag38 = 0;
        streamState->field34 = 0;
        streamState->alignedLength = previousLength + 7U & 0xfffffff8;
        streamState->field30 = 0;

        FUN_00653150(reinterpret_cast<int>(streamState));
        return 0;
    }

    if (self->transferMode == 0) {
        return FUN_00658230(
            static_cast<int>(self->owner + 0x5c),
            streamState->source,
            static_cast<std::uint32_t>(streamState->length + 7U) >> 3,
            0
        );
    }

    FUN_00654f70(
        self->owner,
        self->bufferRegion,
        reinterpret_cast<int>(streamState),
        self->transferMode
    );
    return 0;
}