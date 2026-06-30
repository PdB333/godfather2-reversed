// FUNC_NAME: ResourceManager::loadResource
void __thiscall ResourceManager::loadResource(int resourceId) {
    // Call virtual pre-load function at vtable+0x128 (e.g., clearPreviousResource)
    (this->vtable[0x4A])(this); // (*(code **)(*this + 0x128))()

    if (resourceId != 0) {
        MemoryAllocator* allocator = getMemoryAllocator(); // FUN_009c8f80
        AllocInfo allocInfo;
        allocInfo.type = 2;
        allocInfo.size = 0x10;
        allocInfo.flags = 0;

        // Allocate memory for resource (0xa0 bytes)
        int* allocatedBlock = reinterpret_cast<int*>(allocator->allocate(0xa0, &allocInfo));
        int* newResource;
        if (allocatedBlock == nullptr) {
            newResource = nullptr;
        } else {
            // Create resource object from ID
            newResource = reinterpret_cast<int*>(createResource(resourceId)); // FUN_004a4070
        }

        // Store pointer at this+0x130 (offset 0x4c * 4)
        this->resourcePointer = newResource; // param_1[0x4c]

        // If resource was created, initialize it via vtable+0x24
        if (newResource != nullptr) {
            (newResource->vtable[0x09])(newResource); // (**(code **)(*piVar3 + 0x24))()
        }

        // Notify resource loaded (e.g., update dependencies)
        notifyResourceLoaded(); // FUN_0046ed10
    }
}