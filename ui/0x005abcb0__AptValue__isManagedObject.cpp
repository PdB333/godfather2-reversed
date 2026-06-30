// FUNC_NAME: AptValue::isManagedObject
#include <cstdint>

// Function at 0x005abcb0
// Check if an AptValue is of a specific managed type (type 0x17 with managed flag bit15 set)
// Source: c:\packages001_pc\apt\0.19.optimized\source\apt\_AptValue.h line 456
__thiscall bool AptValue::isManagedObject() {
    // Assert: this pointer must not be null
    if (this == nullptr) {
        // Debug assertion with source location
        // This block would trigger a debugger break if enabled (DAT_01128fd3)
        static const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
        static const int line = 0x1c8; // 456
        // Thread-local assert handler (FS segment)
        // (Simplified: assume assertion triggers break if DAT_01128fd3 is set)
        // ... assertion handling omitted for clarity
        return false;
    }

    // Value structure: first dword contains type (low 15 bits) and managed flag (bit15)
    // Check if type == 0x17 (23) and managed flag is set
    uint32_t value = *(uint32_t*)this;
    return ((value & 0x7FFF) == 0x17) && ((value & 0x8000) != 0);
}