// FUNC_NAME: AptValue::checkType
// Address: 0x005a8030
// Role: Debug type-check assertion function. Returns whether the AptValue's type matches a specific pattern (type code 0x15 with highest bit set). If assertion enabled and type doesn't match, triggers an assert with source file/line info.

#include <cstdint>

// Forward declaration of global assert enable flag (address 0x01128fba)
extern bool g_assertEnabled;

// Definition of a dummy class for context (actual members unknown)
class AptValue {
public:
    uint32_t typeFlags; // +0x00: type code (lower 15 bits) + flag bits (bit15 for string, etc.)
    // ... other members

    // Check if this value's type matches the expected type (0x15 with bit15=1)
    bool checkType();
};

// Helper to report assertion (simplified; actual implementation uses thread-local storage)
void reportAssert(const char* file, int line, const char* expr);

bool AptValue::checkType() {
    // Early exit if this is null (unusual, but present in decompiled code)
    if (this == nullptr) {
        goto typeCheck;
    }

    // Setup assertion context (file, line, expression)
    const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    int line = 0x1b4; // 436
    const char* expr = "EnsureValidType"; // placeholder (DAT_01128fba)
    bool assertionEnabled = g_assertEnabled;

    // If assertion is globally disabled, skip the failure handling
    if (assertionEnabled) {
        // Access some thread-local debug context (simplified)
        // In original: *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30)
        // This is likely a pointer to a debug/reporting object.
        void* debugContext = /* TLS dereference */ nullptr;
        if (debugContext) {
            // Call a method to output the assertion (vtable call)
            // (**(code **)(*context + 8))(&file, &globalMessage)
            // For reconstruction, just call reportAssert.
            reportAssert(file, line, expr);
        }

        // Potentially trigger a debug breakpoint (software interrupt 3)
        if (/* condition based on flags */) {
            __asm { int 3 } // Trigger breakpoint for debugger
        }
    }

typeCheck:
    // Check the actual type of this AptValue
    // Original: ((*unaff_EDI & 0x7fff) == 0x15) && ((~(byte)(*unaff_EDI >> 0xf) & 1) == 0)
    // This means: type code == 0x15 AND bit15 == 1
    uint32_t typeField = this->typeFlags;
    uint32_t typeCode = typeField & 0x7FFF;
    uint32_t flagBit = (typeField >> 15) & 1;
    if (typeCode == 0x15 && flagBit == 1) {
        return true;
    }
    return false;
}