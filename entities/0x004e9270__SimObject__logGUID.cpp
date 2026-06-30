// FUNC_NAME: SimObject::logGUID
uint32_t SimObject::logGUID(void)
{
    // Check if the 128-bit GUID (four ints at this+0x00) is non-zero
    if ( ((int*)this)[0] == 0 && ((int*)this)[1] == 0 && ((int*)this)[2] == 0 && ((int*)this)[3] == 0 )
    {
        return 0;
    }

    char guidString[28]; // Enough for GUID string representation
    // Convert GUID to string (likely "XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX")
    intToGuidString((int*)this, guidString); // FUN_004eaec0

    // Calculate length of the resulting string (excluding null terminator)
    char* endPtr = guidString;
    while (*endPtr != '\0') { endPtr++; }
    int length = (int)endPtr - (int)(guidString + 1); // length without null

    // Log the GUID string (0 = log level, likely Info)
    debugPrint(0, guidString, length); // FUN_00ab8560

    // Return some global flag/state
    return getLoggingEnabled(); // FUN_00616720
}