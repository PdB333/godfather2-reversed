// FUNC_NAME: ResourceManager::submitRequest
undefined4 __thiscall ResourceManager::submitRequest(int this, undefined4 param_2, uint param_3, uint param_4, uint param_5, uint param_6)
{
    uint uVar1;
    uint *puVar2;
    int local_8;
    int local_4;
    
    uVar1 = param_3;
    local_8 = 0;
    // Check if the resource manager is initialized (field at +0x208 indicates state)
    if (*(int *)(this + 0x208) != -1) {
        goto LAB_006fe216;
    }
    // Initialization path: parse param_2 as a handle or identifier
    local_4 = 0;
    FUN_006fd420(&local_4, param_2);
    if (local_4 == 0) {
        // Validate resource availability using various checks
        FUN_006fbfc0(&local_8, &param_3);
        if (local_8 != 0) {
            return 2; // Resource not available, need to wait
        }
        FUN_006fd480(&local_8, &param_3, _DAT_00d60c7c);
        if (((((local_8 == 0) && (FUN_006fc0a0(&local_8, &param_3), local_8 == 0)) &&
             (FUN_006fd480(&local_8, &param_3, DAT_00d5ddec), local_8 == 0)) &&
            (FUN_006fc0f0(&local_8, &param_3), local_8 == 0)) || (uVar1 <= *(uint *)(local_8 + 0x20)))
        {
            goto LAB_006fe216;
        }
    }
    else if (uVar1 <= *(uint *)(local_4 + 0x20)) {
        return 3; // Request exceeds capacity
    }
    // If initialization checks fail, signal a flush/retry
    FUN_006fda60(1);
    return 2;

LAB_006fe216:
    // Already initialized or checks passed
    if (*(int *)(this + 0x74) != 5) {
        // Allocate a new resource slot
        puVar2 = (uint *)FUN_006fc300();
        if (puVar2 == (uint *)0x0) {
            return 0; // Allocation failed
        }
        *puVar2 = *puVar2 & 0x7fffffff; // Clear high bit (likely a flag)
        puVar2[1] = uVar1;              // Set identifier or size
        puVar2[2] = param_4;            // Additional data
        puVar2[3] = param_5;            // Callback or resource pointer
        puVar2[4] = param_6;            // User data
        return 1; // Success
    }
    // Slot count at capacity (5), try to reuse an existing slot
    puVar2 = (uint *)FUN_006fc250();
    if ((puVar2 != (uint *)0x0) && (puVar2[1] < uVar1)) {
        // Invoke cleanup callback if present
        if ((code *)puVar2[3] != (code *)0x0) {
            (*(code *)puVar2[3])(3, puVar2[4]);
        }
        // Reset slot
        puVar2[1] = 0;
        puVar2[2] = 0;
        puVar2[3] = 0;
        puVar2[4] = 0;
        *puVar2 = 0x80000000; // Set high bit to mark as invalid/in-use
        *(int *)(this + 0x74) = *(int *)(this + 0x74) + -1; // Decrement slot count
        *puVar2 = *puVar2 & 0x7fffffff; // Clear high bit
        // Fill in new data
        puVar2[4] = param_6;
        puVar2[1] = uVar1;
        puVar2[2] = param_4;
        puVar2[3] = param_5;
        *(int *)(this + 0x74) = *(int *)(this + 0x74) + 1; // Increment slot count
        return 1;
    }
    return 3; // No available slot
}