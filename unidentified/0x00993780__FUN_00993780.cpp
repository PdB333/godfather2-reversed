// FUNC_NAME: SomeClass::setArrayConstant

void SomeClass::setArrayConstant(uint thisPtr, uint fillValue)
{
    // Pre-processing step
    preProcess(thisPtr, fillValue);

    // Combined descriptor: 40-byte internal buffer + base pointer and stride
    struct {
        uint8_t internalBuffer[40];
        int32_t stride;   // +0x28
        uint32_t* base;   // +0x2C
    } descriptor;

    // Retrieve array range info; stores base and stride in descriptor beyond the buffer
    if (getArrayRange(thisPtr, 2, 0, descriptor.internalBuffer))
    {
        // Fill 4 elements (each 16 bytes) with the constant value
        for (int i = 0; i < 4; i++)
        {
            uint32_t* element = descriptor.base + i * descriptor.stride;
            element[0] = fillValue;
            element[1] = fillValue;
            element[2] = fillValue;
            element[3] = fillValue;
        }

        // Release the range descriptor
        releaseArrayRange(descriptor.internalBuffer);
    }
}