// FUNC_NAME: checkEAMagicSignature
#include <cstdint>

// Check if a memory block contains the EA game magic signature (4 DWORDs)
// Returns 0 if matched, 1 otherwise.
// The magic values appear to be: 0xBABDBABA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911
int32_t __fastcall checkEAMagicSignature(int32_t* signaturePtr)
{
    // Validate first DWORD: 0xBABDBABA
    if (*signaturePtr != 0xBABDBABA)
        return 1;

    // Validate second DWORD: 0xBEEFBEEF
    if (signaturePtr[1] != 0xBEEFBEEF)
        return 1;

    // Validate third DWORD: 0xEAC15A55
    if (signaturePtr[2] != 0xEAC15A55)
        return 1;

    // Validate fourth DWORD: 0x91100911
    if (signaturePtr[3] != 0x91100911)
        return 1;

    return 0; // All four match
}