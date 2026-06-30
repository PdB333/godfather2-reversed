#include <cstdint>

extern "C" std::int32_t FUN_00405720(std::int32_t value, std::int32_t index);

struct FUN_00405720_Object
{
    std::byte pad00[0x0A];
    std::uint8_t flags; // [0x0A]
};

std::uint8_t FUN_004061f0(std::int32_t param_1)
{
    const auto object =
        reinterpret_cast<FUN_00405720_Object*>(FUN_00405720(param_1, 0));
    if (object == nullptr) {
        return 1;
    }

    const std::uint8_t flags = object->flags;
    if ((flags & 0x08u) != 0) {
        return 1;
    }
    if ((flags & 0x10u) != 0) {
        return 0;
    }
    return static_cast<std::uint8_t>(~(flags >> 2) & 1);
}