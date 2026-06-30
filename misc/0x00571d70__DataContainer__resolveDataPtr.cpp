// FUNC_NAME: DataContainer::resolveDataPtr

int* DataContainer::resolveDataPtr(void)
{
    // this[0xb] (offset 0x2c) holds flags
    // Flag 0x20 indicates whether to use large/external storage
    if ((this[0xb] & 0x20U) != 0)
    {
        // this[0] (offset 0x00) is the element count/type discriminator
        if (2 < *this)  // count > 2: external pointer at this[0xc] (offset 0x30)
        {
            return (int *)this[0xc];
        }
        if (*this == 2) // count == 2: inline data starts at offset 0x30
        {
            return this + 0xc;
        }
    }
    // Small/fixed storage: inline array at offset 0x1c (this + 7)
    return this + 7;
}