// FUNC_NAME: ArrayBuffer::isValidIndex
// Function at 0x004b4e20 - checks if an index is within a valid range [start, start+length)
bool __thiscall ArrayBuffer::isValidIndex(uint index) const
{
    uint startIndex = *(uint*)(this + 0xc); // +0x0c: start index
    int length = *(int*)(this + 0x10);       // +0x10: number of elements
    if (startIndex <= index && index < startIndex + length) {
        return true;
    }
    return false;
}