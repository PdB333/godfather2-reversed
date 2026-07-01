// FUNC_NAME: SomeManager::processItemList
void __thiscall SomeManager::processItemList(int *thisPtr)
{
    undefined4 *puVar1;
    char cVar2;
    int *unaff_EBX;
    float fVar3;
    int local_60;
    uint loopCounter;
    undefined8 local_58;
    int local_50;
    undefined4 uStack_4c;
    undefined4 uStack_48;
    int iStack_44;
    undefined4 local_40;
    undefined4 local_3c;
    int local_38;
    undefined4 local_34;
    undefined4 local_30;
    undefined4 local_2c;
    int local_28[3];
    undefined4 local_1c;
    undefined4 local_18;
    undefined4 local_14;

    // Check if the list is valid: thisPtr[0] (flag), thisPtr[1] (manager), thisPtr[2] (count)
    if (((*thisPtr != 0) && (thisPtr[1] != 0)) && (thisPtr[2] != 0)) {
        loopCounter = 0;
        do {
            // Read position data from thisPtr[6..8]
            local_50 = thisPtr[8];
            local_58 = *(undefined8 *)(thisPtr + 6); // 64-bit value from thisPtr[6] and thisPtr[7]
            FUN_008523a0(&local_58); // Convert or normalize the 64-bit value

            local_30 = (undefined4)local_58;
            local_2c = local_58._4_4_;
            local_28[0] = local_50;
            local_28[1] = 0;
            FUN_0056afa0(&local_30, &local_30); // Transform the vector

            // Read container data from thisPtr[5]
            puVar1 = (undefined4 *)thisPtr[5];
            local_1c = puVar1[1];
            local_18 = puVar1[2];
            local_28[2] = *puVar1;

            // Build a 3D vector (local_40, local_3c, local_38) from transformed data
            local_40 = local_30;
            local_3c = local_2c;
            local_14 = 0;
            local_38 = local_28[0];
            local_34 = 0;
            local_60 = 0;

            // Try to get a component from the manager (thisPtr[1]) using hash 0xf26fb813
            cVar2 = (**(code **)(*(int *)thisPtr[1] + 0x10))(0xf26fb813, &local_60);
            if (cVar2 == '\0') {
                // First hash failed, try another hash 0xa7039c8
                unaff_EBX = (int *)0x0;
                cVar2 = (**(code **)(*(int *)thisPtr[1] + 0x10))(0xa7039c8, &stack0xffffff98);
                if ((cVar2 != '\0') && (local_60 != 0)) {
                    // Apply force/position using data from the component
                    FUN_00853be0(&local_40, *(undefined4 *)(local_60 + 0x1f0), local_28 + 2,
                                 *(undefined4 *)(local_60 + 0x1ec));
                    uStack_4c = local_40;
                    uStack_48 = local_3c;
                    iStack_44 = local_38;
                    FUN_008bb3b0(thisPtr[5], &uStack_4c); // Add to container
                }
            }
            else {
                // First hash succeeded, use the component pointed by unaff_EBX
                fVar3 = (float)(**(code **)(*unaff_EBX + 0x1a0))(); // Get some float (e.g., speed)
                fVar3 = (float)(**(code **)(*unaff_EBX + 0x1a4))(local_28, fVar3); // Modify vector
                FUN_00853be0(&uStack_48, fVar3); // Apply force/position
                (**(code **)(*unaff_EBX + 0x198))(local_28, &uStack_48, 1); // Finalize
            }
            loopCounter = loopCounter + 1;
        } while (loopCounter < (uint)thisPtr[2]);
    }
    return;
}