// FUNC_NAME: Destructible::updateDamageDeformationRange
// Function at 0x00589bf0: Updates vertex positions by blending a byte source (damage data) into a float buffer using random component selection.
// The object has three iterators: m_currentIdx (offset 0x34), m_currentByteSrc (offset 0x28), m_currentFloatBase (offset 0x2c).
// param1: startIndex, param2: endIndex (exclusive). Output is written to the float array in EAX (likely a vertex buffer).
// This is part of the destructible object deformation system.

// Global scale factor used to interpolate byte values (0-255) into float offsets.
extern float s_damageScale; // DAT_00e445cc

// Forward declaration of random function (likely engine's rand or hash-based).
unsigned int getRandomUInt32(); // Might be replaced with engine-specific call.

class Destructible {
public:
    // Offsets (relative to this):
    // +0x28: uint8_t* m_currentByteSrc   - pointer to source byte data (damage deltas)
    // +0x2c: float*   m_currentFloatBase - pointer to base vertex data (original positions)
    // +0x34: int32_t   m_currentIdx      - current index in the range being processed

    uint8_t* m_currentByteSrc;   // +0x28
    float*   m_currentFloatBase; // +0x2c
    int32_t  m_currentIdx;       // +0x34

    void updateDamageDeformationRange(int startIndex, int endIndex, float* outVertices);
};

void Destructible::updateDamageDeformationRange(int startIndex, int endIndex, float* outVertices) {
    int curIdx = m_currentIdx;

    // First loop: advance pointers up to startIndex, skipping indices that are not in the target range.
    // The skip size depends on a random value: if (rand & 3) == 0? Actually, the code checks (rand & 3) - 1 < 3.
    // That condition is always true for values 1,2,3 (since 0-1 = -1, which is unsigned less than 3? Not clear).
    // But according to decompiler: if ((uVar2 & 3) - 1) < 3 then add 1 to byteSrc, else add 3.
    // This effectively means: if rand%4 != 0, advance byte pointer by 1; if rand%4 == 0, advance by 3.
    while (curIdx < startIndex) {
        curIdx = m_currentIdx; // refresh? Actually the code reloads m_currentIdx each iteration (likely because it changes, but it's just curIdx after increment).
        unsigned int r = getRandomUInt32() & 3;
        if ((r - 1) < 3) { // if r != 0 (since r-1 for r=0 is 0xFFFFFFFF, which is >3, but unsigned? Actually, for r=0, 0-1 = 0xFFFFFFFF, which as unsigned is >3, so condition false)
            // r is 1,2,3 → advance byte pointer by 1
            m_currentByteSrc += 1;
        } else {
            // r is 0 → advance byte pointer by 3
            m_currentByteSrc += 3;
        }
        m_currentFloatBase += 3; // advance by one vertex (3 floats)
        curIdx += 1;
        m_currentIdx = curIdx;
    }

    // Second loop: process vertices from current index up to endIndex.
    while (curIdx < endIndex) {
        curIdx = m_currentIdx;
        unsigned int r = getRandomUInt32() & 3;
        float scale = s_damageScale;
        uint8_t* byteSrc = m_currentByteSrc;
        float* base = m_currentFloatBase;

        switch (r) {
        case 1:
            // Blend first component from byte, copy other two from base
            outVertices[0] = (float)(*byteSrc) * scale + base[0];
            outVertices[1] = base[1];
            outVertices[2] = base[2];
            byteSrc += 1;
            break;
        case 2:
            // Blend second component
            outVertices[0] = base[0];
            outVertices[1] = (float)(*byteSrc) * scale + base[1];
            outVertices[2] = base[2];
            byteSrc += 1;
            break;
        case 3:
            // Blend third component
            outVertices[0] = base[0];
            outVertices[1] = base[1];
            outVertices[2] = (float)(*byteSrc) * scale + base[2];
            byteSrc += 1;
            break;
        default: // case 0
            // Blend all three components from three consecutive bytes
            outVertices[0] = (float)(byteSrc[0]) * scale + base[0];
            outVertices[1] = (float)(byteSrc[1]) * scale + base[1];
            outVertices[2] = (float)(byteSrc[2]) * scale + base[2];
            byteSrc += 3;
            break;
        }

        // Advance pointers
        m_currentFloatBase = base + 3;
        m_currentByteSrc = byteSrc;
        outVertices += 3;
        curIdx += 1;
        m_currentIdx = curIdx;
    }
    // final curIdx == endIndex, function exits.
}