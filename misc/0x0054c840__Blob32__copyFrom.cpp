// FUNC_NAME: Blob32::copyFrom
// Function at 0x0054c840: Copies 32 bytes (8 dwords) from source to this.
// This is a member function of a 32-byte data block, likely used for
// copying network packets, transformations, or other fixed-size structures.
void __thiscall Blob32::copyFrom(Blob32* this, const Blob32* source)
{
    // Copy 8 dwords (32 bytes) from source to this.
    this->data[0] = source->data[0];
    this->data[1] = source->data[1];
    this->data[2] = source->data[2];
    this->data[3] = source->data[3];
    this->data[4] = source->data[4];
    this->data[5] = source->data[5];
    this->data[6] = source->data[6];
    this->data[7] = source->data[7];
}