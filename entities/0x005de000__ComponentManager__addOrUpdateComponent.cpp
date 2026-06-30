// FUNC_NAME: ComponentManager::addOrUpdateComponent
uint ComponentManager::addOrUpdateComponent(void* param_2) // param_2: input data struct
{
    uint* freeNode;
    uint temp;
    int iVar3;
    int* piVar4;

    iVar3 = gComponentPool; // DAT_01223508
    temp = 0;
    // Search for existing component matching key (type/subtype)
    if (*(uint*)(this + 0x274) != 0) {
        piVar4 = *(int**)(this + 0x270);
        do {
            if (((*piVar4 != 0) &&
                 (*(int*)(*piVar4 + 0x58) == *(int*)(param_2 + 0xc))) &&
                 (*(int*)(*piVar4 + 0x54) == *(int*)(param_2 + 8))) {
                // Update existing component
                *(undefined4*)(*(int*)(*(int*)(this + 0x270) + temp * 4) + 100) =
                     *(undefined4*)(param_2 + 0x14);
                *(undefined4*)(*(int*)(*(int*)(this + 0x270) + temp * 4) + 0x60) =
                     *(undefined4*)(param_2 + 0x14);
                // Return success with index in high byte
                return CONCAT31((int3)(temp >> 8), 1);
            }
            temp = temp + 1;
            piVar4 = piVar4 + 1;
        } while (temp < *(uint*)(this + 0x274));
    }
    // Check pool availability
    if ((*(int*)(gComponentPool + 0x44) == 0) &&
         ((*(int*)(gComponentPool + 0x40) == 0 ||
          ((*(byte*)(gComponentPool + 0x34) & 1) == 0)))) {
        temp = FUN_004de190(); // Allocate new pool block
    }
    freeNode = *(uint**)(iVar3 + 0x44);
    if (freeNode != (uint*)0x0) {
        // Dequeue from free list
        temp = *freeNode;
        *(int*)(iVar3 + 0x20) = *(int*)(iVar3 + 0x20) + 1; // increment allocated count
        *(int*)(iVar3 + 0x1c) = *(int*)(iVar3 + 0x1c) + -1; // decrement free count
        *(uint*)(iVar3 + 0x44) = temp; // update free list head
        if (freeNode != (uint*)0x0) {
            // Set debug sentinel values
            freeNode[4] = 0xbadbadba;
            freeNode[5] = 0xbeefbeef;
            freeNode[6] = 0xeac15a55;
            freeNode[7] = 0x91100911;
            FUN_005dd030(); // Initialize node (constructor)
            // Copy input data into node (offsets relative to node as pointer to uint)
            freeNode[0x14] = *(uint*)(param_2 + 4);  // +0x50
            freeNode[0x15] = *(uint*)(param_2 + 8);  // +0x54 -> key field used for matching
            temp = *(uint*)(param_2 + 0xc);            // +0x0C
            freeNode[0x16] = temp;                     // +0x58 -> key field used for matching
            freeNode[0x17] = *(uint*)(param_2 + 0x10); // +0x5C
            freeNode[0x19] = *(uint*)(param_2 + 0x14); // +0x64 -> value field
            freeNode[0x18] = *(uint*)(param_2 + 0x14); // +0x60 -> also value field (duplicate)
            // Add to component list if space exists
            if (*(uint*)(this + 0x274) < 0x14) {
                iVar3 = *(int*)(this + 0x278);
                if (*(int*)(this + 0x274) == iVar3) {
                    // Reallocate list if full
                    if (iVar3 == 0) {
                        iVar3 = 1;
                    } else {
                        iVar3 = iVar3 * 2;
                    }
                    FUN_005e1c00(iVar3); // Grow list
                }
                piVar4 = (int*)(*(int*)(this + 0x270) + *(int*)(this + 0x274) * 4);
                iVar3 = *(int*)(this + 0x274) + 1;
                *(int*)(this + 0x274) = iVar3;
                if (piVar4 != (int*)0x0) {
                    *piVar4 = (int)freeNode;
                }
                return CONCAT31((int3)((uint)iVar3 >> 8), 1);
            }
        }
    }
    // Return failure (high byte zero)
    return temp & 0xffffff00;
}