// Xbox PDB: AptCIH::getCharacterInst
// FUNC_NAME: AptValue::isCharacterInst
#include <cstdint>

// AptValue class from Scaleform (Flash UI framework), used in EA's EARS engine.
// This method checks if the underlying value is a character instance (string) and returns it.
// The 'this' pointer is expected to be in EAX (__thiscall convention).
uint32_t AptValue::isCharacterInst(void)
{
    // Try to get or initialize the character value
    if (func_005a4080() != 0) // likely a get-or-create helper
    {
        // Initialization succeeded or value is already a character
        // returns m_data +0x58 (the character string pointer) from this
        return *(uint32_t*)((uint8_t*)this + 0x58);
    }

    // Debug assertion block - checks if we're in a valid state
    const char* expressionStr = "isCharacterInst()";
    const char* fileStr = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
    uint32_t lineNum = 0x2aa;    // line 682
    int32_t assertType = 2;       // likely ASSERT or warning level
    uint8_t* assertFlag = &DAT_01128f6f;  // global debug flag, 0 = ignore assertions

    if (*assertFlag != 0)
    {
        // Assertion active - get the current exception/error handler
        int* handler = *(int**)(*(int**)(__readfsdword(0x2c)) + 0x30); // Get SEH handler
        uint32_t resultCode = 1;

        if (handler != nullptr)
        {
            // Call the handler's format/display function (vtable index 2)
            resultCode = ((int (__stdcall*)(const char**, const char*))(*(void***)handler)[2])(
                &expressionStr, "isCharacterInst()");
        }

        if (assertFlag != nullptr && (resultCode & 2) != 0)
        {
            *assertFlag = 0;  // Disable further assertions
        }

        // Decide whether to break/abort
        if (handler != nullptr || assertType == 4) // always break on fatal?
        {
            if ((resultCode & 1) != 0 || (assertType == 0 || assertType == 1))
            {
                // Trigger debug breakpoint
                __debugbreak();  // equivalent to swi(3) on ARM, int3 on x86
                return 0;        // fallback return
            }
        }
    }

    // Normal path: return the character pointer from this+0x58
    return *(uint32_t*)((uint8_t*)this + 0x58);
}