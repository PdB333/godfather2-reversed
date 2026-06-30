// FUNC_NAME: ResourceManager::storeResource
void __fastcall ResourceManager::storeResource(int thisPtr)
{
    int resourcePtr;
    int tlsBase;
    
    resourcePtr = *(int *)(*(int *)(thisPtr + 4) + 0x20); // deref thisPtr+4 => class descriptor, then +0x20 => resource pointer
    if (resourcePtr != 0) {
        *(int *)(resourcePtr + 4) = *(int *)(resourcePtr + 4) + 1; // increment reference count at +4
    }
    resourcePtr = FUN_004fc3d0(resourcePtr); // likely get or duplicate resource
    if (resourcePtr != 0) {
        // write from resource+8 into global array indexed by thisPtr+0x40
        // accessing thread-local storage via FS segment
        tlsBase = *(int *)(__readfsdword(0x2c)); // get TLS base
        *(int *)(*(int *)(tlsBase + 8) + 0x84 + *(int *)(thisPtr + 0x40)) = *(int *)(resourcePtr + 8);
    }
}