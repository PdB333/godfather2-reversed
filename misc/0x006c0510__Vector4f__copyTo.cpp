// FUNC_NAME: Vector4f::copyTo
void __thiscall Vector4f::copyTo(void *thisPtr, float *outArray)
{
    // Copy four float components from object offsets +0x10 through +0x1c
    outArray[0] = *(float *)((char *)thisPtr + 0x10);
    outArray[1] = *(float *)((char *)thisPtr + 0x14);
    outArray[2] = *(float *)((char *)thisPtr + 0x18);
    outArray[3] = *(float *)((char *)thisPtr + 0x1c);
}