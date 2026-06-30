// FUNC_NAME: NetGhost::syncProperty
// Address: 0x0073df20
// Role: Transfers a property from the source object to the destination property structure.
// This function appears to handle the replication of a specific property type (identified by hash 0x1b2d5c51)
// from the server-side object to the client-side ghost. It manages an intrusive linked list node pointer
// and sets flags based on the source object's state.

void __thiscall NetGhost::syncProperty(void *this, GhostProperty *dest)
{
    int *listHead;            // piVar1: pointer to the list head in dest
    void *sourcePtr;          // iVar2: pointer to the source property node

    // Check if the destination already has the expected type hash
    if ((**(code **)*dest)() == 0x1b2d5c51) // Virtual function returning type hash?
    {
        // Read the source node pointer from this+0x5c
        if (*(int *)((char *)this + 0x5c) == 0)
        {
            sourcePtr = (void *)0;
        }
        else
        {
            sourcePtr = *(void **)((char *)this + 0x5c) - 0x48; // Offset to containing structure
        }

        listHead = (int *)&dest->nodeHead; // dest + 0x19 (offset 0x64 bytes from dest start? actually +0x19 *4 = 0x64)
        // Re-add offset to get back the original pointer (if non-zero)
        if (sourcePtr != (void *)0)
        {
            sourcePtr = (void *)((int)sourcePtr + 0x48);
        }

        // Update the list head if changed
        if (*listHead != (int)sourcePtr)
        {
            if (*listHead != 0)
            {
                FUN_004daf90(listHead); // Deallocate or release old pointer
            }
            *listHead = (int)sourcePtr;
            if (sourcePtr != (void *)0)
            {
                dest->nodePrev = *(GhostProperty **)((int)sourcePtr + 4); // back pointer
                *(int **)((int)sourcePtr + 4) = listHead; // update node's back pointer to list head
            }
        }

        // Copy global values (likely frame counters or times)
        dest->field_0x18 = g_someGlobal1;
        dest->field_0x17 = g_someGlobal2;
        dest->flags = 1; // dest + 0x1f (offset 0x7c)

        // Check another source pointer at this+0x64 (100)
        if (*(int *)((char *)this + 100) == 0)
        {
            sourcePtr = (void *)0;
        }
        else
        {
            sourcePtr = (void *)(*(int *)((char *)this + 100) - 0x48);
        }

        int state = *(int *)((int)sourcePtr + 0x84); // read state from source's parent
        if ((state > 3) && ((state < 7) || (state == 8)))
        {
            dest->flagByte |= 0x20; // dest + 0x16 (offset 0x58)
        }
    }
}