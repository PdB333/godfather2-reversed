// FUNC_NAME: PoolManager::resolveIndex
// Address: 0x00637490
// Role: Indexes into a fixed-size pool (stride 0x14) using various key types.
//   The pool size is a power of two, determined by a byte at +0x7 (shift).
//   The pool pointer is at +0x10.
//   Command codes in params[0]:
//     1: mask index (params[1] & (2^shift-1))
//     2: modulo index (params[1] % (2^shift))
//     3: float index with constant offset (params[1] as float + g_floatAdjust)
//     4: indirect index from a structure at params[1], using its uint32 at offset 8
//     default: float index (params[1] as float)

extern float g_floatAdjust; // DAT_00e2b1a4

// Minimal layout of the pool manager class (offsets inferred)
struct PoolManager {
    /* 0x00 */ void* vtable;      // unconfirmed
    /* 0x04 */ uint8_t pad0[3];
    /* 0x07 */ uint8_t m_capacityShift; // e.g., 4 => capacity = 16 (1<<4)
    /* 0x08 */ uint8_t pad1[8];
    /* 0x10 */ void* m_pool;      // pointer to array of 0x14-byte elements
};

// __fastcall: ECX = this (PoolManager*), EDX = params (uint32_t[2])
int* __fastcall PoolManager::resolveIndex(void* thisPtr, uint32_t* params) {
    PoolManager* self = (PoolManager*)thisPtr;
    uint32_t command = params[0];
    uint32_t rawValue = params[1];  // interpretation depends on command
    float fValue;
    uint32_t mask;

    // Compute mask from capacity shift (must be <= 31)
    uint32_t shift = self->m_capacityShift & 0x1F;
    mask = (1 << shift) - 1;

    switch (command) {
    case 1:
        // Direct masked index
        return (int*)self->m_pool + ((mask & rawValue) * 0x14);
    case 2:
        // Modulo index (division by actual capacity)
        return (int*)self->m_pool + ((rawValue % (mask | 1)) * 0x14);
    case 3:
        // Float index with global offset added
        fValue = (float)rawValue + g_floatAdjust;
        break;
    case 4:
        // Indirect index: rawValue is a pointer, read uint32 at offset 8
        return (int*)self->m_pool + ((mask & *(uint32_t*)((uint8_t*)rawValue + 8)) * 0x14);
    default:
        // Float index without offset
        fValue = (float)rawValue;
        break;
    }

    // Cases 3 and default fall through here
    uint32_t index = (uint32_t)fValue % (mask | 1);
    return (int*)self->m_pool + (index * 0x14);
}