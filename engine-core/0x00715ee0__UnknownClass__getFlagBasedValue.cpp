// FUNC_NAME: UnknownClass::getFlagBasedValue
int UnknownClass::getFlagBasedValue(int actionType) {
    // +0x18: pointer to some subobject (e.g., character data)
    int* subObject = *(int**)(this + 0x24); // note: offset 0x18 from this, but in code it's param_1+0x18
    // At +0x8e0 in that subobject: flags word, check bit 1
    uint flags = *(uint*)(subObject + 0x8e0);
    bool bit1Set = ((flags >> 1) & 1) != 0;

    // Returns different constants based on actionType and bit1Set
    if (actionType == 1) {
        // Constants: 0x4f2e4bfe and 0x3c45af0b
        return bit1Set ? 0x8B73FB09 : 0x3c45af0b;
    } else {
        // Constants: 0xb4b23112 and 0x25f945f8
        return bit1Set ? 0xDA4B770A : 0x25f945f8;
    }
}