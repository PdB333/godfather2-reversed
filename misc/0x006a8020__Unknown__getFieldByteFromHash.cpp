// FUNC_NAME: Unknown::getFieldByteFromHash
// Function address: 0x006a8020
// Retrieves a byte field from an object using a hash identifier.
char __fastcall getFieldByteFromHash(void* obj, void* param_1)
{
    // obj is the 'this' pointer (in EAX), param_1 is additional data (in EDX)
    if (obj != 0 && param_1 != 0) {
        int outSize = 0;          // local_8
        char* outData = 0;        // local_4 — likely set by the hash lookup, though decompilation shows it unassigned
        char result = FUN_005fd340(
            *(unsigned short*)((int)obj + 0x12),  // offset +0x12: some identifier/hash
            0xe311f9aa,                           // target field hash
            &outSize                              // output size/value
        );
        // If lookup succeeded, outData points to field data, outSize is nonzero,
        // and the type byte at offset +6 equals 2 (e.g., a field type identifier)
        if (result != 0 && outData != 0 && outSize != 0 && *(char*)(outSize + 6) == 0x02) {
            return *outData;   // return the first byte of the field
        }
    }
    return 0;
}