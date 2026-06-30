// FUNC_NAME: DataManager::GetByteFromHashLookup
// Address: 0x006a8020
// Role: Retrieves a single byte from a data lookup based on an object's ID and a hash constant.
// Uses a hash lookup function (FUN_005fd340) to find a data block, checks type marker at offset +6, returns first byte if type == 2.

struct HashLookupResult {
    char* dataPtr;   // +0x00 pointer to data
    char* extraPtr;  // +0x04 pointer to additional info (used for type check)
};

char __fastcall GetByteFromHashLookup(int pObject, int pContext) {
    if (pObject != 0 && pContext != 0) {
        HashLookupResult result;
        result.dataPtr = 0;
        result.extraPtr = 0;

        // Lookup data using object's 16-bit ID at offset 0x12 and a hash constant (0xe311f9aa)
        char found = HashLookupFunc(
            *(unsigned short*)(pObject + 0x12),  // object ID
            0xe311f9aa,                           // hash for the property (likely "model" or "anim")
            &result                               // output structure
        );

        if (found && result.dataPtr && result.extraPtr && *(char*)(result.extraPtr + 6) == 2) {
            return *result.dataPtr;
        }
    }
    return 0;
}