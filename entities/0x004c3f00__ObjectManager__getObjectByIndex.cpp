// FUNC_NAME: ObjectManager::getObjectByIndex
// Address: 0x004c3f00
// Returns the first 4 bytes of the 0x10-byte structure at given index from the array stored at this+0xc.
// Used to retrieve an object pointer or handle from an indexed array of 16-byte entries.
unsigned int __thiscall CObjectManager::getObjectByIndex(CObjectManager* this, int index) {
    // this+0xc: pointer to array of 16-byte structures
    // Each structure's first DWORD is the object reference (pointer or handle)
    return *(unsigned int*)(*(int*)((char*)this + 0xc) + index * 0x10);
}