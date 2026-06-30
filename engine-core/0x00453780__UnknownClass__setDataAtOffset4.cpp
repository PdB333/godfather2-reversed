// FUNC_NAME: UnknownClass::setDataAtOffset4
void UnknownClass::setDataAtOffset4(void* thisPtr, const void* sourceData)
{
    // Copy data from sourceData into this+4 (offset 0x4 from this)
    copyData(sourceData, reinterpret_cast<char*>(thisPtr) + 4);
}