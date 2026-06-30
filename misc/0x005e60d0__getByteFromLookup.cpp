// FUNC_NAME: getByteFromLookup
// Address: 0x005e60d0
// Role: Retrieves a byte at offset 0x22 from an object found via a lookup function.
//       Used to obtain a flag or status from a game data structure.

char __fastcall getByteFromLookup(void* unusedParam, void* key)
{
    char localByte;        // byte at offset 0x22
    char localBuffer[4];   // buffer for lookup output (size unknown)
    
    void* result = FUN_005f0560(key, &localByte, localBuffer);  // perform lookup, expecting pointer in eax
    if (result != 0) {
        return *(char*)((int)result + 0x22);  // return field at +0x22
    }
    return 0;
}