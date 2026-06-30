// FUNC_NAME: RefCountedPtrAssign
// Function address: 0x00657a10
// Reference-counted pointer assignment: decrements refcount of old pointer,
// calls destructor if zero, then assigns new pointer and increments its refcount.
void RefCountedPtrAssign(int** ppOld, int* pNew) {
    int* oldPtr = *ppOld; // previous pointer value
    if (oldPtr != nullptr) {
        int* refCountPtr = oldPtr + 2; // refcount at offset +8 (assuming 4-byte ints)
        *refCountPtr = *refCountPtr - 1;
        if (*refCountPtr == 0) {
            // Call destructor via vtable (third entry at offset 8)
            (**(void (__thiscall**)(int*))(*(int*)oldPtr + 8))();
        }
    }
    *ppOld = pNew; // assign new pointer
    if (pNew != nullptr) {
        int* newRefCount = (int*)((char*)pNew + 8); // refcount at offset +8
        *newRefCount = *newRefCount + 1;
    }
}