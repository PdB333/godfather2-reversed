// FUNC_NAME: ObjectManager::releaseReferencedObject
void __thiscall ObjectManager::releaseReferencedObject(int thisPtr, int objPtr)
{
    // Check if the object is flagged as active (bit 4 at offset +0x8a)
    if ((*(byte *)(objPtr + 0x8a) & 0x10) != 0) {
        // Release the object's resources (likely destructor or free)
        FUN_006e7030(objPtr);
        // Clear the active flag
        *(byte *)(objPtr + 0x8a) &= ~0x10;
        // Decrement the reference count / active object count
        // +0x2020: likely m_activeCount or m_refCount
        *(int *)(thisPtr + 0x2020) -= 1;
    }
}