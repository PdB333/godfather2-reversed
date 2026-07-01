// Xbox PDB: EARS::Modules::StreamScripterManager::StreamScripterManager
// FUNC_NAME: MsgStreamManager::MsgStreamManager
#include <windows.h> // For DWORD, etc.

// Static globals for the singleton instance and hashed stream IDs
static MsgStreamManager* g_pMsgStreamManager = nullptr;       // DAT_01223440
static uint32_t g_msgStreamVisibleId = 0;                      // DAT_0120e944
static uint32_t g_msgStreamHiddenId = 0;                       // DAT_0120e94c

// External helper: hashes a string (likely returning a 32-bit hash from EARS string table)
uint32_t __fastcall hashString(const char* str);               // FUN_004dafd0

// External helper: stores a 32-bit value at a given address (assignment wrapper)
void __fastcall storeUint32(uint32_t* dest, uint32_t value);   // FUN_00408260

class MsgStreamManager {
public:
    // Vtable pointer placed at offset +0x00
    void** vtable;

    // Constructor: initializes vtable, stores singleton, registers stream IDs
    MsgStreamManager() {
        // Set vtable to class-specific virtual function table (+0x00)
        this->vtable = (void**)0x00e31220;        // PTR_FUN_00e31220

        // Store this instance as the global singleton
        g_pMsgStreamManager = this;               // DAT_01223440 = param_1

        // Look up and store the hash for "iMsgStreamVisible"
        uint32_t visibleHash = hashString("iMsgStreamVisible");
        storeUint32(&g_msgStreamVisibleId, visibleHash);   // DAT_0120e944

        // Look up and store the hash for "iMsgStreamHidden"
        uint32_t hiddenHash = hashString("iMsgStreamHidden");
        storeUint32(&g_msgStreamHiddenId, hiddenHash);     // DAT_0120e94c
    }
};