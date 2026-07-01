// FUNC_NAME: PacketPool::allocatePacket
// Address: 0x0094ce60
// Role: Allocates a packet from a pool based on reliability and type flags.
// Uses global debug flag (DAT_0112af90 + 0x48) to set extra flag 0x80.

typedef unsigned int uint;

// Forward declarations of callees
uint FUN_00949ee0(uint param);
void FUN_00408680(void* mutex); // likely a mutex lock
void* FUN_0094ab00(uint* param); // returns pointer to store result
void FUN_004de190(); // error handler
uint FUN_0094c4d0(uint uVar2, uint param_2, uint param_3, uint uVar5, uint param_7, uint param_8);

// Global debug flag (DAT_0112af90 + 0x48)
extern char* g_globalDebug; // DAT_0112af90

// Global mutex (DAT_011301a8)
extern void* g_packetMutex; // DAT_011301a8

// __thiscall: ecx = this
uint __thiscall PacketPool::allocatePacket(uint this_,
                                               uint param_2,
                                               uint param_3,
                                               uint param_4,
                                               int param_5,
                                               int param_6,
                                               uint param_7,
                                               uint param_8)
{
    uint* puVar1;          // temporary free list node
    uint  uVar2;           // result from FUN_00949ee0 (likely packet ID/sequence)
    uint* puVar3;          // output pointer from FUN_0094ab00
    uint  uVar4;           // intermediate
    uint  uVar5;           // combined flags

    // Get base value from param_4 - might be a hash or ID
    uVar2 = FUN_00949ee0(param_4);

    uVar5 = 0;
    // Determine reliability flags
    if (param_6 == 0) {
        uVar5 = 0x200;         // reliable?
    } else if (param_6 == 1) {
        uVar5 = 0x100;         // unreliable?
    }

    // Set packet type flags
    if (param_5 == 1) {
        uVar5 |= 1;            // data packet?
    } else if (param_5 == 3) {
        uVar5 |= 4;            // control packet?
    }

    param_4 = uVar2;           // param_4 is reused, now holds the ID

    // Check global debug flag at offset 0x48
    if (*(char*)(g_globalDebug + 0x48) == '\0') {
        uVar5 |= 0x80;         // debug flag
        FUN_00408680(&g_packetMutex); // acquire mutex
    }

    // Allocate a storage slot for the result (probably a pointer to pointer)
    puVar3 = (uint*)FUN_0094ab00(&param_4);

    // Validate pool state: if free list head is 0 and secondary check fails, call error handler
    if ((*(int*)(this_ + 0x5c) == 0) &&
        ((*(int*)(this_ + 0x58) == 0 || ((*(byte*)(this_ + 0x4c) & 1) == 0)))) {
        FUN_004de190(); // pool exhaustion error
    }

    puVar1 = *(uint**)(this_ + 0x5c); // free list head
    if (puVar1 != (uint*)0x0) {
        uVar4 = *puVar1;        // next free node
        // Update pool counters
        *(int*)(this_ + 0x38) = *(int*)(this_ + 0x38) + 1;  // allocated count
        *(int*)(this_ + 0x34) = *(int*)(this_ + 0x34) - 1;  // free count
        *(uint*)(this_ + 0x5c) = uVar4; // move free list head

        if (puVar1 != (uint*)0x0) {
            // Build the actual packet into the allocated node
            uVar4 = FUN_0094c4d0(uVar2, param_2, param_3, uVar5, param_7, param_8);
            *puVar3 = uVar4;      // store result into output pointer
            return uVar2;         // return the packet ID/sequence
        }
    }

    // No free node available, return 0
    *puVar3 = 0;
    return uVar2;
}