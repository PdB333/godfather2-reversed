// FUNC_NAME: ReferenceCountedObject::release
void __fastcall ReferenceCountedObject::release(int thisPtr)
{
    // Call release on the sub-object stored at offset +0x8c
    // This likely frees or decrements the reference count of that object
    releaseInternal(*(void**)(thisPtr + 0x8c));

    // Decrement the reference count/slot usage at offset +0x174
    *(int*)(thisPtr + 0x174) -= 1;
}