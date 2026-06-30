// FUNC_NAME: debugVPrintf

int debugVPrintf(int category)
{
    int result = 0;
    int outputLength = 0;
    void* buffer = (void*)getTempBuffer(); // FUN_00456010 - returns a temporary buffer pointer or size? Actually it returns a buffer pointer
    if (buffer != 0) {
        // Initialize variable argument list structure (local_70)
        char* formatString; // local_80, will point to either buffer or default string
        int argCount;       // local_7c
        int argSize;        // local_78
        void (*freeFunc)(void*); // local_74, function pointer to free buffer

        // Set up format string and arguments (mimicking va_list)
        // The local variables between 0x64 and 0x2c might be a pre-allocated va_list area
        local_64 = 0;
        local_60 = 0;
        local_54 = 0;
        local_50 = 0;
        local_44 = g_globalA1A4;   // DAT_00e2b1a4
        local_68 = 1;
        local_58 = 1;
        local_40 = g_globalB04C;   // DAT_00e2b04c
        local_5c = 0;
        local_4c = 0;
        local_34 = 0;
        local_48 = 0;
        local_47 = 0;
        local_3c = g_globalB050;   // DAT_00e2b050
        local_38 = 0;
        local_30 = 0;
        local_2c = 0;

        clearArgStructure(); // FUN_005e3130 - first call

        // Allocate temporary buffer for formatted output
        formatString = 0;
        argCount = 0;
        argSize = 0;
        freeFunc = 0;
        clearArgStructure(); // FUN_005e3130 - second call

        allocateFormatBuffer(&formatString, buffer, 0); // FUN_004a8460 - allocates buffer of size from buffer? third param 0 means no extra flags
        initVaList(local_70, buffer); // FUN_004a84d0 - initializes the va_list array from the buffer's internal data

        local_1c = *(int*)((char*)buffer + 0x30); // probably read a stored argument count or size
        local_70[0] = (void*)&s_DebugPrefix; // DAT_00438ba0 - a format string like "[DBG] "
        local_28 = category; // store the category for later? not used further

        if (g_ediFlag != 0) { // unaff_EDI - probably a global flag indicating something
            local_38 = getSomeValue(); // FUN_004dafd0
        }

        // Determine the format string to use
        if (formatString != 0) {
            formatString = (char*)formatString;
        } else {
            formatString = (char*)&s_DefaultString; // DAT_0120546e - likely "(null)"
        }

        // Check if logging is enabled in the global logger object
        if (*(char*)((char*)g_Logger + 0x1744) != '\0') { // DAT_0122350c is the logger object
            result = outputFormattedString(g_Logger, &outputLength, formatString, (va_list)local_70, 0xFFFFFFFF); // FUN_005e25f0 - returns the number of bytes written?
        }

        // Free the allocated buffer if it was used
        if (formatString != 0) {
            freeFunc(formatString); // free the buffer
        }
    }
    return result;
}