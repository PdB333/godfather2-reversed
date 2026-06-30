#include <cstdint>

extern "C" std::int32_t FUN_004025a0(std::int32_t value);
extern "C" void FUN_00402ba0();
extern "C" void FUN_00402b00();
extern "C" void FUN_004042e0(std::int32_t object, float value);

extern "C" float DAT_00e2eff4;

struct FUN_004025a0_Object
{
    std::byte pad00[0x48];
    float field48;  // [0x48]
    float field4C;  // [0x4C]
};

void FUN_00406130(std::int32_t param_1, std::int32_t param_2, float param_3)
{
    const auto* const object1 =
        reinterpret_cast<const FUN_004025a0_Object*>(FUN_004025a0(param_1));
    if (object1 != nullptr) {
        auto* const object2 =
            reinterpret_cast<FUN_004025a0_Object*>(FUN_004025a0(param_2));
        if (object2 != nullptr) {
            FUN_00402ba0();
            FUN_00402b00();

            const bool changed = param_3 != DAT_00e2eff4;
            object2->field4C = param_3;

            if (changed) {
                FUN_004042e0(param_2, object1->field48 * param_3);
            }
        }
    }
}