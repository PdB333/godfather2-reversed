// FUNC_NAME: ActiveListManager::processCurrentEntry
void __thiscall ActiveListManager::processCurrentEntry(void* thisPtr, uint32 param_2)
{
    uint32 currentIndex = *(uint32*)((uint8*)thisPtr + 0xA0);
    uint32 entryCount = *(uint32*)((uint8*)thisPtr + 0x68);

    if (currentIndex != 0xFFFFFFFF && currentIndex < entryCount)
    {
        // Array of entity/handle IDs at +0x64
        uint32* pIdArray = *(uint32**)((uint8*)thisPtr + 0x64);
        uint32 objectId = pIdArray[currentIndex];

        // Resolve the object pointer from ID (likely via a global object manager)
        void* pObject = FUN_006b0ee0(objectId);
        if (pObject != nullptr)
        {
            // Read argument from object at +0x48, and use +0x10 as a data buffer
            uint32 arg1 = *(uint32*)((uint8*)pObject + 0x48);
            void* dataBuffer = (uint8*)pObject + 0x10;
            FUN_0097b440(arg1, dataBuffer, param_2, DAT_00d5e288);
        }
    }
}