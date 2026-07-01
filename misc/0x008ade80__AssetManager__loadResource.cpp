// FUNC_NAME: AssetManager::loadResource
int __thiscall AssetManager::loadResource(void* thisPtr, void* worldState, const char* resourceId, bool doSomething, void* param5, void* param6, bool useCustomTransform)
{
    int resourceHandle = 0;
    if (worldState != 0) {
        int resourceInfoPtr = *(int*)((char*)worldState + 0x1ef8); // +0x1ef8: resource definition pointer
        int cacheEntry = thisPtr->findInCache(&resourceInfoPtr); // FUN_006a7890 via this
        if (cacheEntry != 0) {
            return *(int*)(cacheEntry + 4); // +4: cached resource handle
        }
        if (!useCustomTransform) {
            resourceHandle = thisPtr->createResourceStandard(resourceId, worldState, 0, 5, 0, 1, 1, 0, 2, 0, 0, 0, 0); // FUN_0094cc00
        } else {
            // Build a transform from the current camera/player object
            int transformArray[4]; // local_50 etc., each is 16 bytes? Actually 4 quads of 4 ints? Here we have 16 fields but repeating pattern.
            transformArray[0] = 0; // local_50
            transformArray[1] = 0;
            transformArray[2] = 0;
            transformArray[3] = 0;
            transformArray[4] = 0; // local_40
            transformArray[5] = 0; // uStack_3c
            transformArray[6] = 0;
            transformArray[7] = 0;
            transformArray[8] = 0; // local_30
            transformArray[9] = 0;
            transformArray[10] = 0; // uStack_28
            transformArray[11] = 0;
            transformArray[12] = 0; // local_20
            transformArray[13] = 0;
            transformArray[14] = 0;
            transformArray[15] = 0; // uStack_14

            int gameInstance = this->getGameInstance(); // FUN_00471610
            // Copy first three components from gameInstance+0x30 (likely a position)
            transformArray[12] = *(int*)(gameInstance + 0x30);
            transformArray[13] = *(int*)(gameInstance + 0x34);
            transformArray[14] = *(int*)(gameInstance + 0x38);
            // The 15th component remains 0 (w?)
            // Note: There was globals _DAT_00d5780c used for some components; those are likely zero or identity quaternion.
            resourceHandle = this->createResourceWithTransform(resourceId, transformArray, 0, 5, 0, 1, 2, 0, 0, 0, 0, 0); // FUN_0094ca20
        }
        if (resourceHandle != 0) {
            if (doSomething) {
                this->setExtraData(resourceHandle, param6, param5); // FUN_0094ac40
            }
            int cacheEntry = this->storeInCache(&resourceInfoPtr); // FUN_006a78f0
            *(int*)(cacheEntry + 4) = resourceHandle;
            // Virtual call at vtable+0xf0: notify resource loaded
            (*(void(__thiscall**)(void*, int))(*((int*)thisPtr) + 0x3c))(thisPtr, resourceHandle); // 0xf0 is at offset from vtable start (0x3c in int pointer steps)
        }
    }
    return resourceHandle;
}