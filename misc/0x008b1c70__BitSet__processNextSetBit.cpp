// FUNC_NAME: BitSet::processNextSetBit

// 0x008b1c70: Advances the current bit index in the bitset until hitting the next set bit, triggering allocation events sized at 0x20 bytes each time a set bit is found.

class BitSet {
public:
    uint32_t currentBitIndex;  // +0x18, index of next bit to check
    uint32_t totalBitCount;    // +0x2c, total number of bits tracked
    uint8_t doneFlag;          // +0x1c set to 1 once past the last bit

    uint8_t* GetBitData() const { // +0x0c, pointer to packed byte array
        return *reinterpret_cast<uint8_t**>(reinterpret_cast<uintptr_t>(this) + 0x0c);
    }
};

void __thiscall BitSet::processNextSetBit() {
    uint32_t idx = this->currentBitIndex;
    uint32_t total = this->totalBitCount;

    if (idx < total) {
        uint8_t* data = this->GetBitData();
        uint8_t byteVal = data[idx >> 3];

        // advance index before checking (post‑increment)
        this->currentBitIndex = idx + 1;

        if ((byteVal & (1 << (idx & 7))) != 0) {
            // set bit found – trigger some per‑bit action (e.g. packet allocation)
            // The loop below originally used 'this' as count, likely a decompiler artefact.
            // In practice it may be the number of packed bytes or set bits.
            FUN_0064b9e0(0x20, &this);               // allocate or log for the first set bit
            for (int i = this->totalBitCount; i != 0; --i) { // plausible: iterate all bits again?
                FUN_0064b9e0(0x20, &this);
            }
        }
    } else {
        this->doneFlag = 1;
    }
}