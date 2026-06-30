// Xbox PDB: AptCIH::getSpriteInstBase
// FUNC_NAME: AptValue::getSpriteInstBaseData
// Function at 0x005a19c0 - Returns data from offset 0x58 if this is a sprite instance base, with debug assertion

// Assumed class layout (from _AptValue.h):
// class AptValue {
// public:
//    bool isSpriteInstBase(); // FUN_005a1a60
//    // +0x58 some data (likely a pointer or int)
//    ...
// };

#include <cstdlib>
#include <cstdio>

// Debug assertion globals (from known EA patterns)
extern bool gAssertEnabled; // DAT_01128f63
extern void* gAssertLogFunction; // virtual function table from thread-local storage

// Forward declaration of the check function
bool isSpriteInstBase(AptValue* thisPtr);

// Internal assertion function (simplified)
void __debugbreak_assert(const char* expr, const char* file, int line, int severity) {
    // placeholder for EA_DEBUG_BREAK or similar
    if (gAssertEnabled) {
        // call assertion handler via TLS
        void* tlsData = *(void**)(*(int*)__readfsdword(0x2c) + 0x30);
        if (tlsData) {
            void* logFunc = *(void**)(*(int*)tlsData + 8); // virtual function at +8
            // typical log function takes format string and args
            // but we skip details for brevity
        }
        __debugbreak(); // actual breakpoint
    }
}

// The actual function
uint32_t AptValue::getSpriteInstBaseData() {
    bool isSprite = this->isSpriteInstBase(); // FUN_005a1a60
    if (isSprite) {
        // Return the data at offset 0x58
        return *(uint32_t*)((char*)this + 0x58);
    }

    // Assertion block
    const char* expr = "isSpriteInstBase()";
    const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    int line = 0x281;
    int severity = 2; // assertion severity level
    bool assertEnabled = gAssertEnabled;

    if (!assertEnabled) {
        // If assertions disabled, just return the data anyway
        return *(uint32_t*)((char*)this + 0x58);
    }

    // Call debug assertion function
    void* tlsData = *(void**)(*(int*)__readfsdword(0x2c) + 0x30);
    uint32_t flags = 1;

    if (tlsData != nullptr) {
        // Virtual call to assertion log function
        void* logFunc = *(void**)(*(int*)tlsData + 8);
        // The call is: (*(logFunc))(&expr, "isSpriteInstBase()");
        // but the second argument seems redundant; possibly it's forwarded.
        reinterpret_cast<void(__cdecl*)(const char**, const char*)>(logFunc)(&expr, "isSpriteInstBase()");
    } else {
        // If no TLS data, flags might be modified differently
        if (flags & 2) {
            gAssertEnabled = false; // disable further assertions
        }
    }

    if ((tlsData != nullptr) || (severity != 4)) {
        if ((flags & 1) || (severity == 0) || (severity == 1)) {
            // Trigger debug break
            __debugbreak();
        }
    }

    // In debug builds, return the data even if assertion fails
    return *(uint32_t*)((char*)this + 0x58);
}