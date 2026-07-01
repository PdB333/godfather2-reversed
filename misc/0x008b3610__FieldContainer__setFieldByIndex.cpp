// FUNC_NAME: FieldContainer::setFieldByIndex
// Function address: 0x008b3610
// Identified role: Sets one of two 4-byte fields (at +0x54 and +0x58) based on index (0 or 1).
// Likely used for paired parameters (e.g., axis values, coefficients).

class FieldContainer {
    // +0x54: m_field0
    // +0x58: m_field1
public:
    void __thiscall setFieldByIndex(uint index, uint32_t value) {
        if (index < 2) {
            if (index == 1) {
                *(uint32_t*)((uint8_t*)this + 0x58) = value;
            } else { // index == 0
                *(uint32_t*)((uint8_t*)this + 0x54) = value;
            }
        }
    }
};