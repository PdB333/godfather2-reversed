// FUNC_NAME: AptValue::isType6

bool AptValue::isType6() const
{
    // If this is null, trigger an assertion in debug builds.
    // In release builds (DAT_01128fb7 == 0), the assertion is skipped,
    // but the null pointer would then be dereferenced below.
    if (this == nullptr)
    {
        const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
        int line = 0x195; // 405
        int expressionId = 2; // likely expression "this != 0"
        const char* expressionStr = "this != 0"; // based on DAT_01128fb7 reference

        if (DAT_01128fb7 != '\0') // debug build flag
        {
            // Standard EA assert: fetch assertion handler from thread-local storage
            // and call it with the debug info, then issue a breakpoint (swi(3)).
            // For reconstruction, we assume __debugbreak is available.
            __debugbreak();
        }
        // If assertion flag is zero (release) and pointer is null,
        // we fall through to the type check which will crash the game.
    }

    // Check the type field stored in the first 4 bytes of the object.
    // The type code occupies bits 0-14, bit 15 is a flag (must be 0 for this type).
    // Type value 6 is being checked (e.g., array type in the APT value system).
    uint32_t typeFlags = *reinterpret_cast<const uint32_t*>(this);
    if ((typeFlags & 0x7FFF) == 6 && ((~(typeFlags >> 0xF) & 1) == 0))
    {
        return true;
    }
    return false;
}