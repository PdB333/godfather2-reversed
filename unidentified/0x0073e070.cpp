// FUN_NAME: getStateBasedConstant
#include <cstdint>

uint32_t getStateBasedConstant() {
    int32_t state = FUN_00806440(); // Returns a state index (0, 1, or other)
    // Returns a magic constant depending on the state
    if (state == 0 || state == 1) {
        return 0xabdb8e78;
    } else {
        return 0x82da383e;
    }
}