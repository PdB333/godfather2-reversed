// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

#include <cstring> // for memcpy

// External globals
extern void* const PTR_FUN_00d5da74;   // base vtable pointer
extern void* const PTR_FUN_00e2f19c;   // placeholder vtable/function pointer
extern void* const PTR_LAB_00d5da64;   // second overwrite target
extern void* g_pInitData;              // DAT_012069c4 - initialization data block

// Global singleton pointer (DAT_01129900)
class GodfatherGameManager;
GodfatherGameManager* g_pGodfatherGameManager = nullptr;

class GodfatherGameManager {
public:
    // +0x00: vtable pointer
    void* vtable;

    // +0x04: large embedded buffer (0x8000 bytes) for initialization data
    // Subsequent member interactions use explicit offsets inside this buffer
    unsigned char dataBuffer[0x8000];

    // Constructor (__thiscall, this in ECX)
    GodfatherGameManager() {
        // Store global singleton reference
        g_pGodfatherGameManager = this;

        // Step 1: set placeholder vtable/data pointers
        *(void**)(this + 1) = &PTR_FUN_00e2f19c;   // param_1[1] = placeholder
        *(int*)(this + 2) = 1;                       // param_1[2] = 1
        *(int*)(this + 3) = 0;                       // param_1[3] = 0

        // Step 2: set base vtable and second data pointer
        *(void**)this = &PTR_FUN_00d5da74;           // param_1[0] = base vtable
        *(void**)(this + 1) = &PTR_LAB_00d5da64;     // param_1[1] = overwritten to second pointer

        // Clear five integer fields at offsets +0x10 through +0x20
        for (int i = 4; i <= 8; ++i) {
            *(int*)(this + i) = 0;        // param_1[4]..param_1[8]
        }

        // Step 3: if external init data exists, copy 0x8000 bytes into the buffer (offset +0x04)
        if (g_pInitData != nullptr) {
            memcpy((char*)this + 4, g_pInitData, 0x8000);
        }

        // Step 4: set specific bytes inside the buffer
        *(char*)((char*)this + 0x28) = 0;   // param_1[10] = 0
        *(char*)((char*)this + 0x29) = 0;   // param_1 + 0x29 = 0
        *(int*)((char*)this + 0x2C) = 0;    // param_1[0xb] = 0

        // Note: The object layout places vtable at +0x00 and a 0x8000-byte buffer at +0x04.
        // Offsets 0x28 and 0x2C lie within this buffer.
    }
};