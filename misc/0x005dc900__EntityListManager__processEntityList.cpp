// FUNC_NAME: EntityListManager::processEntityList
// Function address: 0x005dc900
// This function appears to iterate over a linked list of entities and update visibility flags.
// It likely belongs to the EARS engine's entity management system.

int __thiscall EntityListManager::processEntityList(void *this, char param_2)
{
    int entityId;         // iVar4
    int listHead;         // iVar1 (pointer from this+8)
    int currentNode;      // iVar2
    int listSentinel;     // iVar3

    entityId = getCurrentEntityId(this); // FUN_005dc670 returns some ID or pointer
    if (entityId != 0)
    {
        listHead = *(int *)((char *)this + 8);          // +0x8: pointer to list structure
        currentNode = **(int **)(listHead + 0x1c);      // +0x1c: head pointer, dereferenced twice to get first node's data?
        while( true )
        {
            listSentinel = *(int *)(*(int *)((char *)this + 8) + 0x1c); // recompute head pointer
            // Check if list structure pointer is valid (likely assertion)
            if ((listHead == 0) || (listHead != *(int *)((char *)this + 8)))
            {
                assertionFailure(); // FUN_00b97aea
            }
            if (currentNode == listSentinel) break; // end of list when we wrap around (circular list)
            if (listHead == 0)
            {
                assertionFailure(); // FUN_00b97aea
            }
            if (currentNode == *(int *)(listHead + 0x1c)) // if current node equals head pointer?
            {
                assertionFailure(); // FUN_00b97aea
            }
            int entityPtr = *(int *)(currentNode + 0x10); // +0x10: pointer to entity structure
            if (entityPtr != entityId)
            {
                if (param_2 == '\0')
                {
                    *(char *)(entityPtr + 0x298) = 0; // +0x298: visibility flag (0 = hidden)
                }
                else if (*(char *)(entityPtr + 0x299) == '\0')
                {
                    *(char *)(entityPtr + 0x298) = 1; // +0x299: another flag, if zero set visible
                }
            }
            advanceToNextNode(); // FUN_005e09e0
        }
        return 1;
    }
    return 0;
}