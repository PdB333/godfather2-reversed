// FUNC_NAME: Entity::~Entity
void __fastcall Entity_destructor(Entity* thisPtr)
{
    // Set vtable to current base class destructor vtable
    thisPtr->vtable = &PTR_FUN_00e371d8;

    // Call common cleanup routine (e.g., release resources)
    FUN_0052e710();

    // ---- Remove from global active list (offset +0x28) ----
    int* pNode = (int*)(gEntityManager + 0x14); // Pointer to global list head pointer
    int* objPtr = thisPtr->field_0x28;          // Pointer stored at +0x28
    if (objPtr != 0)
    {
        // Append objPtr to a free list or buffer at gEntityManager+0x14
        *(*pNode) = (int)&PTR_LAB_01124ba8;     // Write sentinel address
        *pNode = *pNode + 4;                    // Advance pointer
        *(*pNode) = (int)objPtr;                // Write object pointer
        *pNode = *pNode + 4;                    // Advance pointer again
        thisPtr->field_0x28 = 0;
    }

    // ---- Remove from doubly linked list at offsets +0x90 and +0x94 ----
    int* listNode = (int*)thisPtr->field_0x90;  // Next pointer at +0x90
    if (listNode != 0)
    {
        int** prevNext = (int**)(listNode + 1); // Address of prev->next?
        if (listNode == (int*)((char*)thisPtr + 0x90))
        {
            // Node is the head, update head (prev pointer at +0x94)
            *(int**)((char*)thisPtr + 0x94) = (int*)thisPtr->field_0x94;
        }
        else
        {
            // Traverse to find predecessor
            int** curPrev = (int**)(listNode[1]); // Start from stored next
            while (curPrev != (int**)((char*)thisPtr + 0x90))
            {
                listNode = (int*)listNode[1];
                curPrev = (int**)listNode[1];
            }
            // Redirect predecessor's next to skip this node
            listNode[1] = thisPtr->field_0x94;
        }
    }

    // ---- Switch vtable to next base class ----
    thisPtr->vtable = &PTR_FUN_00e37f48;

    // ---- Remove from another doubly linked list (offsets +0x10 and +0x14) ----
    if (thisPtr->field_0x10 != 0)
    {
        // Relink prev and next to remove this node
        *(int**)(thisPtr->field_0x14 + 0x10) = thisPtr->field_0x10; // prev->next = next
        *(int**)(thisPtr->field_0x10 + 0x14) = thisPtr->field_0x14; // next->prev = prev
        thisPtr->field_0x10 = 0;
    }

    // ---- Final vtable switch ----
    thisPtr->vtable = &PTR_LAB_00e37304;
    return;
}