// FUNC_NAME: AptValue::initWithDebugCheck
// Address: 0x005abf00
// Role: Debug constructor/initializer that asserts pValue validity and sets a debug signature.

#include <cstdint>

void __thiscall AptValue::initWithDebugCheck(int thisPtr) {
    // Debug assertion block (from _AptValue.h line 0x33f)
    if (g_assertEnabled != 0) {                    // unaff_EDI
        const char* expr = "pValue";
        const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
        int line = 0x33f;
        int assertType = 2;
        static char assertOnceFlag = 0;            // DAT_01128fd5

        if (assertOnceFlag == '\0') {
            // Access TLS assertion handler
            int* tlsPtr = *(int**)(*(int*)(__readfsdword(0x2c) + 0x30));
            uint32_t result = 1;
            if (tlsPtr != nullptr) {
                result = (*(uint32_t(__thiscall**)(const char**, const char*))(*tlsPtr + 8))(&expr, "pValue");
            }
            if ((result & 2) != 0) {
                assertOnceFlag = 1;
            }
            if ((tlsPtr != nullptr) || (assertType != 4)) {
                if ((result & 1) != 0 || (assertType == 0) || (assertType == 1)) {
                    __debugbreak(); // software interrupt (swi 3)
                }
            }
        }
    }

    // Initialize base class at offset 4
    baseClassInit(thisPtr + 4);   // FUN_005a92b0

    // Set debug signature to detect uninitialized memory
    *(uint32_t*)(thisPtr + 0x20) = 0xbeefceec;   // +0x20: debugMagic
}