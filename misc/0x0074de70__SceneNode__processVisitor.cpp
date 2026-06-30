// FUNC_NAME: SceneNode::processVisitor
// Address: 0x0074de70
// This function appears to be a visitor/update method for a scene graph node.
// It handles two node types (identified by RTTI IDs) and manages a linked list of children/contexts.
// The function updates a state variable at +0x84 and may call various engine subsystems.

void __thiscall SceneNode::processVisitor(void *thisPtr, int *visitor)
{
    int *piVar1;
    int iVar2;
    int iVar3;
    int uVar4;
    long long uStack_18; // actually a struct of two ints (x, y) or a float2
    int uStack_10;
    uint uStack_c;
    int uStack_8;
    int *puStack_4;

    // Get the type ID from the visitor's vtable
    iVar3 = (*(code **)visitor[0])(); // virtual call: visitor->getTypeID()
    if (iVar3 == 0x1b2d5c51) // TYPE_1
    {
        iVar3 = FUN_00718480(); // Get some node pointer (maybe current scene node)
        if (iVar3 == 0)
            return;
        piVar1 = visitor + 0x19; // +0x64 (since int is 4 bytes, offset 0x19*4 = 0x64)
        iVar2 = iVar3 + 0x48; // offset 0x48 in node structure
        if (visitor[0x19] == iVar2)
            return; // already linked
        if (visitor[0x19] != 0)
            FUN_004daf90(piVar1); // free/release the link
        *piVar1 = iVar2; // set link to node
        if (iVar2 == 0)
            return;
        visitor[0x1a] = *(int *)(iVar3 + 0x4c); // +0x4c in node
        *(int **)(iVar3 + 0x4c) = piVar1; // link back
        return;
    }
    if (iVar3 != 0x6862a74c) // TYPE_2
        return;

    uVar4 = FUN_0072d0c0(); // Some base value or time
    // Set up stack variables as a temporary struct (maybe a vector or transform)
    uStack_18 = CONCAT44(&LAB_0074c340, (int)thisPtr); // address of some code? Probably a struct constructor
    *(long long *)(visitor + 0x1e) = uStack_18; // store at offset 0x1e*4 = 0x78
    *(unsigned long long *)(visitor + 0x20) = (unsigned long long)uStack_c << 0x20;
    *(unsigned long long *)(visitor + 0x22) = CONCAT44(&LAB_0074c7b0, uStack_8);
    uStack_18 = CONCAT44(&LAB_0074c330, (int)thisPtr);
    *(long long *)(visitor + 0x24) = uStack_18;
    uStack_10 = 0;
    *(unsigned long long *)(visitor + 0x26) = (unsigned long long)uStack_c << 0x20;
    puStack_4 = &LAB_0074c7b0;
    *(unsigned long long *)(visitor + 0x28) = CONCAT44(&LAB_0074c7b0, uStack_8);
    *(int *)((int)thisPtr + 0x84) = uVar4; // set state

    // Check bit 2 of flags at +0xe4
    if ((*(unsigned int *)((int)thisPtr + 0xe4) >> 2 & 1) != 0)
    {
        FUN_0074caa0((int)thisPtr + 0xe8, &uStack_18, DAT_00e51920);
        if ((*(int *)(*(int *)((int)thisPtr + 0x88) + 0x1ed4) == 0x637b907) &&
            (iVar3 = FUN_00721d70(4, &uStack_18, DAT_00e51920 * DAT_00d64704, 0), iVar3 != 0))
        {
            iVar3 = FUN_00471610();
            FUN_0074caa0(iVar3 + 0x30, &uStack_18, DAT_00e51920);
        }
        FUN_0075cd50(&uStack_18);
        *(int *)((int)thisPtr + 0x84) = 0x8f2d9a2e;
        goto LAB_0074e0f9;
    }

    // Not bit 2: check for other conditions
    if ((*(int *)((int)thisPtr + 0xd8) == 0) || (*(int *)((int)thisPtr + 0xe0) == 0))
    {
        if ((*(int *)((int)thisPtr + 0x8c) != 0) && (*(int *)((int)thisPtr + 0x8c) != 0x48))
        {
            if (*(int *)((int)thisPtr + 0x8c) == 0)
                iVar3 = 0;
            else
                iVar3 = *(int *)((int)thisPtr + 0x8c) - 0x48;
            uStack_10 = *(int *)(iVar3 + 0x74);
            // Extract two parts from a 64-bit value (float2?)
            uStack_18._4_4_ = (float)((unsigned long long)*(long long *)(iVar3 + 0x6c) >> 0x20);
            uStack_18._0_4_ = (int)*(long long *)(iVar3 + 0x6c);
            uStack_18 = CONCAT44(uStack_18._4_4_ + DAT_00d5ef50, (int)uStack_18); // add a global float offset
            FUN_0075cd50(&uStack_18);
            if (*(int *)((int)thisPtr + 0x8c) == 0)
                iVar3 = 0;
            else
                iVar3 = *(int *)((int)thisPtr + 0x8c) - 0x48;
            FUN_0072cb10(*(int *)(iVar3 + 0x94) == 2);
            goto LAB_0074e0f9;
        }
        iVar3 = *(int *)((int)thisPtr + 0x94);
        if (iVar3 == 0)
            goto LAB_0074e0f9;
        if (((*(char *)(iVar3 + 0x88) & 1) == 0) || (*(int *)(*(int *)((int)thisPtr + 0x88) + 0x1e70) != 0))
            *(int *)((int)thisPtr + 0x84) = uVar4;
        else
            *(int *)((int)thisPtr + 0x84) = 0x8f2d9a2e;
        uStack_18 = *(long long *)(iVar3 + 0x44);
        uStack_10 = *(int *)(iVar3 + 0x4c);
    }
    else
    {
        long long *puVar5 = (long long *)0x0;
        *(int *)((int)thisPtr + 0x84) = 0x8f2d9a2e;
        if (*(int *)((int)thisPtr + 0xd8) != 0)
            puVar5 = *(long long **)((int)thisPtr + 0xe0);
        uStack_18 = *puVar5;
        uStack_10 = *(int *)(puVar5 + 1);
    }
    uStack_18 = CONCAT44(uStack_18._4_4_ + DAT_00d5ef50, (int)uStack_18);
    FUN_0075cd50(&uStack_18);

LAB_0074e0f9:
    // After processing, check bit 1 of flags and maybe add to list
    if ((((*(unsigned int *)((int)thisPtr + 0xe4) >> 1 & 1) == 0) &&
         (*(unsigned int *)((int)thisPtr + 0xb0) < DAT_00e51934)) &&
        (iVar3 = FUN_00718480(), iVar3 != 0))
    {
        FUN_007607b0(iVar3);
        visitor[0x41] = (int)thisPtr + 0xb4; // store this node's ref in visitor list
    }
    *(int *)((int)thisPtr + 0xb0) += 1; // increment frame counter

    if ((*(unsigned int *)((int)thisPtr + 0xe4) >> 1 & 1) != 0)
        *(int *)((int)thisPtr + 0x84) = uVar4; // reset state

    if (*(int *)((int)thisPtr + 0x84) == -0x70d265d2) // 0x8f2d9a2e as signed
    {
        FUN_0072cb10(1); // set a flag (possibly "hasAnimation")
    }
    return;
}