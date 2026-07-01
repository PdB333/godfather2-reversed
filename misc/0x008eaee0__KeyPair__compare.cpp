// FUNC_NAME: KeyPair::compare
// Function address: 0x008eaee0
// Compares two KeyPair objects (two int32 fields: typeID and id).
// Asserts that the typeID fields are non-zero and equal.
// Returns a packed 32-bit value: high 24 bits of this->id, and low byte = (this->id != other->id).

// Offset 0x00: typeID (int32)
// Offset 0x04: id (int32)
struct KeyPair {
    int32_t typeID;
    int32_t id;
};

int __thiscall KeyPair::compare(KeyPair *this, KeyPair *other)
{
    // Precondition: typeID must be non-zero and equal between objects.
    if ((this->typeID == 0) || (this->typeID != other->typeID)) {
        FUN_00b97aea(); // likely debug assertion failure
    }

    // Return high 24 bits of this->id combined with equality flag.
    // (this->id >> 8) gives high 24 bits, then shifted left 8 bits for the high part.
    // Low 8 bits are 1 if id differs, 0 if equal.
    return ((uint32_t)(this->id >> 8) << 8) | (this->id != other->id);
}