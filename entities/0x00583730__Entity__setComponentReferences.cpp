// FUNC_NAME: Entity::setComponentReferences
void __fastcall Entity::setComponentReferences(Entity *this, int key, MappingContainer *mapping)
{
    MappingData *mappingData;
    int (*triplets)[3];
    int tripletCount;
    int *currentTriplet;

    // Guard: 'this' must not be null
    if (this == nullptr)
        return;

    // Access the mapping data structure at offset +0x70 in the mapping container
    mappingData = *(MappingData **)((char *)mapping + 0x70);
    tripletCount = mappingData->count;                     // +0x4c
    triplets = (int (*)[3])((char *)mappingData + 0x50);   // +0x50

    // Search for a triplet whose first element matches the key
    for (currentTriplet = &(*triplets)[0]; tripletCount > 0; tripletCount--, currentTriplet += 3)
    {
        if (currentTriplet[0] == key)
        {
            // Save the three reference pointers from 'this'
            int savedRef0 = *(int *)((char *)this + 0x3c);
            int savedRef1 = *(int *)((char *)this + 0x40);
            int savedRef2 = *(int *)((char *)this + 0x44);

            // Clear them temporarily, then get the manager
            *(int *)((char *)this + 0x3c) = 0;
            *(int *)((char *)this + 0x40) = 0;
            *(int *)((char *)this + 0x44) = 0;
            int manager = FUN_005861c0();   // Returns a global manager (e.g., ComponentManager)

            // Restore the references (they will be swapped later)
            *(int *)((char *)this + 0x3c) = savedRef0;
            *(int *)((char *)this + 0x40) = savedRef1;
            *(int *)((char *)this + 0x44) = savedRef2;

            // Process savedRef0: increment its ref count, then swap with manager's slot
            if (savedRef0 != 0)
                (*(unsigned char *)(savedRef0 + 9))++;

            int *oldSlot = *(int **)((char *)manager + 0x3c);
            if (oldSlot != nullptr)
            {
                (*(unsigned char *)((char *)oldSlot + 9))--;
                if ((*(char *)((char *)oldSlot + 8) == 0) && (*(unsigned char *)((char *)oldSlot + 9) == 0))
                {
                    // Remove from free list (using global head DAT_01205588)
                    int *prev = *oldSlot;
                    int *next = oldSlot[1];
                    if (prev != 0)
                        *(int **)(prev + 4) = next;
                    if (next == nullptr)
                    {
                        // Update tail pointers (LIST_TAIL at various offsets)
                        *(int **)(DAT_01205588 + 8) = *(int **)(DAT_01205588 + 4);  // tail = old tail
                        *(int **)(DAT_01205588 + 4) = prev;                          // new last node
                        if (prev == 0)
                            *(int **)(DAT_01205588 + 8) = *(int **)(DAT_01205588 + 0xc); // also update front
                    }
                    else
                    {
                        *next = prev;
                    }
                }
            }
            *(int *)((char *)manager + 0x3c) = savedRef0;   // Swap: manager now points to savedRef0

            // Repeat for savedRef1 (offset 0x40, global head DAT_0120558c)
            if (savedRef1 != 0)
                (*(unsigned char *)(savedRef1 + 9))++;

            oldSlot = *(int **)((char *)manager + 0x40);
            if (oldSlot != nullptr)
            {
                (*(unsigned char *)((char *)oldSlot + 9))--;
                if ((*(char *)((char *)oldSlot + 8) == 0) && (*(unsigned char *)((char *)oldSlot + 9) == 0))
                {
                    int *prev = *oldSlot;
                    int *next = oldSlot[1];
                    if (prev != 0)
                        *(int **)(prev + 4) = next;
                    if (next == nullptr)
                    {
                        *(int **)(DAT_0120558c + 8) = *(int **)(DAT_0120558c + 4);
                        *(int **)(DAT_0120558c + 4) = prev;
                        if (prev == 0)
                            *(int **)(DAT_0120558c + 8) = *(int **)(DAT_0120558c + 0xc);
                    }
                    else
                    {
                        *next = prev;
                    }
                }
            }
            *(int *)((char *)manager + 0x40) = savedRef1;

            // Repeat for savedRef2 (offset 0x44, global head DAT_0120555c)
            if (savedRef2 != 0)
                (*(unsigned char *)(savedRef2 + 9))++;

            oldSlot = *(int **)((char *)manager + 0x44);
            if (oldSlot != nullptr)
            {
                (*(unsigned char *)((char *)oldSlot + 9))--;
                if ((*(char *)((char *)oldSlot + 8) == 0) && (*(unsigned char *)((char *)oldSlot + 9) == 0))
                {
                    int *prev = *oldSlot;
                    int *next = oldSlot[1];
                    if (prev != 0)
                        *(int **)(prev + 4) = next;
                    if (next == nullptr)
                    {
                        *(int **)(DAT_0120555c + 8) = *(int **)(DAT_0120555c + 4);
                        *(int **)(DAT_0120555c + 4) = prev;
                        if (prev == 0)
                            *(int **)(DAT_0120555c + 8) = *(int **)(DAT_0120555c + 0xc);
                    }
                    else
                    {
                        *next = prev;
                    }
                }
            }
            *(int *)((char *)manager + 0x44) = savedRef2;
            return;
        }
    }

    // If no matching triplet found, handle four additional reference slots (0x34,0x38,0x3c,0x40)
    int manager2 = FUN_0056fdd0();   // Different manager for the second set

    // Process slot at offset 0x34
    int savedRef3 = *(int *)((char *)this + 0x34);
    if (savedRef3 != 0)
        (*(unsigned char *)(savedRef3 + 9))++;
    int *oldSlot = *(int **)((char *)manager2 + 0x34);
    if (oldSlot != nullptr)
    {
        (*(unsigned char *)((char *)oldSlot + 9))--;
        if ((*(char *)((char *)oldSlot + 8) == 0) && (*(unsigned char *)((char *)oldSlot + 9) == 0))
        {
            int *prev = *oldSlot;
            int *next = oldSlot[1];
            if (prev != 0)
                *(int **)(prev + 4) = next;
            if (next == nullptr)
            {
                *(int **)(DAT_01205564 + 8) = *(int **)(DAT_01205564 + 4);
                *(int **)(DAT_01205564 + 4) = prev;
                if (prev == 0)
                    *(int **)(DAT_01205564 + 8) = *(int **)(DAT_01205564 + 0xc);
            }
            else
            {
                *next = prev;
            }
        }
    }
    *(int *)((char *)manager2 + 0x34) = savedRef3;

    // Process slot at offset 0x38
    int savedRef4 = *(int *)((char *)this + 0x38);
    if (savedRef4 != 0)
        (*(unsigned char *)(savedRef4 + 9))++;
    oldSlot = *(int **)((char *)manager2 + 0x38);
    if (oldSlot != nullptr)
    {
        (*(unsigned char *)((char *)oldSlot + 9))--;
        if ((*(char *)((char *)oldSlot + 8) == 0) && (*(unsigned char *)((char *)oldSlot + 9) == 0))
        {
            int *prev = *oldSlot;
            int *next = oldSlot[1];
            if (prev != 0)
                *(int **)(prev + 4) = next;
            if (next == nullptr)
            {
                *(int **)(DAT_01205560 + 8) = *(int **)(DAT_01205560 + 4);
                *(int **)(DAT_01205560 + 4) = prev;
                if (prev == 0)
                    *(int **)(DAT_01205560 + 8) = *(int **)(DAT_01205560 + 0xc);
            }
            else
            {
                *next = prev;
            }
        }
    }
    *(int *)((char *)manager2 + 0x38) = savedRef4;

    // Process slot at offset 0x3c
    int savedRef5 = *(int *)((char *)this + 0x3c);
    if (savedRef5 != 0)
        (*(unsigned char *)(savedRef5 + 9))++;
    oldSlot = *(int **)((char *)manager2 + 0x3c);
    if (oldSlot != nullptr)
    {
        (*(unsigned char *)((char *)oldSlot + 9))--;
        if ((*(char *)((char *)oldSlot + 8) == 0) && (*(unsigned char *)((char *)oldSlot + 9) == 0))
        {
            int *prev = *oldSlot;
            int *next = oldSlot[1];
            if (prev != 0)
                *(int **)(prev + 4) = next;
            if (next == nullptr)
            {
                *(int **)(DAT_01205588 + 8) = *(int **)(DAT_01205588 + 4);
                *(int **)(DAT_01205588 + 4) = prev;
                if (prev == 0)
                    *(int **)(DAT_01205588 + 8) = *(int **)(DAT_01205588 + 0xc);
            }
            else
            {
                *next = prev;
            }
        }
    }
    *(int *)((char *)manager2 + 0x3c) = savedRef5;

    // Process slot at offset 0x40
    int savedRef6 = *(int *)((char *)this + 0x40);
    if (savedRef6 != 0)
        (*(unsigned char *)(savedRef6 + 9))++;
    oldSlot = *(int **)((char *)manager2 + 0x40);
    if (oldSlot != nullptr)
    {
        (*(unsigned char *)((char *)oldSlot + 9))--;
        if ((*(char *)((char *)oldSlot + 8) == 0) && (*(unsigned char *)((char *)oldSlot + 9) == 0))
        {
            int *prev = *oldSlot;
            int *next = oldSlot[1];
            if (prev != 0)
                *(int **)(prev + 4) = next;
            if (next == nullptr)
            {
                *(int **)(DAT_0120558c + 8) = *(int **)(DAT_0120558c + 4);
                *(int **)(DAT_0120558c + 4) = prev;
                if (prev == 0)
                    *(int **)(DAT_0120558c + 8) = *(int **)(DAT_0120558c + 0xc);
            }
            else
            {
                *next = prev;
            }
        }
    }
    *(int *)((char *)manager2 + 0x40) = savedRef6;
}