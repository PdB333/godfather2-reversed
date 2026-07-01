// FUNC_NAME: SomeClass::getOrCreateSubObject
int __thiscall SomeClass::getOrCreateSubObject(void* thisPtr)
{
    // +0x7c: pointer to allocator/manager for sub-object
    // +0x9c: sub-object storage (lazily initialized)
    // +0xa0: flag indicating whether sub-object is initialized (0 = not initialized)
    if (*(int*)((char*)thisPtr + 0xa0) == 0) {
        constructSubObject(*(void**)((char*)thisPtr + 0x7c), (void*)((char*)thisPtr + 0x9c));
    }
    return (int)((char*)thisPtr + 0x9c);
}