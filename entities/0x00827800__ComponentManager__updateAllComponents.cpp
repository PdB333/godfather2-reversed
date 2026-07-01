// FUNC_NAME: ComponentManager::updateAllComponents
void __thiscall ComponentManager::updateAllComponents(int this)
{
    // This function iterates over a list of component entries stored in the manager.
    // Manager structure offset:
    // +0x04: Pointer to an array of component entries (each entry is 8 bytes; first 4 bytes = component pointer, second 4 bytes = unknown/unused here)
    // +0x08: Number of entries (uint)
    uint numEntries = *(uint *)(this + 8);
    if (numEntries != 0) {
        for (uint i = 0; i < numEntries; i++) {
            // Each entry occupies 8 bytes, so index by i*2 in pointer array (stride = 8)
            void **entryArray = *(void ***)(this + 4);
            void *component = entryArray[i * 2];
            // Call the 4th virtual method (vtable offset 0xC) on the component.
            // This is likely a virtual update/process function.
            (*(void (**)(void))((*(int *)component) + 0xC))();
        }
    }
}