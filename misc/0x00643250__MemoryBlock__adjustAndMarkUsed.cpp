// FUNC_NAME: MemoryBlock::adjustAndMarkUsed
void __fastcall MemoryBlock::adjustAndMarkUsed(int *this, int *entryInfo)
{
    // Entry info: pointer to a structure with offset 4 containing an index.
    // *this: pointer to memory block descriptor, with a pointer at offset 0xc to the base of an array.
    // Lookup table for character classification (bits: 0x80 = "separator"?). Based on constant string "$a $ a4A".
    static const char lookupTable[] = "$a $ a4A";
    
    // Access the array element: base[index]
    uint *element = (uint *)(*(int *)(*this + 0xc) + *(int *)(entryInfo + 4) * 4);
    
    // If not the first element and the previous element's low 6 bits match a separator (bit 0x80 set in lookup), step back.
    if ((0 < *(int *)(entryInfo + 4)) && ((lookupTable[element[-1] & 0x3f] & 0x80) != 0)) {
        element--;
    }
    
    // Set the high byte (0x01000000) if it was zero, otherwise leave unchanged.
    *element = ((*element & 0xff000000) == 0 ? 0x01000000 : 0) | (*element & 0x00ffffff);
}