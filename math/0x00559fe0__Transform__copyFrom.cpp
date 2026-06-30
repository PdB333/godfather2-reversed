// FUNC_NAME: Transform::copyFrom
// Function at 0x00559fe0: Copies a subset of fields from another Transform (header + 4x3 matrix, skipping 3 fields).
// Likely a member function of a transform class used in the EARS engine.

void __thiscall Transform::copyFrom(const Transform* other) {
    // Copy header fields (offsets 0x00 to 0x10: 5 ints)
    this->field0 = other->field0;   // +0x00
    this->field1 = other->field1;   // +0x04
    this->field2 = other->field2;   // +0x08
    this->field3 = other->field3;   // +0x0C
    this->field4 = other->field4;   // +0x10

    // Skip offsets 0x14-0x1C (3 fields, e.g., padding or unrelated data)

    // Copy 4x3 matrix (12 floats) starting at offset 0x20 (index 8)
    this->matrix[0] = other->matrix[0];   // +0x20
    this->matrix[1] = other->matrix[1];   // +0x24
    this->matrix[2] = other->matrix[2];   // +0x28
    this->matrix[3] = other->matrix[3];   // +0x2C
    this->matrix[4] = other->matrix[4];   // +0x30
    this->matrix[5] = other->matrix[5];   // +0x34
    this->matrix[6] = other->matrix[6];   // +0x38
    this->matrix[7] = other->matrix[7];   // +0x3C
    this->matrix[8] = other->matrix[8];   // +0x40
    this->matrix[9] = other->matrix[9];   // +0x44
    this->matrix[10] = other->matrix[10]; // +0x48
    this->matrix[11] = other->matrix[11]; // +0x4C
}