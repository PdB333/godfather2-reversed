// FUNC_NAME: InteractionAreaManager::setZoneRectangle
extern float* getCurrentPosition(); // FUN_00926810 returns x,y via references
extern void* resolveObjectFromHandle(int handle); // FUN_00927910
extern void copyMemoryBlock(void* dest, void* src, int size, int unusedFlag); // FUN_005c4660

// Global pointers to active singleton managers
extern int g_activeMissionManager; // DAT_0112982c
extern int g_activeDialogManager; // DAT_01129890
extern int g_activeCrimeSceneManager; // DAT_01129928
extern int g_activeSomeOtherManager; // DAT_0112e228
extern int g_activeSpecialManager; // DAT_01130020

int __thiscall InteractionAreaManager::setZoneRectangle(int thisPtr, int sourceHandle, int targetHandle,
                                                         float minX, float minY, float maxX, float maxY)
{
    float currentX, currentY;
    getCurrentPosition(&currentX, &currentY);

    // Check if current position is within the rectangle bounds
    if (currentX < minX || currentY < minY || maxX < currentX || maxY < currentY) {
        return 0;
    }

    // Complex visibility/activity checks based on global managers
    if (g_activeMissionManager != 0) {
        void* missionObj = resolveObjectFromHandle(sourceHandle);
        if (missionObj != (void*)g_activeMissionManager) {
            return 0;
        }
        // If mission manager exists and source matches, proceed
    }
    else if (g_activeDialogManager != 0) {
        void* dialogObj = resolveObjectFromHandle(sourceHandle);
        if (dialogObj != (void*)g_activeDialogManager) {
            return 0;
        }
        // If dialog manager exists and source matches, proceed
    }
    else if (g_activeCrimeSceneManager != 0) {
        // Check if source is valid for crime scene
        void* crimeObj = resolveObjectFromHandle(sourceHandle);
        if (crimeObj == 0) {
            return 0;
        }
        int objType = *(int*)(*(int*)(crimeObj + 0x10) + 4); // virtual function? returns a 4-byte code
        if (objType == 0x6D61706D) { // "mpam" ??? (little-endian ASCII)
            // Special case: map marker type?
        }
        else {
            if (*(char*)((int)g_activeSpecialManager + 0x50) != 0) {
                return 0;
            }
            copyMemoryBlock(thisPtr + 0x19C, sourceHandle, 0xC0, 0);
            goto storeTargetAndRect;
        }
    }
    else {
        // Two other managers with offset 0x48 flags
        if (g_activeCrimeSceneManager != 0 && *(char*)(g_activeCrimeSceneManager + 0x48) == 0 &&
            g_activeSpecialManager != 0 && *(char*)(g_activeSpecialManager + 0x48) == 0)
        {
            // If both deactivated, check special manager
            if (g_activeSpecialManager == 0) goto copyAndStore;
            void* specialObj = resolveObjectFromHandle(sourceHandle);
            if (specialObj == 0) return 0;
            int specialType = *(int*)(*(int*)(specialObj + 0x10) + 4);
            if (specialType != 0x6D61706D) {
                if (*(char*)(g_activeSpecialManager + 0x50) != 0) return 0;
                copyMemoryBlock(thisPtr + 0x19C, sourceHandle, 0xC0, 0);
                goto storeTargetAndRect;
            }
        }
    }

    // If we reach here, allocate rectangle with same block copy
    copyMemoryBlock(thisPtr + 0x19C, sourceHandle, 0xC0, 0);

storeTargetAndRect:
    copyMemoryBlock(thisPtr + 0x25C, targetHandle, 8, 0);
    *(float*)(thisPtr + 0x290) = minX;
    *(float*)(thisPtr + 0x294) = minY;
    *(float*)(thisPtr + 0x298) = maxX;
    *(float*)(thisPtr + 0x29C) = maxY;
    return 1;
}