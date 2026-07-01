// FUNC_NAME: ObjectWithMagic::checkAndHandleCorruption
int __fastcall ObjectWithMagic::checkAndHandleCorruption(int* thisPtr)
{
    int result;
    int virtualReturn;
    int someHandle;
    int expectedMagic[4];

    // Check if integrity flag is not set (0 = unverified)
    // and if any of the four magic fields are non-zero,
    // but not all equal to the expected sentinel values.
    if ((thisPtr[0x68] == 0) &&
        ((((thisPtr[0x64] != 0) || (thisPtr[0x65] != 0) || (thisPtr[0x66] != 0) || (thisPtr[0x67] != 0)))) &&
        (((thisPtr[0x64] != 0xBABDBABA) || (thisPtr[0x65] != 0xBEEFBEEF) ||
          (thisPtr[0x66] != 0xEAC15A55) || (thisPtr[0x67] != 0x91100911))))
    {
        // Setup expected magic numbers (debug canaries)
        expectedMagic[0] = 0xBADBADBA;   // -0x45245246
        expectedMagic[1] = 0xBEEFBEEF;   // -0x41104111
        expectedMagic[2] = 0xEAC15A55;   // -0x153EA5AB
        expectedMagic[3] = 0x91100911;   // -0x6EEFF6EF

        // Call virtual function at vtable offset 0x10 (4th method)
        // with pointer to expectedMagic array and a zero argument.
        virtualReturn = (*(int (__thiscall**)(int*, int))(*(int*)thisPtr + 0x10))(&expectedMagic, 0);

        if (virtualReturn != 0) {
            // Handle corruption: look up by resource ID and call error handler
            someHandle = FUN_00724dc0(virtualReturn, 0x8A859764);
            FUN_008e7710(someHandle);
        }
    }

    return thisPtr[0x68]; // Return integrity flag
}