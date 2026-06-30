// FUNC_NAME: Handle::getDecodedValue
// Function at 0x0054eb10: Decodes a packed handle value stored in the Handle object.
// The raw handle is read from a nested structure: this->handleDataPtr + 0x2c.
// The top 2 bits of the raw handle indicate the type:
//   0x00000000 – immediate bitmask (1 << bits[5..9])
//   0x40000000 – direct index into a global table at offset 8
//   0x80000000 – sentinel value (0x80000000)
//   0xC0000000 – direct index into a global table at offset 0x54

class Handle {
public:
    // Offset +0x18: pointer to handle data structure (e.g., a HandleBlock)
    // handleData +0x2c: raw handle value (uint32)
    int __thiscall getDecodedValue() const {
        uint32 rawHandle = *(uint32*)(*(uint32*)((uint8*)this + 0x18) + 0x2c);
        uint32 type = rawHandle & 0xC0000000;

        if (type == 0) {
            // Bitmask from bits [9:5] (5-bit shift amount)
            uint32 shift = (rawHandle >> 5) & 0x1F;
            return 1 << shift;
        }

        if (type == 0x40000000) {
            // Index into table at absolute address 0x08
            return *(int*)(rawHandle * 4 + 8);
        }

        if (type == 0xC0000000) {
            // Index into table at absolute address 0x54
            return *(int*)(rawHandle * 4 + 0x54);
        }

        // Remaining type (0x80000000) returns sentinel
        return 0x80000000; // -2147483648
    }
};