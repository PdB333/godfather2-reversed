// FUNC_NAME: EARS::Framework::BoundingBox::init
void __thiscall BoundingBox::init(float* vec1, float* vec2, float param4, float param5, float param6, float param7)
{
    // Clear flag byte (offset 0x08)
    *(byte*)((uint)this + 8) = 0;
    this->taggedPtr = 0;                                    // +0x24 (index 9)
    this->colorR = param4;                                  // +0x34 (index 0xD)
    this->colorG = param5;                                  // +0x38 (index 0xE)
    this->colorB = param6;                                  // +0x3C (index 0xF)
    this->colorA = param7;                                  // +0x40 (index 0x10)
    this->typeId = 0x3E0;                                   // +0x30 (index 0xC), constant 1008

    // Copy first vector (e.g., min point)
    this->x1 = vec1[0];                                     // +0x00
    this->y1 = vec1[1];                                     // +0x04
    this->z1 = vec1[2];                                     // +0x08 (low byte overwritten by flag)
    this->pad1 = 0;                                         // +0x0C

    // Copy second vector (e.g., max point)
    this->x2 = vec2[0];                                     // +0x10
    this->y2 = vec2[1];                                     // +0x14
    this->z2 = vec2[2];                                     // +0x18
    this->pad2 = 0;                                         // +0x1C

    // Set flag to 1 (valid)
    *(byte*)((uint)this + 8) = 1;

    // Build tagged pointer to the 'typeId' field (offset 0x30)
    this->taggedPtr = ((uint)(this + 0xC) >> 2) | 0x40000000;
}