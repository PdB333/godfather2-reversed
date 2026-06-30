// FUNC_NAME: AssetManager::findAssetByID
// Address: 0x004499e0
// Role: Looks up an asset using a 4-int hash/ID. Returns 1 if found and activates bit 0x100 at offset 0x50 (likely "in use" or "loaded" flag).
// Uses global string buffer DAT_0120e944 for temporary path/name formatting.

#include <cstdint>

// Forward declarations
int __cdecl hashLookup(int hash); // FUN_004059b0 - returns non-zero pointer if hash exists
void __cdecl formatStringBuffer(void* buffer, int arg); // FUN_00408a00 - initializes/clears string buffer
void* __cdecl getObjectFromID(int id); // FUN_004025a0 - returns object pointer from ID

struct AssetRecord {
    // offset 0x00: type/value fields
    // ...
    uint32_t flags; // +0x50
};

int __stdcall findAssetByID(int* idParts) {
    // idParts is array of 4 ints forming a hash (GUID?)
    int hash = ((idParts[0] * 0x21 + idParts[1]) * 0x21 + idParts[2]) * 0x21 + idParts[3];
    int assetPtr = hashLookup(hash);
    if (assetPtr == 0) {
        return 0;
    }

    // Setup local buffer for path/name resolution
    struct {
        char* buffer; // +0x00 - points to global DAT_0120e944
        uint8_t terminator; // +0x04 - set to 0
        int assetID; // +0x08 - the hash/ID
    } localBuffer;
    localBuffer.buffer = (char*)0x0120e944; // Global string buffer base
    localBuffer.terminator = 0;
    localBuffer.assetID = assetPtr;

    formatStringBuffer(&localBuffer, 0);

    void* object = getObjectFromID(assetPtr);
    if (object != nullptr) {
        // Set bit 0x100 on the asset's flags word at +0x50
        *(uint32_t*)((uintptr_t)object + 0x50) |= 0x100;
    }
    return 1;
}