// FUNC_NAME: RefCountedPtr::assign
// Function address: 0x004e0790
// Role: Helper method for intrusive reference-counted smart pointer assignment.
// Decrements ref count on current held object, deletes if zero, then assigns new object and increments its ref count.

void __thiscall RefCountedPtr::assign(int* thisPtr, int* newObject)
{
    int* currentObject = (int*)*thisPtr;
    if (currentObject != nullptr) {
        int* refCountPtr = currentObject + 1; // +0x04: reference count
        *refCountPtr = *refCountPtr - 1;
        if (currentObject[1] == 0) { // ref count became zero
            void (*destructor)(void) = (void (*)(void))(* (int*)(*currentObject + 4)); // vtable+4: destructor
            destructor();
        }
        *thisPtr = 0;
    }
    *thisPtr = (int)newObject;
    if (newObject != nullptr) {
        int* newRefCount = newObject + 1; // +0x04: reference count
        *newRefCount = *newRefCount + 1;
    }
}