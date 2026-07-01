// FUNC_NAME: GodfatherGameManager::updateTick
// Reconstructed from Ghidra decompile at 0x00843d00
// This appears to be the main game object update function, handling initialization,
// first-frame logic, and per-frame processing of a primary game entity.
// It uses a counter at this+0x48 to track first call, sets global flags,
// checks a magic number (GUID) at entity+0x134 for type identification,
// and performs string operations via FUN_00815250.

#include <cstdint>
#include <cstring>

// Forward declarations for called functions (not shown)
bool FUN_004464d0(const char*); // debug break?
void FUN_00843b60(); // exit?
void FUN_0040b7a0(); // debug output?
void FUN_004d3bc0(uint32_t); // unknown
void FUN_004d57e0(); // unknown
uint32_t FUN_00815250(uint32_t, uint32_t, const char*); // string/allocation? returns handle
void FUN_00842970(); // unknown
void FUN_008c6de0(); // unknown
void FUN_0093c210(); // unknown
void FUN_0081dd40(int); // unknown
void FUN_0081e2a0(); // unknown
void FUN_00842f30(); // unknown
void FUN_008439c0(); // unknown
void FUN_00409d80(int); // unknown (maybe sleep?)
void FUN_00447bf0(); // unknown
void FUN_00440c20(); // unknown

// Global variables (offsets approximate)
extern uint8_t DAT_012055a1; // byte, likely g_isFirstFrame
extern uint8_t DAT_012055a2; // byte, likely g_hasValidEntity
extern int DAT_0112dba8; // pointer, likely g_someGlobal
extern uint32_t DAT_0112dcc4; // perhaps a backup of some value
extern uint32_t DAT_0112dcc8;
extern uint32_t DAT_01223394; // pointer, likely g_anotherGlobal
extern uint32_t DAT_00d5ef70; // float threshold
extern float _DAT_00d5780c; // float constant
extern uint8_t DAT_0120546e; // some string? maybe a default string
extern int DAT_01129904; // pointer to some object

class GodfatherGameManager {
public:
    // Offsets from this:
    // +0x20: pointer to some object (e.g., Entity)
    // +0x38: pointer to entity with GUID at +0x134 etc.
    // +0x3C: some value (backup for +0x40)
    // +0x40: stored value
    // +0x48: call counter (incremented each update)
    // +0x4C: flags (bitfield)
    // +0x50, +0x54: parameters for string operation
    // +0x58: bool flag for string processing
    // +0x5C: result of string operation
    // +0x61: byte flag (set to 0 at start, checked for exit)

    uint32_t __thiscall updateTick();
};

uint32_t __thiscall GodfatherGameManager::updateTick() {
    uint32_t* thisPtr = this; // for clarity with offset access
    int iVar1;
    const char* cleanupStr; // puStack_10
    uint32_t handle; // uVar3
    float elapsedTime; // fVar4

    // Reset exit flag
    *(uint8_t*)((uint8_t*)this + 0x61) = 0;

    // Possibly a breakpoint or debug check
    FUN_004464d0(&LAB_00842ec0);

    iVar1 = DAT_0112dba8; // global pointer

    if (*(uint8_t*)((uint8_t*)this + 0x61) != 0) {
        // If exit flag was set (maybe by debug break?), quit
        FUN_00843b60();
        return 0;
    }

    // Backup and zero out some global values
    DAT_0112dcc4 = *(uint32_t*)(DAT_0112dba8 + 0x20);
    DAT_0112dcc8 = *(uint32_t*)(DAT_0112dba8 + 0x24);
    *(uint32_t*)(DAT_0112dba8 + 0x20) = 0;
    *(uint32_t*)(iVar1 + 0x24) = 0;

    if (*(uint32_t*)((uint8_t*)this + 0x20) != 0) {
        // Call a virtual function on the object at this+0x20 (probably getElapsedTime)
        // The function at offset +0x54 in vtable (after +4 for vtable pointer)
        elapsedTime = ( (*(code**) ( *(uint32_t*)( *(uint32_t*)((uint8_t*)this + 0x20) + 4 ) + 0x54 ) )();
        iVar1 = DAT_01223394;
        if (elapsedTime < (float)DAT_00d5ef70) {
            // If elapsed time is less than a threshold, set some flags
            *(uint32_t*)(DAT_01223394 + 0x40) = 0;
            *(uint32_t*)(iVar1 + 0x2c) = *(uint32_t*)&_DAT_00d5780c; // copy float as uint
            *(uint32_t*)(iVar1 + 0x28) = 0;
            *(uint8_t*)(iVar1 + 0x25) = 1;
            *(uint8_t*)(iVar1 + 0x24) = 1;
            *(uint8_t*)(iVar1 + 0x38) = 0;
            FUN_0040b7a0(); // debug output
        }
    }

    if (DAT_012055a1 != 0) {
        // If first frame happened, exit early? No, continue with cleanup
        FUN_00843b60();
        // Clear bit 9 (0x200) of flags
        *(uint32_t*)((uint8_t*)this + 0x4c) &= ~0x200;
    }

    // Increment call counter
    iVar1 = *(uint32_t*)((uint8_t*)this + 0x48);
    *(uint32_t*)((uint8_t*)this + 0x48) = iVar1 + 1;
    if (iVar1 == 0) {
        // First call: set global first-frame flag and backup this+0x3C to this+0x40
        DAT_012055a1 = 1;
        *(uint32_t*)((uint8_t*)this + 0x40) = *(uint32_t*)((uint8_t*)this + 0x3C);
    }

    iVar1 = *(uint32_t*)((uint8_t*)this + 0x38); // pointer to some entity
    *(uint32_t*)((uint8_t*)this + 0x5C) = 0; // clear handle

    if (iVar1 != 0) {
        // Check GUID at offsets +0x134..0x140 (four ints)
        // Two possible checks: either all four are specific magic values (class ID?) or all zero
        int* guidPtr = (int*)(iVar1 + 0x134);
        if ( (guidPtr[0] == -0x45245246 && guidPtr[1] == -0x41104111 &&
              guidPtr[2] == -0x153ea5ab && guidPtr[3] == -0x6eeff6ef) ||
             (guidPtr[0] == 0 && guidPtr[1] == 0 && guidPtr[2] == 0 && guidPtr[3] == 0) ) {
            DAT_012055a2 = 0; // invalid entity
        } else {
            DAT_012055a2 = 1; // valid entity
            if (*(uint8_t*)((uint8_t*)this + 0x58) != 0) {
                // Perform string/allocation operation
                // The entity at +0x38 has a member at +0xFC which points to some data; +4 offset is used
                FUN_004d3bc0( *(uint32_t*)( *(uint32_t*)(iVar1 + 0xFC) + 4 ) );
                FUN_004d57e0();
                // Use cleanup structure (possibly SEH or scope guard)
                cleanupStr = (const char*)puStack_10; // from stack variable
                if (cleanupStr == nullptr) {
                    cleanupStr = &DAT_0120546e; // default string
                }
                handle = FUN_00815250(*(uint32_t*)((uint8_t*)this + 0x50),
                                      *(uint32_t*)((uint8_t*)this + 0x54),
                                      cleanupStr);
                *(uint32_t*)((uint8_t*)this + 0x5C) = handle;
                FUN_00842970();
                *(uint8_t*)((uint8_t*)this + 0x58) = 0; // clear flag
                if (puStack_10 != nullptr) {
                    // Execute cleanup function (via stack pointer)
                    ((code*)pcStack_4)(puStack_10);
                }
            }
        }
    }

    // Another global check
    if (*(uint8_t*)(DAT_01129904 + 0x3D) != 0) {
        *(uint32_t*)((uint8_t*)this + 0x4C) |= 0x2000;
        FUN_008c6de0();
    }

    if ((*(uint32_t*)((uint8_t*)this + 0x4C) & 0x1000) == 0) {
        *(uint32_t*)((uint8_t*)this + 0x4C) |= 0x1000;
        FUN_0093c210();
    }

    // Various system updates
    FUN_0081dd40(1);
    FUN_0081e2a0();
    FUN_00842f30();

    if (*(uint32_t*)((uint8_t*)this + 0x38) != 0 &&
        (*(uint32_t*)(*(uint32_t*)((uint8_t*)this + 0x38) + 0x118) >> 1 & 1) == 0) {
        FUN_008439c0();
    }

    if ((*(uint32_t*)((uint8_t*)this + 0x4C) >> 5 & 1) != 0) {
        *(uint32_t*)((uint8_t*)this + 0x4C) &= ~0x20;
    }

    FUN_00409d80(10); // possibly a yield/delay

    if (*(uint32_t*)((uint8_t*)this + 0x38) != 0 &&
        (*(uint32_t*)(*(uint32_t*)((uint8_t*)this + 0x38) + 0x118) >> 1 & 1) == 0) {
        FUN_00447bf0();
    }

    if ((*(uint32_t*)((uint8_t*)this + 0x4C) >> 6 & 1) == 0) {
        FUN_00440c20();
        *(uint32_t*)((uint8_t*)this + 0x4C) |= 0x40;
    }

    // Clear bits 0 and 1? Actually mask off 0x7E (bits 1,2,3,4,5,6)
    *(uint32_t*)((uint8_t*)this + 0x4C) &= 0xFFFFFF7E; // clear bits 1-6, keep bit 0 and high bits

    return 1;
}