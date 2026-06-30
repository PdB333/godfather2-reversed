// FUN_004dfdd0: updateEffectPools
// Address: 0x004dfdd0
// Role: Per-frame update of 7 effect pools (each with a pointer and counter).
// For each pool, attempts to allocate an object. On failure, frees the pool.
// On success, increments a 15-bit sequence number at object+0x14 (wrapping via XOR).
// Pool7 reverses the logic: update on success and return immediately.

#include <cstdint>

// Forward declarations for external functions
void* allocateFromPool();               // FUN_00407da0
void freeToPool(void* pool, uint32_t size); // FUN_004084d0

// Global pool control blocks (static data)
extern void* g_effectPool1;       // 0x012069d4, pointer to pool memory
extern int32_t g_effectPool1Counter; // 0x012069d8, tick counter
extern void* g_effectPool2;       // 0x012069ec
extern int32_t g_effectPool2Counter; // 0x012069f0
extern void* g_effectPool3;       // 0x01206960
extern int32_t g_effectPool3Counter; // 0x01206964
extern void* g_effectPool4;       // 0x01206980
extern int32_t g_effectPool4Counter; // 0x01206984
extern void* g_effectPool5;       // 0x01206978
extern int32_t g_effectPool5Counter; // 0x0120697c
extern void* g_effectPool6;       // 0x01206968
extern int32_t g_effectPool6Counter; // 0x0120696c
extern void* g_effectPool7;       // 0x01206970
extern int32_t g_effectPool7Counter; // 0x01206974

// Helper: update the 15-bit sequence number at object offset +0x14
static void updateSequenceNumber(void* obj) {
    uint16_t val = *(uint16_t*)((uint8_t*)obj + 0x14);
    // Bit-twiddling: (short)(val*2>>1) == val (since val is u16), then (val+1)^val, &0x7fff, ^val
    // Effectively increments a 15-bit counter with the top bit acting as a toggle?
    uint16_t newVal = ((int16_t)(((uint32_t)val * 2) >> 1) + 1) ^ val;
    newVal = (newVal & 0x7fff) ^ val;
    *(uint16_t*)((uint8_t*)obj + 0x14) = newVal;
}

void updateEffectPools(void) {
    // Pool1 (size 0x4000)
    if (g_effectPool1) {
        g_effectPool1Counter++;
        void* obj = allocateFromPool();
        if (obj == nullptr) {
            freeToPool(g_effectPool1, 0x4000);
        } else {
            updateSequenceNumber(obj);
        }
    }

    // Pool2 (size 0x4000)
    if (g_effectPool2) {
        g_effectPool2Counter++;
        void* obj = allocateFromPool();
        if (obj == nullptr) {
            freeToPool(g_effectPool2, 0x4000);
        } else {
            updateSequenceNumber(obj);
        }
    }

    // Pool3 (size 0x8000)
    if (g_effectPool3) {
        g_effectPool3Counter++;
        void* obj = allocateFromPool();
        if (obj == nullptr) {
            freeToPool(g_effectPool3, 0x8000);
        } else {
            updateSequenceNumber(obj);
        }
    }

    // Pool4 (size 0x8000)
    if (g_effectPool4) {
        g_effectPool4Counter++;
        void* obj = allocateFromPool();
        if (obj == nullptr) {
            freeToPool(g_effectPool4, 0x8000);
        } else {
            updateSequenceNumber(obj);
        }
    }

    // Pool5 (size 0x8000)
    if (g_effectPool5) {
        g_effectPool5Counter++;
        void* obj = allocateFromPool();
        if (obj == nullptr) {
            freeToPool(g_effectPool5, 0x8000);
        } else {
            updateSequenceNumber(obj);
        }
    }

    // Pool6 (size 0x8000)
    if (g_effectPool6) {
        g_effectPool6Counter++;
        void* obj = allocateFromPool();
        if (obj == nullptr) {
            freeToPool(g_effectPool6, 0x8000);
        } else {
            updateSequenceNumber(obj);
        }
    }

    // Pool7 (size 0x8000) – early return on successful allocation
    if (g_effectPool7) {
        g_effectPool7Counter++;
        void* obj = allocateFromPool();
        if (obj != nullptr) {
            updateSequenceNumber(obj);
            return; // original code returns immediately after update
        }
        freeToPool(g_effectPool7, 0x8000);
    }
}