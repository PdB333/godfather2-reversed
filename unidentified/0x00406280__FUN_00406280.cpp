#include <cstddef>
#include <cstdint>

extern "C" std::int32_t FUN_00405770(std::int32_t param_1, std::int32_t param_2);

struct FUN_00405770_Object
{
    std::byte pad00[0x0A];
    std::uint8_t flags; // [0x0A]
};

bool FUN_00406280(std::int32_t param_1, std::int32_t param_2, char param_3)
{
    auto* const object =
        reinterpret_cast<FUN_00405770_Object*>(FUN_00405770(param_1, param_2));

    if (object != nullptr) {
        if (param_3 != '\0') {
            object->flags = static_cast<std::uint8_t>(object->flags & 0xf7u);
            return object != nullptr;
        }

        object->flags = static_cast<std::uint8_t>(object->flags & 0xefu);
    }

    return object != nullptr;
}