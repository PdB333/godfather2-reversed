// FUNC_NAME: ManagerBase::getObjectBySlotIndex
int __thiscall ManagerBase::getObjectBySlotIndex(uint index) {
    // Array of 11 entries starts at this+0x18, each entry is 0x14 bytes.
    // The first 4 bytes of each entry store a pointer to a member at offset 0x48 of the containing object.
    if (index < 11) {
        int* pEntryBase = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x18);
        int* pMember = reinterpret_cast<int*>(pEntryBase[index * 5]); // stride 0x14 = 5 ints
        if (pMember != nullptr) {
            // Subtract 0x48 to get the address of the containing object (member is at +0x48)
            return reinterpret_cast<int>(reinterpret_cast<char*>(pMember) - 0x48);
        }
    }
    return 0;
}