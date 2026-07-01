// FUNC_NAME: SomeClass::~SomeClass
int __thiscall SomeClass::~SomeClass(void* this, byte flags)
{
    // Call base class destructor
    baseDestructor();

    // Release resource at offset +0x6c
    releaseResource(*(undefined4*)((int)this + 0x6c));

    // Check member at +0x58 (likely a child object pointer)
    int* childObject = *(int**)((int)this + 0x58);
    if (childObject != 0) {
        // Release its sub-resource at +8
        releaseResource(*(undefined4*)(childObject + 2)); // +8 bytes
        // Destroy the child object itself
        destroyObject(childObject);
    }

    // Release resource at offset +0x4c
    if (*(int*)((int)this + 0x4c) != 0) {
        releaseResource(*(int*)((int)this + 0x4c));
    }

    // Perform global cleanup
    globalCleanup();

    // If the delete flag (bit 0) is set, call operator delete
    if ((flags & 1) != 0) {
        operatorDelete(this);
    }

    return (int)this;
}