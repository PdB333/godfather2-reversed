// FUNC_NAME: RefCountedPtr::operator=
int* __thiscall RefCountedPtr::operator=(int* thisPtr, int* otherPtr)
{
    int* objectPtr;
    int refCount;

    // Release current object if any
    if (*thisPtr != 0) {
        objectPtr = (int*)(*thisPtr + 4); // +0x04: reference count
        *objectPtr = *objectPtr - 1;
        if (((int*)*thisPtr)[1] == 0) { // ref count became zero
            // Call destructor via vtable[1] (offset 4 from vtable)
            (**(code**)(*(int*)*thisPtr + 4))();
        }
        *thisPtr = 0;
    }

    // Assign new object and increment its reference count
    int newObj = *otherPtr;
    *thisPtr = newObj;
    if (newObj != 0) {
        *(int*)(newObj + 4) = *(int*)(newObj + 4) + 1; // +0x04: reference count
    }

    return thisPtr;
}