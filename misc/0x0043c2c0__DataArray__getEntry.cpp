// FUNC_NAME: DataArray::getEntry
// Returns a pointer (as int) to an array element of size 0x1c bytes.
// this+0x4: pointer to a data block with an 8-byte header, then array entries.
// index: zero-based index into the array.
int __thiscall DataArray::getEntry(int thisPtr, int index)
{
    // Read the base pointer stored at offset +0x4 of this object
    int* dataBlock = *(int**)(thisPtr + 4);
    // Array starts at offset +8 from dataBlock, each entry is 0x1c bytes
    return (int)((char*)dataBlock + 8 + index * 0x1c);
}