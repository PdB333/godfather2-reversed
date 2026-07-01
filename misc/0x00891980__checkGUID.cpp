// FUNC_NAME: checkGUID
int __fastcall checkGUID(int thisPtr)
{
    int* guidPtr = (int*)(thisPtr + 0x178); // GUID field at this+0x178 (128-bit)

    // Sentinel value for "null" GUID: 0xBADBADBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911
    // If the GUID matches this sentinel or all zeros, return 0 (invalid).
    if ((guidPtr[0] == 0xBADBADBA && guidPtr[1] == 0xBEEFBEEF &&
         guidPtr[2] == 0xEAC15A55 && guidPtr[3] == 0x91100911) ||
        (guidPtr[0] == 0 && guidPtr[1] == 0 && guidPtr[2] == 0 && guidPtr[3] == 0))
    {
        return 0;
    }

    // Otherwise, decode or interpret the GUID and return the result.
    int result = FUN_00446100(guidPtr, 0);
    return result;
}