// FUNC_NAME: ResourceManager::activatePendingLoads
// Function address: 0x006b4ca0
// Role: On first activation, load any pending resources that haven't been loaded yet.

void __thiscall ResourceManager::activatePendingLoads(int this) {
    // Increment activation counter at offset +0x78
    *(int *)(this + 0x78) = *(int *)(this + 0x78) + 1;
    
    // On first activation, process any remaining work
    if (*(int *)(this + 0x78) == 1) {
        int remaining = *(int *)(this + 0x68) - *(int *)(this + 0xac);
        while (remaining > 0) {
            FUN_006b4b50();  // Processes next pending unit (e.g., load one resource)
            remaining--;
        }
    }
}