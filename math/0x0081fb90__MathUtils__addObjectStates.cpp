// FUNC_NAME: MathUtils::addObjectStates
// Address: 0x0081fb90
// Role: Adds two ObjectState structures element-wise into a destination state.
// Fields at specific offsets represent position, velocity, angular velocity, orientation, etc.
// The function first calls an initialization routine on srcA.

struct ObjectState {
    // Offsets based on decompiled additions:
    // +0x50: first vector component group (likely translation x,y,z,w)
    // +0x54, +0x58, +0x5c
    // +0x60: second group (maybe velocity)
    // +0x64 (=0x64 = 100 decimal), +0x68, +0x6c
    // +0x70: third group (angular velocity? orientation?)
    // +0x74, +0x78, +0x7c
    // +0x80: fourth group (other orientation or scale)
    // +0x84, +0x88, +0x8c
    // +0x90: fifth group (maybe extra velocity/force)
    // +0x94, +0x98
    // +0xa0: sixth group (misc)
    // +0xa4
    float m_fields[0xa8 / 4]; // approximate sized array for clarity
};

// Pre-processing helper (calls FUN_0081fac0).
// Assumed to normalize or prepare srcA for addition.
void preprocessObjectState(ObjectState* state);

ObjectState* __cdecl addObjectStates(ObjectState* dest, const ObjectState* srcA, const ObjectState* srcB) {
    preprocessObjectState(const_cast<ObjectState*>(srcA));

    // Add first block (offset 0x50 - 0x5c)
    dest->m_fields[0x50 / 4] = srcA->m_fields[0x50 / 4] + srcB->m_fields[0x50 / 4];
    dest->m_fields[0x54 / 4] = srcA->m_fields[0x54 / 4] + srcB->m_fields[0x54 / 4];
    dest->m_fields[0x58 / 4] = srcA->m_fields[0x58 / 4] + srcB->m_fields[0x58 / 4];
    dest->m_fields[0x5c / 4] = srcA->m_fields[0x5c / 4] + srcB->m_fields[0x5c / 4];

    // Add second block (offset 0x80 - 0x8c)
    dest->m_fields[0x80 / 4] = srcA->m_fields[0x80 / 4] + srcB->m_fields[0x80 / 4];
    dest->m_fields[0x84 / 4] = srcA->m_fields[0x84 / 4] + srcB->m_fields[0x84 / 4];
    dest->m_fields[0x88 / 4] = srcA->m_fields[0x88 / 4] + srcB->m_fields[0x88 / 4];
    dest->m_fields[0x8c / 4] = srcA->m_fields[0x8c / 4] + srcB->m_fields[0x8c / 4];

    // Add third block (offset 0x70 - 0x7c)
    dest->m_fields[0x70 / 4] = srcA->m_fields[0x70 / 4] + srcB->m_fields[0x70 / 4];
    dest->m_fields[0x74 / 4] = srcA->m_fields[0x74 / 4] + srcB->m_fields[0x74 / 4];
    dest->m_fields[0x78 / 4] = srcA->m_fields[0x78 / 4] + srcB->m_fields[0x78 / 4];
    dest->m_fields[0x7c / 4] = srcA->m_fields[0x7c / 4] + srcB->m_fields[0x7c / 4];

    // Add fourth block (offset 0x60 - 0x6c)
    dest->m_fields[0x60 / 4] = srcA->m_fields[0x60 / 4] + srcB->m_fields[0x60 / 4];
    dest->m_fields[0x64 / 4] = srcA->m_fields[0x64 / 4] + srcB->m_fields[0x64 / 4];
    dest->m_fields[0x68 / 4] = srcA->m_fields[0x68 / 4] + srcB->m_fields[0x68 / 4];
    dest->m_fields[0x6c / 4] = srcA->m_fields[0x6c / 4] + srcB->m_fields[0x6c / 4];

    // Add fifth block (offset 0x90 - 0x98)
    dest->m_fields[0x90 / 4] = srcB->m_fields[0x90 / 4] + srcA->m_fields[0x90 / 4];
    dest->m_fields[0x94 / 4] = srcA->m_fields[0x94 / 4] + srcB->m_fields[0x94 / 4];
    dest->m_fields[0x98 / 4] = srcA->m_fields[0x98 / 4] + srcB->m_fields[0x98 / 4];

    // Add sixth block (offset 0xa0 - 0xa4)
    dest->m_fields[0xa0 / 4] = srcA->m_fields[0xa0 / 4] + srcB->m_fields[0xa0 / 4];
    dest->m_fields[0xa4 / 4] = srcA->m_fields[0xa4 / 4] + srcB->m_fields[0xa4 / 4];

    return dest;
}