// FUNC_NAME: UnknownStruct::equals (equality check for 17-byte structure: 4 ints + 1 byte)
// Function address: 0x00991dc0
// Returns 0 if equal, 1 if not equal (matching original binary behavior)

struct AssetID { // guess: 4 ints (16 bytes) + 1 byte char field
    int field0;
    int field4;
    int field8;
    int field12;
    char field16;   // low byte of the 5th int if packed into int boundaries
};

// __thiscall: parameter_1 (this) and parameter_2 (other) are pointers to AssetID
int __thiscall UnknownStruct::equals(AssetID* this, AssetID* other) {
    // Compare first four ints (offsets 0,4,8,12)
    if (this->field0 != other->field0) return 1;
    if (this->field4 != other->field4) return 1;
    if (this->field8 != other->field8) return 1;
    if (this->field12 != other->field12) return 1;
    // Compare the byte field at offset 16 (cast to char to isolate low byte)
    if (this->field16 != other->field16) return 1;
    return 0;
}