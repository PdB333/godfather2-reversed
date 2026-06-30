// FUNC_NAME: AptValue::getTextValue
// Address: 0x0059c810
// Class: AptValue (from EA APT library, _AptValue.h line 646)
// Returns the text value pointer from a text-typed AptValue instance.
// Asserts that isTextInst() returns true; in debug builds triggers a breakpoint if not.

#include <cstdint>

// Forward declaration of assertion macro (typically __declspec(noinline) __fastcall)
extern void __debugbreak(); // swi(3) equivalent on x86 windows

// Assertion macro helper (simplified)
#define APT_ASSERT(expr, msg, file, line) \
    if (!(expr)) { \
        static bool suppress = false; \
        if (!suppress) { \
            suppress = true; \
            __debugbreak(); \
        } \
    }

class AptValue {
public:
    // ... other members ...
    // Returns true if this value is a text (string) instance.
    bool isTextInst() const; // defined at 0x0059c950

    // Getter for the text data pointer.
    // Offset 0x58: likely stores a pointer to the actual string data (char* or wchar_t*)
    void* getTextValue() const {
        // Validate that this value is indeed a text instance.
        if (!isTextInst()) {
            // Debug assertion: file _AptValue.h, line 0x286 (646)
            APT_ASSERT(false, "isTextInst()", "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h", 0x286);
        }
        // Return the text data pointer at offset 0x58 from this object.
        // In release builds, this may return without assertion.
        return *(void**)((uint8_t*)this + 0x58);
    }
};