// FUNC_NAME: ResourceContainer::releaseAllResources
void __thiscall ResourceContainer::releaseAllResources(void)
{
    // +0x128: byte flag indicating whether resources have been released
    *(uint8 *)(this + 0x128) = 1;
    
    // +0x14c: count of resources in the array
    uint count = *(uint32 *)(this + 0x14c);
    if (count != 0) {
        // +0x12c: start of the resource array (each element is a 4-byte handle/pointer)
        uint32 *resourceArray = (uint32 *)(this + 0x12c);
        for (uint32 i = 0; i < count; i++) {
            // FUN_009c8eb0: releases or destroys the resource
            FUN_009c8eb0(resourceArray[i]);
        }
        // Reset count after release
        *(uint32 *)(this + 0x14c) = 0;
    }
}