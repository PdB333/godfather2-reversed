// FUNC_NAME: SimObjectManager::updateActiveObjects
void __thiscall SimObjectManager::updateActiveObjects(void* thisPtr, bool bUpdate)
{
    // this+0x68 = number of active objects in pool
    uint32_t activeCount = *(uint32_t*)((uint8_t*)thisPtr + 0x68);
    if (activeCount != 0)
    {
        // this+0x64 (100) = pointer to array of 8-byte slot entries
        // Each slot: first 4 bytes = pointer to node inside an object (offset 0x48 from object base)
        uint8_t* slotBase = *(uint8_t**)((uint8_t*)thisPtr + 100); // +0x64
        for (uint32_t i = 0; i < activeCount; i++)
        {
            uint8_t* nodePtr = *(uint8_t**)(slotBase + i * 8); // pointer to embedded node
            void* objPtr = nullptr;
            if (nodePtr != nullptr) {
                // Node is stored at offset 0x48 within the actual object
                objPtr = (void*)(nodePtr - 0x48);
            }
            // If bUpdate is true and object exists, call the update/cleanup routine
            if (bUpdate && objPtr != nullptr)
            {
                // FUN_007890a0 performs the actual per-object update
                updateObject(objPtr);
            }
        }
    }
}