// FUNC_NAME: SomeManager::~SomeManager
void __thiscall SomeManager::~SomeManager(void* thisPtr)
{
    // Set vtable to derived class's vtable (0x00d81218)
    *(void**)thisPtr = (void*)0x00d81218;

    // Release two global resources (decrement reference counts or free)
    releaseResource(&DAT_0112fe5c); // +0x?? - some resource pointer
    releaseResource(&DAT_0112fe54); // +0x?? - another resource pointer

    // Call base class destructor (or cleanup function)
    baseClassDestructor();

    // Set vtable to base class's vtable (0x00d81214) after cleanup
    *(void**)thisPtr = (void*)0x00d81214;

    // Mark global initialization flag as false
    DAT_0112a580 = 0;
}