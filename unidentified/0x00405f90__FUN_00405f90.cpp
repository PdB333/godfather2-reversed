#include <cstdint>

struct FUN_00405f90_Object
{
    std::int32_t values[16];  // [0x00] .. [0x3F]
    std::int32_t count;       // [0x40]
    std::int32_t extraValue;  // [0x44]
};

std::int32_t __fastcall FUN_00405f90(const FUN_00405f90_Object* lhs, const FUN_00405f90_Object* rhs)
{
    const std::uint32_t count = static_cast<std::uint32_t>(lhs->count);

    if (count != static_cast<std::uint32_t>(rhs->count)) {
        return 1;
    }

    std::uint32_t index = 0;
    if (count != 0) {
        const std::int32_t* lhsValue = &lhs->values[1];

        do {
            if (*lhsValue != rhs->values[static_cast<std::size_t>(lhsValue - &lhs->values[0])]) {
                return 1;
            }

            index = index + 1;
            lhsValue = lhsValue + 1;
        } while (index < count);
    }

    return 0;
}