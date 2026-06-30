// FUNC_NAME: GameObjectManager::getObjectFromIndex
int __thiscall GameObjectManager::getObjectFromIndex(int index)
{
    // +0x1ac: pointer array of 8-byte entries (each entry likely a pointer to an object's member field)
    int childPtr = *(int*)((char*)this + 0x1ac + index * 8);
    if (childPtr != 0)
    {
        // Subtract 0x48 to get base of containing object (header size or offset to parent)
        return childPtr - 0x48;
    }
    return 0;
}