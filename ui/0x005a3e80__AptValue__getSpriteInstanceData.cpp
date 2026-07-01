// FUNC_NAME: AptValue::getSpriteInstanceData
// Function address: 0x005a3e80
// Returns a pointer from this+0x58, asserting that the object is a sprite instance.

#include <cstdint>

// Forward declaration of the assertion handler (from EA's debug system)
extern bool g_assertEnabled; // DAT_01128f6e
extern int __stdcall DebugAssertHandler(const char** msg, const char* expr); // from FUN_005a3fc0? Actually the check is separate

class AptValue {
public:
    // Returns true if this is a sprite instance
    bool isSpriteInstance(); // FUN_005a3fc0

    // Returns the sprite data pointer at offset 0x58
    void* getSpriteInstanceData() {
        // If not a sprite instance, trigger assertion
        if (!isSpriteInstance()) {
            const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
            const char* expr = "isSpriteInst()";
            int line = 0x27c; // 636
            int assertType = 2; // likely assertion type
            char* assertFlag = reinterpret_cast<char*>(&g_assertEnabled);

            if (*assertFlag != 0) {
                // Get thread-local storage for assertion handler
                // (simplified: actual code uses FS segment)
                void* tls = *(void**)(*(uintptr_t*)__readfsdword(0x2c) + 0x30);
                uint32_t result = 1;
                if (tls != nullptr) {
                    // Call assertion handler via vtable
                    result = (*(uint32_t(__stdcall**)(const char**, const char*))(*((uintptr_t*)tls) + 8))(&file, expr);
                }
                if ((result & 2) != 0) {
                    *assertFlag = 0; // disable further assertions
                }
                if ((tls != nullptr) || (assertType == 4)) {
                    // If assertion not handled, break
                    if ((result & 1) != 0 || (assertType == 0 || assertType == 1)) {
                        __debugbreak(); // swi 3
                    }
                }
            }
        }
        // Return value at this+0x58
        return *(void**)((uintptr_t)this + 0x58);
    }
};