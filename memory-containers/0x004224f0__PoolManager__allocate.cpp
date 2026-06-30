// FUNC_NAME: PoolManager::allocate
// Function address: 0x004224f0
// Allocates a slot from a fixed-size pool of 16 entries, each 0x180 bytes.
// Returns pointer to allocated memory, or NULL if pool is full.

#include <cstdint>

// --- Global pool data (offsets from base) ---
// DAT_00e2e6f8: Critical section / mutex for pool access (size? Probably 0x18 or 0x24 bytes)
// DAT_012053b4: Array of 16 bytes, each byte = 1 if slot allocated, 0 if free
// DAT_01206bb0: Array of 16 * 0x180 = 0x1800 bytes of pool memory

extern "C" {
    extern uint8_t gPoolMutex[0x18]; // placeholder size
    extern uint8_t gSlotFlags[16];   // allocation flags
    extern uint8_t gPoolMemory[16 * 0x180]; // actual storage
}

// External synchronization functions (lock/unlock the mutex)
void poolLock(void* mutex);   // FUN_00ab4db0
void poolUnlock();            // FUN_00ab4e70

void* PoolManager::allocate() {
    poolLock(&gPoolMutex);
    
    for (uint32_t i = 0; i < 16; i++) {
        if (gSlotFlags[i] == 0) {
            gSlotFlags[i] = 1;
            poolUnlock();
            return &gPoolMemory[i * 0x180];
        }
    }
    
    poolUnlock();
    return nullptr;
}