// FUNC_NAME: DataBuffer::setDataArray
// Function address: 0x006600e0
// Copies an array of uint32 values from external source into internal buffer.
// Implicit parameters: this (EDI), count (ESI), source (param_1 on stack)
void DataBuffer::setDataArray(uint32_t *source, uint32_t count)
{
    // Pointer to the destination array stored at offset +0x8 in this object
    uint32_t *dest = *(uint32_t **)((uint8_t *)this + 8);
    uint32_t i = 0;

    if (count != 0) {
        do {
            if (dest != nullptr) {
                dest[i] = source[i];
            }
            i++;
        } while (i < count);
    }
}