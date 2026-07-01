// FUNC_NAME: sumSixFloatComponents
double sumSixFloatComponents(void* objectPtr) {
    // Sum six consecutive float values starting at offset 0x14 from the object
    // Offsets: +0x14, +0x18, +0x1C, +0x20, +0x24, +0x28
    float* values = (float*)((uint8_t*)objectPtr + 0x14);
    return (double)values[0] + (double)values[1] + (double)values[2] +
           (double)values[3] + (double)values[4] + (double)values[5];
}