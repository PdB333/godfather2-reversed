// FUNC_NAME: AllocationManager::createAndAddNode
int __fastcall AllocationManager::createAndAddNode(int thisPtr) // 0x0089b1b0
{
    // +0xac: pointer to head of allocated object list
    // +0xb0: pointer to tail or next pointer of last node

    // Allocate 0x1c bytes for a new object + node
    int* pAlloc = (int*)mem_alloc(0x1c); // FUN_009c8e50(0x1c)

    if (pAlloc == nullptr || !objectInit(pAlloc)) // FUN_0089b0e0(pAlloc)
    {
        return 0; // allocation or initialization failed
    }

    Node* pNode = (Node*)((char*)pAlloc + 0x14); // node starts at offset 0x14 within allocation
    int savedPrev = 0; // local_4

    if (pNode != nullptr)
    {
        savedPrev = pNode->ppHead; // original value at node+4 (maybe from free list)
        pNode->ppHead = (int*)&pNode; // temporary: point to itself via stack variable
    }

    int** ppListHead = (int**)(thisPtr + 0xac); // pointer to head pointer
    int* pTempNode = (int*)pNode; // local_8 = pNode

    // Avoid self-assignment and handle empty list
    if (ppListHead != &pTempNode && *ppListHead != (int)pNode)
    {
        if (*ppListHead != 0)
        {
            listNodeRemove(ppListHead); // FUN_004daf90 - remove old head from list?
        }
        *ppListHead = (int)pNode; // set new head to node

        if (pNode != nullptr)
        {
            *(int**)(thisPtr + 0xb0) = (int*)savedPrev; // store previous next pointer from node
            pNode->ppHead = (int**)ppListHead; // node's ppHead points to list head pointer
        }
    }

    if (pTempNode != 0)
    {
        listNodeRemove(&pTempNode); // cleanup temporary stack reference
    }

    if (*ppListHead == 0)
    {
        return 0; // list head still null => failure
    }

    return (int)((char*)*ppListHead - 0x14); // return pointer to base of allocation (object)
}