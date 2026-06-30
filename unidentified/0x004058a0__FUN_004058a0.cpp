#include <cstdint>

std::int32_t __cdecl FUN_004025a0(std::uint32_t param_1);

extern std::uint8_t DAT_0120546e;

struct FUN_004058a0_StringRange
{
    std::uint8_t gap_00[0x4];
    std::uint32_t length; // [0x4]
};

struct FUN_004058a0_Source
{
    std::uint8_t gap_00[0xA];
    std::uint8_t flags; // [0xA]
    std::uint8_t gap_0B[0x1];
    std::int32_t index; // [0xC]
};

struct FUN_004058a0_Entry
{
    std::uint8_t gap_00[0x8];
    char* value;                  // [0x8]
    std::uint8_t gap_0C[0xC];
    FUN_004058a0_Source* source;  // [0x18]
};

struct FUN_004058a0_Context
{
    std::uint8_t gap_00[0x154];
    std::uint32_t ranges; // [0x154]
};

char* __thiscall FUN_004058a0(FUN_004058a0_Context* self, std::uint32_t param_1)
{
    const std::int32_t entryAddress = FUN_004025a0(param_1);
    char* result = nullptr;

    if (entryAddress != 0)
    {
        auto* const entry = reinterpret_cast<FUN_004058a0_Entry*>(entryAddress);

        result = entry->value;
        if (result == nullptr)
        {
            result = reinterpret_cast<char*>(&DAT_0120546e);
        }

        FUN_004058a0_Source* source = entry->source;
        if ((source != nullptr) && ((source->flags & 0x20) != 0))
        {
            const std::int32_t rangeAddress =
                source->index * 0x10 + static_cast<std::int32_t>(self->ranges);

            if (rangeAddress != 0)
            {
                char* stringEnd = result;
                do
                {
                    const char ch = *stringEnd;
                    ++stringEnd;
                    if (ch == '\0')
                    {
                        break;
                    }
                } while (true);

                const std::uint32_t length =
                    reinterpret_cast<FUN_004058a0_StringRange*>(rangeAddress)->length;

                if (length < static_cast<std::uint32_t>(
                                 static_cast<std::int32_t>(stringEnd - (result + 1))))
                {
                    result = result + length;
                }
            }
        }
    }

    return result;
}