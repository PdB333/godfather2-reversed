// FUNC_NAME: isObjectOfType
// Function at 0x0071fa50 checks if an object (identified by a handle/pointer structure) is of a specific type (hash 0x637b907).
// The handle structure: +0x0: something (unused), +0x4: pointer to an object (or null).
// To get the type info, it subtracts 0x48 from that pointer to reach a base class, then reads word at +0x2134 as a type pointer.
// If that pointer is non-null, it calls hash function (FUN_006b0f50) and compares to the expected CRC.
// Returns 1 (true) if match, else 0.

bool __fastcall isObjectOfType(int handlePtr)
{
    int objectPtr;
    int basePtr;

    if (*(int *)(handlePtr + 4) == 0) {
        objectPtr = 0;
    }
    else {
        objectPtr = *(int *)(handlePtr + 4) - 0x48;  // adjust to base class offset
    }

    if (*(int *)(objectPtr + 0x2134) != 0) {  // type info pointer at large offset
        int typeHash = FUN_006b0f50(*(int *)(objectPtr + 0x2134));
        if (typeHash == 0x637b907) {
            return true;
        }
    }
    return false;
}