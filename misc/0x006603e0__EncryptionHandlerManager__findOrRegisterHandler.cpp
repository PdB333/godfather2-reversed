// FUNC_NAME: EncryptionHandlerManager::findOrRegisterHandler
#include <cstddef>

// Handler entry structure (0x2c bytes each)
struct EncryptionHandler {
    int    occupied;     // +0x00: non-zero if slot is used
    char   type;        // +0x04: handler type identifier (0x06 for Rijndael)
    // padding to align next field
    const char* name;   // +0x08: human-readable name (e.g. "rijndael")
    double value1;      // +0x10: some encryption constant or key schedule
    double value2;      // +0x18: another constant
    void (*func1)();    // +0x20: encryption function pointer
    void (*func2)();    // +0x28: decryption function pointer
};

// Global table of encryption handlers (size unknown, but at least up to 0x1206008)
static EncryptionHandler g_encryptionHandlers[1024]; // approximate max count

// Global data references from .rdata
extern const char* PTR_s_rijndael;    // _PTR_s_rijndael_00e27a84
extern double       DAT_00e27a8c;     // first encryption constant
extern double       DAT_00e27a94;     // second encryption constant
extern void (*     PTR_FUN_00e27a9c)(); // encryption routine pointer
extern void (*     PTR_FUN_00e27aa4)(); // decryption routine pointer
extern void (*     PTR_FUN_00e27aac)(); // extra function pointer

int findOrRegisterEncryptionHandler()
{
    int index = 0;
    // First pass: search for an already registered handler of type 0x06 (Rijndael)
    EncryptionHandler* entry = &g_encryptionHandlers[1]; // start at offset 1? Actually base+4
    while (true)
    {
        EncryptionHandler* prev = entry - 1;  // point to occupied field (offset 0)
        if (prev->occupied != 0 && entry->type == 0x06) {
            return index;  // found existing handler
        }
        entry++;
        index++;
        if (entry >= &g_encryptionHandlers[0x100000]) // arbitrary large bound
            break;
    }

    // Second pass: find an empty slot
    index = 0;
    EncryptionHandler* slot = g_encryptionHandlers;
    while (slot < &g_encryptionHandlers[0x100000]) // limit
    {
        if (slot->occupied == 0)
        {
            // Fill the slot with the Rijndael handler data
            slot->occupied = 1;          // mark as used
            slot->type    = 0x06;       // type ID
            slot->name    = PTR_s_rijndael; // +0x08: name string
            slot->value1  = DAT_00e27a8c;   // +0x10: key schedule?
            slot->value2  = DAT_00e27a94;   // +0x18: another constant
            slot->func1   = PTR_FUN_00e27a9c; // +0x20: encryption
            slot->func2   = PTR_FUN_00e27aa4; // +0x28: decryption
            // The last pointer (at +0x2c?) is stored separately
            *(void**)((char*)slot + 0x2c) = PTR_FUN_00e27aac;
            return index;
        }
        slot++;
        index++;
    }
    return -1; // no free slot
}