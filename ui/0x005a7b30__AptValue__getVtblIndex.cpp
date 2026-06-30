// FUNC_NAME: AptValue::getVtblIndex
// Address: 0x005a7b30
// Role: Returns the virtual table index of an AptValue object, with debug assertions.
// The return value packs a boolean (index == 3) in the low byte and the high byte of the index in bits 8-14.

uint AptValue::getVtblIndex() {
    // Debug assertion: this must not be null
    if (this == nullptr) {
        // Assertion failure: "this"
        // File: c:\packages001_pc\apt\0.19.optimized\source\apt\_AptValue.h, line 0x16f (367)
        // Trigger debug break if assertion handler is active
        if (PTR_DAT_01128fb0._3_1_ != '\0') {
            // Call assertion handler via thread-local storage
            int* fsBase = *(int**)(__readfsdword(0x2C));
            int* handler = *(int**)(*fsBase + 0x30);
            if (handler != nullptr) {
                uint result = (**(code**)(*handler + 8))(&local_14, &DAT_00e3b9b8);
                if (local_4 != nullptr) {
                    if ((result & 2) != 0) {
                        *local_4 = 0;
                    }
                }
            } else {
                if ((local_8 != 4) && ((result & 1) != 0 || (local_8 == 0 || local_8 == 1))) {
                    __debugbreak();
                }
            }
        }
    }

    uint vtblIndex = *this & 0x7FFF; // Low 15 bits store the virtual table index

    // Debug assertion: vtblIndex must be less than AptVFT_NumVFTs (0x24 = 36)
    if (vtblIndex >= 0x24) {
        // Assertion failure: "getVtblIndex() < AptVFT_NumVFTs"
        // File: same, line 0x170 (368)
        if (DAT_01128fb4 == '\0') {
            goto LAB_005a7c4c;
        }
        int* fsBase = *(int**)(__readfsdword(0x2C));
        int* handler = *(int**)(*fsBase + 0x30);
        if (handler != nullptr) {
            uint result = (**(code**)(*handler + 8))(&local_14, "getVtblIndex() < AptVFT_NumVFTs");
            if (local_4 != nullptr) {
                if ((result & 2) != 0) {
                    *local_4 = 0;
                }
            }
        } else {
            if ((local_8 != 4) && ((result & 1) != 0 || (local_8 == 0 || local_8 == 1))) {
                __debugbreak();
            }
        }
    }

LAB_005a7c4c:
    // Return packed value: low byte = (vtblIndex == 3), high 3 bytes = (vtblIndex >> 8)
    return ((vtblIndex >> 8) << 8) | (vtblIndex == 3);
}