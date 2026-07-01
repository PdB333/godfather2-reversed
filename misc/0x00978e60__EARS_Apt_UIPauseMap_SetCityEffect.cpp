// Xbox PDB: EARS_Apt_UIPauseMap_SetCityEffect
// FUNC_NAME: VFXManager::toggleActiveVFX
void __thiscall VFXManager::toggleActiveVFX(int thisPtr, bool enable)
{
    int *oldNodePtr;
    int resourceObj;
    int effectHandle;
    int *nodePtr;
    char vfxNameBuffer[16];
    struct Matrix4x4 identityMatrix = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };
    // _DAT_00d5780c is treated as 1.0f (floating-point constant)
    
    // If disabled or resource not available, remove any existing effect
    if (!enable || (resourceObj = FUN_00849cf0(*(int *)(thisPtr + 0x13c)), resourceObj == 0)) {
        FUN_004df630(); // cleanup/remove function
        return;
    }

    // Build VFX name from resource fields: "dv_vfx_" + two integers
    FUN_004d3ca0("dv_vfx_", 7, *(int *)(resourceObj + 0x5c), *(int *)(resourceObj + 0x60));

    // The string buffer pointer (local_70) is likely set by FUN_004d3ca0 or a global
    // If null, use a default name
    char *effectName = local_70;
    if (local_70 == 0) {
        effectName = (char *)&DAT_0120546e; // default effect name
    }
    FUN_004eacb0(effectName); // Register/load the effect

    // Create new effect node with given parameters
    FUN_004df420(&effectHandle, vfxNameBuffer, (int *)&identityMatrix, 0x2ff, 4, 0, 0xffffffff, 0);

    // Manage linked list of effect handles at offset +0x100
    nodePtr = (int *)(thisPtr + 0x100);
    if (*nodePtr != 0) {
        *(int *)(*nodePtr + 8) = 0; // clear next pointer of old node
        *nodePtr = 0;
    }
    *nodePtr = effectHandle;
    if (effectHandle != 0) {
        *(int **)(effectHandle + 8) = nodePtr; // link new node to list head
    }

    // If effect name was dynamically allocated, free it via callback
    if (local_70 != 0) {
        ((void (*)(char *))local_64)(local_70);
    }
}