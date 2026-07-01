// FUNC_NAME: ResourceContainer::~ResourceContainer
// Address: 0x0096cb90 - Destructor for a container holding an inner object and a resource pointer.
// Performs global cleanup, releases the primary resource at +0x14, then if an inner object exists at +0x0,
// releases its resource at +0x8 and deletes the inner object.

void __thiscall ResourceContainer::~ResourceContainer(int* this)
{
    int* innerObj = *(int**)this; // offset +0x00, pointer to an owned inner object

    globalCleanup(); // FUN_0096adc0 - static/global decrement or manager shutdown
    releaseResource((void*)this[5]); // offset +0x14, release main resource

    if (innerObj != 0) {
        releaseResource(*(void**)(innerObj + 2)); // offset +0x08, release inner object's resource
        deleteInnerObject(innerObj); // FUN_009c8eb0 delete the inner object itself
    }
}