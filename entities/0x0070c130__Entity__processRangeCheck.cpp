// FUNC_NAME: Entity::processRangeCheck
void __thiscall Entity::processRangeCheck(int *param_2, char param_3)
{
    float rangeValue;
    // If param_3 is false (0), compute range from param_2 using FUN_0070ab40 (likely getDistanceTo)
    if (param_3 == 0) {
        rangeValue = FUN_0070ab40(param_2);  // returns float, maybe distance to target
    } else {
        // Use stored range value at this+0x2e0
        rangeValue = *(float *)(this + 0x2e0);
        // Set flag bit 2 at this+0x39e (ushort) – likely "range updated" or "manual override"
        *(unsigned short *)(this + 0x39e) |= 4;
    }

    // Check global range threshold (DAT_00d5ef84) and valid param_2
    if (DAT_00d5ef84 < rangeValue && param_2 != nullptr) {
        // Call virtual function at param_2 vtable offset 0x78 (probably "isActive" or "isUsable")
        char isUsable = (*(char (__thiscall **)(int *))(*(int *)param_2 + 0x78))(param_2);
        if (isUsable != 0) {
            // Check some state at this+0x2d4 (maybe action state), must be non-zero and not 0x48
            if (*(int *)(this + 0x2d4) != 0 && *(int *)(this + 0x2d4) != 0x48) {
                // Call helper functions, possibly preparing a spawn/creation
                FUN_0084dd20();  // Start transaction?
                FUN_0044b210(this);  // Likely getOwner or getParent
                
                int tempVar;
                if (*(int *)(this + 0x2d4) == 0) {
                    tempVar = 0;
                } else {
                    tempVar = *(int *)(this + 0x2d4) - 0x48;  // Subtract offset
                }
                FUN_0044b210(tempVar);
                
                // Get some global structure (maybe camera or transform)
                int global1 = FUN_00471610();
                uStack_6c = *(unsigned long long *)(global1 + 0x30);
                uStack_64 = *(unsigned int *)(global1 + 0x38);
                
                int global2 = FUN_00471610();
                uStack_78 = *(unsigned long long *)(global2 + 0x30);
                uStack_70 = *(unsigned int *)(global2 + 0x38);
                
                // Determine action type depending on param_3 and a flag
                if (param_3 == 0 || *(char *)(this + 0x39c) != 0) {
                    // Use stored target info from this+0x304 (maybe timer or ID)
                    uStack_5c = *(unsigned int *)(this + 0x304);
                } else {
                    // Alternative branch: set flag BIT5 (0x20) and BIT3 (0x08) on uStack_48
                    uStack_48 |= 0x28;
                    uStack_5c = 1;  // Action type 1?
                    
                    int target = FUN_006b1c70(param_2, 0x55859efa);  // Find something by hash
                    if (target != 0) {
                        uStack_50 = *(unsigned int *)(target + 0x674) >> 2;  // Extract data
                    }
                }
                uStack_54 = 3;  // Some constant (maybe priority or count)
                fStack_60 = rangeValue;
                uStack_4c = DAT_01205224;  // Global ID or pointer
                
                // Format a string/ID for param_2+0x0f (offset 15*4 = 60 bytes into param_2)
                FUN_00408bb0(&DAT_0112dd94, param_2 + 0xf, auStack_8c, 0);
                
                char valid = FUN_00481660();  // Some validation
                if (valid != 0) {
                    FUN_0084d330();    // Begin spawn?
                    FUN_0084dda0(auStack_8c);  // Pass data
                    FUN_0070b6a0(auStack_44);  // Process
                    FUN_004a8ec0(param_2 + 0x16);  // Another offset (22*4)
                    FUN_0084e1c0();   // Finalize
                }
                FUN_0070aaf0();  // Cleanup
            }
        }
    }
}