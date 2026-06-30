// FUNC_NAME: MemoryManager::initialize
// Function address: 0x00644120
// Reconstructed C++ for EA EARS engine memory manager initialization

#include <windows.h> // for CRITICAL_SECTION, SYSTEM_INFO, etc.

class MemoryManager {
public:
    // +0x00: initialized flag (byte)
    // +0x04: flags (uint32)
    // +0x08..+0x2F: reserved?
    // +0x30: free list pool (128 blocks of 8 bytes each = 0x400 bytes)
    // +0x430: another small pool? (16 bytes)
    // +0x440: free list head pointer (points into pool)
    // +0x444: free list count? (4 bytes)
    // +0x448: sentinel block (8 bytes)
    // +0x450: more fields...
    // +0x460: another list head
    // +0x464: another list tail
    // +0x468..+0x48F: various flags and sizes
    // +0x490: block size? (4 bytes)
    // +0x494: alignment? (4 bytes)
    // +0x498: max blocks? (4 bytes)
    // +0x49C: another sentinel (8 bytes)
    // +0x4A4: list head for another pool
    // +0x4A8: list tail for another pool
    // +0x4C8: flags for second pool
    // +0x4CC: block size for second pool
    // +0x4D0: saved free list head
    // +0x4D4: page size (DWORD)
    // +0x4E8: critical section pointer
    // +0x51C: initialization done flag (byte)

    int initialize(int param2, int param3, int param4, int param5, int param6, int param7);
};

// Forward declaration of critical section getter
CRITICAL_SECTION* getMemoryManagerCriticalSection();

// Forward declaration of sub-allocator function
int FUN_00647e90(int param2, int param3, int param4, int param5, int param6, int param7);

int MemoryManager::initialize(int param2, int param3, int param4, int param5, int param6, int param7)
{
    // One-time initialization guard
    if (*(char*)this == '\0') {
        *(char*)this = '\x01'; // Mark as initialized

        // Get or create critical section for thread safety
        if (*(int*)((char*)this + 0x4E8) == 0) {
            *(CRITICAL_SECTION**)((char*)this + 0x4E8) = getMemoryManagerCriticalSection();
        }

        CRITICAL_SECTION* cs = *(CRITICAL_SECTION**)((char*)this + 0x4E8);
        if (cs != nullptr) {
            EnterCriticalSection(cs);
            // Increment lock count? (hacky debug info manipulation)
            cs[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&cs[1].DebugInfo->Type + 1);
        }

        // Initialize flags and small pool area (0x30 to 0x430)
        // Set flags at offset 0x04 to 0x48 (bitwise OR with 1 and 0x48)
        *(uint32*)((char*)this + 4) = (*(uint32*)((char*)this + 4) & 1) | 0x48;

        // Zero out 16 bytes at offset 0x04? Actually it's setting individual bytes from +0x04 to +0x2F
        // The decompiled shows many byte assignments, but we can simplify as memset
        memset((char*)this + 4, 0, 0x2C); // 0x04 to 0x2F inclusive? Actually 0x2C bytes from +0x04

        // Initialize free list pool at +0x30 (0x400 bytes)
        char* pool = (char*)this + 0x30;
        memset(pool, 0, 0x400);

        // Initialize 128 free blocks (each 8 bytes) as a linked list
        // Each block has next and prev pointers (8 bytes total)
        for (int i = 0; i < 128; i++) {
            char* block = pool + i * 8;
            *(char**)(block + 8) = block; // next points to self? Actually it's a circular list
            *(char**)(block + 12) = block; // prev points to self
        }

        // Zero out 16 bytes at +0x430 (another small pool)
        memset((char*)this + 0x430, 0, 16);

        // Set free list head to point to first block in pool
        *(char**)((char*)this + 0x440) = pool;

        // Initialize sentinel block at +0x448 (8 bytes)
        char* sentinel = (char*)this + 0x448;
        memset(sentinel, 0, 8);

        // Initialize another linked list at +0x460 (head and tail both point to sentinel)
        *(char**)((char*)this + 0x460) = sentinel;
        *(char**)((char*)this + 0x464) = sentinel;

        // Zero out 32 bytes at +0x468? Actually from +0x468 to +0x487
        memset((char*)this + 0x468, 0, 0x20);

        // Set block size for first pool (at +0x490)
        *(uint32*)((char*)this + 0x490) = 0; // size? Actually set to 0 then later to 1? The decompiled shows byte assignments
        // The decompiled sets bytes at +0x490..+0x493 to 0,0,1,0 => little-endian 0x01000000? Actually 0x01 at +0x492
        // So it's setting a uint32 to 0x00010000? Let's just set the bytes as per decompiled
        ((char*)this)[0x490] = 0;
        ((char*)this)[0x491] = 0;
        ((char*)this)[0x492] = 1;
        ((char*)this)[0x493] = 0;

        // Set alignment? at +0x494..+0x497 to 0,0,2,0 => 0x00020000
        ((char*)this)[0x494] = 0;
        ((char*)this)[0x495] = 0;
        ((char*)this)[0x496] = 2;
        ((char*)this)[0x497] = 0;

        // Set max blocks? at +0x498 to 0
        ((char*)this)[0x498] = 0;

        // Initialize second sentinel at +0x49C (8 bytes)
        char* sentinel2 = (char*)this + 0x49C;
        memset(sentinel2, 0, 8);

        // Zero out 8 bytes at +0x4A4? Actually from +0x4A4 to +0x4AB
        memset((char*)this + 0x4A4, 0, 8);

        // Set second pool head and tail to sentinel2
        *(char**)((char*)this + 0x4A4) = sentinel2;
        *(char**)((char*)this + 0x4A8) = sentinel2;

        // Set flags for second pool at +0x4C8..+0x4CB to 0,0,4,0 => 0x00040000
        ((char*)this)[0x4C8] = 0;
        ((char*)this)[0x4C9] = 0;
        ((char*)this)[0x4CA] = 4;
        ((char*)this)[0x4CB] = 0;

        // Set block size for second pool at +0x4CC..+0x4CF to 0,0,1,0 => 0x00010000
        ((char*)this)[0x4CC] = 0;
        ((char*)this)[0x4CD] = 0;
        ((char*)this)[0x4CE] = 1;
        ((char*)this)[0x4CF] = 0;

        // Save free list head to +0x4D0
        *(char**)((char*)this + 0x4D0) = *(char**)((char*)this + 0x440);

        // Get system page size
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        *(DWORD*)((char*)this + 0x4D4) = sysInfo.dwPageSize;

        // Leave critical section
        if (cs != nullptr) {
            // Decrement lock count (reverse of earlier hack)
            cs[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&cs[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(cs);
        }
    }

    // If param2 or param3 is non-zero, call sub-allocator
    if (param2 != 0 || param3 != 0) {
        FUN_00647e90(param2, param3, param4, param5, param6, param7);
    }

    // Call registered initialization callbacks (list at +0x51C)
    if (*(char*)((char*)this + 0x51C) == '\0') {
        *(char*)((char*)this + 0x51C) = '\x01';
        // Iterate through a global callback list (DAT_012059e4)
        for (void** callback = (void**)DAT_012059e4; callback != nullptr; callback = (void**)callback[2]) {
            ((void (*)(MemoryManager*, int, void*))callback[0])(this, 1, callback[1]);
        }
    }

    return 1;
}