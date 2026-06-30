// FUNC_NAME: AptValue::isTypeWithTag0x800F
#include <cstdint>

// Represents a value in EA's APT UI library
class AptValue {
public:
    // Returns true if the value's type tag matches 0x800F (bit15 set, lower 15 bits == 0xF)
    bool __thiscall isTypeWithTag0x800F(void);

private:
    // Internal assertion flag (from DAT_01128f15)
    static bool s_assertEnabled;
};

bool __thiscall AptValue::isTypeWithTag0x800F(void) {
    // Guard against null this pointer
    if (this == nullptr) {
        // EA assertion macro expanded; source: c:\packages001_pc\apt\0.19.optimized\source\apt\_AptValue.h line 710
        const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
        int line = 710;
        int assertionType = 2;  // ASSERT_ALWAYS
        if (!s_assertEnabled) {
            // If assertion flag is disabled, skip break
        } else {
            // In debug builds, invoke debugger break
            if (s_assertEnabled) {
                __debugbreak();  // corresponds to swi(3)
            }
        }
        // If assertion didn't break, fall through to check
    }

    uint32_t header = *reinterpret_cast<uint32_t*>(this);
    // Check: lower 15 bits == 0xF and bit 15 is set
    if ((header & 0x7FFF) == 0xF && ((~(uint8_t)(header >> 15) & 1) == 0)) {
        return true;
    }
    return false;
}