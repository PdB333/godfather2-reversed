// FUNC_NAME: UnknownClass::setTransformData
void __thiscall UnknownClass::setTransformData(UnknownClass *this, uint32_t param) {
    // Temporary buffer to hold 48 bytes of transform data from param
    struct TransformElement {
        double part0; // 8 bytes
        float  part1; // 4 bytes
    } tempBuffer[4]; // 4 * 12 = 48 bytes

    // Convert param (likely an ID or index) into 4 transform elements
    FUN_0043a2a0(&tempBuffer, param);

    // Copy each element into the object's member fields
    // Offsets relative to this:
    // +0x20 : first 8 bytes of element 0
    // +0x28 : next 4 bytes of element 0
    // +0x2c : first 8 bytes of element 1
    // +0x34 : next 4 bytes of element 1
    // +0x38 : first 8 bytes of element 2
    // +0x40 : next 4 bytes of element 2
    // +0x44 : first 8 bytes of element 3
    // +0x4c : next 4 bytes of element 3
    *(double *)(this + 0x20) = tempBuffer[0].part0;
    *(double *)(this + 0x2c) = tempBuffer[1].part0;
    *(double *)(this + 0x38) = tempBuffer[2].part0;
    *(double *)(this + 0x44) = tempBuffer[3].part0;
    *(float  *)(this + 0x28) = tempBuffer[0].part1;
    *(float  *)(this + 0x34) = tempBuffer[1].part1;
    *(float  *)(this + 0x40) = tempBuffer[2].part1;
    *(float  *)(this + 0x4c) = tempBuffer[3].part1;
}