// FUNC_NAME: ArrayOffsetManager::updateArrays
// Function address: 0x005f09e0
// This function iterates over an array of pairs (each pair: count of sub-elements and a base pointer),
// adds a base offset to each base pointer, then adds an element offset to each element in the sub-array.
// The return value encodes the last accessed element address and a flag.
// Offsets relative to 'this':
//   +0x0c: uint** m_arrayPairs;   // pointer to array of {count, basePtr} pairs
//   +0x10: uint   m_numPairs;     // number of pairs
//   +0x14: int    m_baseOffset;   // offset added to each base pointer
//   +0x18: int    m_elementOffset; // offset added to each element in sub-arrays

class ArrayOffsetManager {
public:
    uint** m_arrayPairs;      // +0x0c
    uint   m_numPairs;        // +0x10
    int    m_baseOffset;      // +0x14
    int    m_elementOffset;   // +0x18

    // Returns a 64-bit value: high 32 bits = last element address, low 32 bits = (m_arrayPairs & 0xFFFFFF00) | 1
    uint64_t updateArrays(int param2) {
        uint** puVar3 = m_arrayPairs;
        uint uVar5 = 0;

        if (m_numPairs != 0) {
            do {
                // Add base offset to the base pointer of the current pair
                puVar3[1] = puVar3[1] + m_baseOffset;

                uint uVar4 = 0;
                if (puVar3[0] != 0) {
                    do {
                        uint baseAddr = puVar3[1]; // base pointer after offset
                        int* element = (int*)(baseAddr + uVar4 * 4);
                        *element = *element + m_elementOffset;
                        param2 = baseAddr + uVar4 * 4; // track last element address
                        uVar4++;
                    } while (uVar4 < puVar3[0]);
                }

                uVar5++;
                puVar3 += 2; // move to next pair (each pair is 2 uint32s)
            } while (uVar5 < m_numPairs);
        }

        // Encode return value: high 32 bits = param2 (last element address),
        // low 32 bits = (puVar3 & 0xFFFFFF00) | 1
        return ((uint64_t)param2 << 32) | ((uint32_t)puVar3 & 0xFFFFFF00) | 1;
    }
};