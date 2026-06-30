// FUNC_NAME: AptValue::isObject

// Function at 0x005a4140
// Checks if an AptValue's internal type is 0x8013 (object type?).
// Includes a debug assertion that the value pointer is not null.
// Returns true if the type matches, false otherwise.
// Called from many places to verify value types.

bool AptValue::isObject() const
{
    // Get the 'this' pointer (in EDI by convention for this function)
    const uint32_t* valuePtr = /* this */ reinterpret_cast<uint32_t*>(this);

    if (valuePtr == nullptr)
    {
        // Debug assertion: file, line, condition
        const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
        int line = 0x2de; // 734
        int condition = 2; // maybe assertion severity or condition index
        const char* conditionStr = &DAT_01128f72; // points to a static assertion condition string

        // Check if assertion reporting is enabled (DAT_01128f72 is a flag byte)
        if (DAT_01128f72 != '\0')
        {
            // Get the current exception handler (FS:0x2c offset, Windows structured exception)
            int* pExceptionHandler = *(int**)(*(int*)(__readfsdword(0x2c) + 0x30));
            uint32_t result = 1;
            if (pExceptionHandler != nullptr)
            {
                // Call assertion handler (function pointer at offset 8 from handler)
                result = (*(code**)(*pExceptionHandler + 8))(&file, &DAT_00e3b9b8);
                if (conditionStr != nullptr)
                {
                    // Clear the assertion flag if condition met?
                    *conditionStr = '\0';
                }
            }
            else
            {
                if ((result & 2) != 0)
                {
                    *conditionStr = '\0';
                }
            }

            // If assertion should break (condition = 4? or no handler), trigger breakpoint
            if ((pExceptionHandler == nullptr) || (condition == 4) ||
                ((result & 1) != 0) || (condition == 0) || (condition == 1))
            {
                // Trigger debug break (interrupt 3)
                __debugbreak();
            }
        }
    }

    // Type check: extract lower 15 bits and bit 15
    // The type field is a 32-bit value where bit 15 is a flag and lower 15 bits are type ID
    uint32_t typeField = *valuePtr;
    // Check if the type ID is 0x13 (19) and the flag (bit 15) is set
    if ((typeField & 0x7fff) == 0x13 && ((~(byte)(typeField >> 0xf) & 1) == 0))
    {
        return true;
    }
    return false;
}