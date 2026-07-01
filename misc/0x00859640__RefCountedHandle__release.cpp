// FUNC_NAME: RefCountedHandle::release
void __fastcall RefCountedHandle::release(int* this)
{
    // +0x00: pointer to the managed object
    int* pObject = reinterpret_cast<int*>(this[0]);
    if (pObject != 0) {
        // Release child objects at byte offsets +0x08 and +0x0C of the managed object
        int* child1 = *reinterpret_cast<int**>(reinterpret_cast<char*>(pObject) + 8);
        if (child1 != 0) {
            releaseRefCountedObject(child1);
        }
        int* child2 = *reinterpret_cast<int**>(reinterpret_cast<char*>(pObject) + 12);
        if (child2 != 0) {
            releaseRefCountedObject(child2);
        }
        // Call virtual destructor (vtable entry at offset 4) on the managed object
        // this[3] stores a pointer to the object's vtable pointer (i.e., &(pObject->vtable))
        int* vtablePtr = *reinterpret_cast<int**>(this[3]);
        typedef void (__thiscall *DestroyFunc)(void*, int);
        DestroyFunc destroy = reinterpret_cast<DestroyFunc>(vtablePtr[1]); // second vtable entry
        destroy(pObject, 0);
        // Decrement reference count
        this[1] = this[1] - 1;
    }
    // Clear the object pointer
    this[0] = 0;
}