// FUNC_NAME: ConfigDatabase::getInt
// Address: 0x005e6af0
// Role: Retrieves an integer value from the global config database by key (struct with byte + int).
// The key is passed via stack (byte + int) and a pointer to the key struct is given to an internal lookup.
// If found, returns the integer stored at the returned pointer; else 0.

#include <cstdint>

// Forward declarations of internal helpers (from other translation units)
int32_t* __cdecl getConfigValuePtr(void* configDB, void* key);   // FUN_005f0600
int32_t  __cdecl extractConfigInt(void* configDB, int32_t value); // FUN_005f0680

// Global config database pointer (DAT_01223514)
extern void* gConfigDB;

// Config key structure: 1-byte type + 4-byte id/hash
struct ConfigKey {
    uint8_t type;   // +0x00
    int32_t id;     // +0x04
};

int32_t __cdecl getConfigInt(void)
{
    void* configDB = gConfigDB;
    ConfigKey key;
    key.type = 0;
    key.id   = 0;

    int32_t* valuePtr = getConfigValuePtr(configDB, &key);
    if (valuePtr != nullptr) {
        return extractConfigInt(configDB, *valuePtr);
    }
    return 0;
}