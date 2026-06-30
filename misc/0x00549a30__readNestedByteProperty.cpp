// FUNC_NAME: readNestedByteProperty
void __thiscall readNestedByteProperty(void* this, uint8_t* outByte)
{
    // this+0x18 -> pointer to an internal data structure
    void* internalData = *(void**)((char*)this + 0x18);
    // internalData+0x10 -> byte field value
    *outByte = *(uint8_t*)((char*)internalData + 0x10);
}