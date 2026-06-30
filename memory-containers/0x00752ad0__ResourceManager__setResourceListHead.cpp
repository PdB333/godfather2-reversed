// FUNC_NAME: ResourceManager::setResourceListHead
void __thiscall ResourceManager::setResourceListHead(int this, uint param_2, uint param_3, uint param_4, uint param_5)
{
    int *pHead; // pointer to list head at this+0x98
    int newHead; // pointer from pool
    int hash; // hash key?
    bool success;
    int local_8[2]; // stack buffer for lookup result? or return data

    local_8[0] = 0;
    local_8[1] = 0;

    // Lookup a resource by hash (0x7a1b032e) and additional parameters
    success = hashLookup(local_8, 0x7a1b032e, param_2, param_3, param_4, param_5);
    if (success != 0) {
        // Get a new node from a pool/manufacturer using the lookup result
        newHead = allocateNode(local_8); // FUN_007520c0? Actually it takes no args? Wait decompiled shows no args for FUN_007520c0, but here we pass local_8? No, the decompiled call is FUN_007520c0() with no args. But then later uses local_8? Actually the decompiled code calls FUN_007520c0() with no args. So it's independent of local_8. So the lookup result is used only for the condition? That seems odd. Wait the condition checks success, then calls FUN_007520c0(). So perhaps the lookup just checks if the resource exists, and then allocates a new node regardless? That would be a typical pattern: if the resource is not already present, create a new node. But the decompiled code does not pass local_8 to FUN_007520c0. So likely FUN_007520c0 returns a pointer to a node (maybe from a freelist or static array). Then the function inserts it into the list.
        // So newHead = some node pointer, not necessarily related to local_8. The local_8 might be a temporary used only for the hash check. The constant 0x7a1b032e might be a hash of something like "secondaryResource" or a class ID.
        int* newHead = (int*)FUN_007520c0(); // returns pointer to a node (or NULL if pool empty)
        pHead = (int*)(this + 0x98); // +0x98: list head pointer
        if (newHead == 0) {
            // If no node available, set to 0? Actually the code checks iVar3 == 0 and sets iVar3=0. Then later if newHead is 0, they still set *pHead = 0, and then skip the rest because newHead==0.
        }
        // If newHead is 0, it's treated as NULL
        // Remove old head if different and non-NULL
        if (*pHead != newHead) {
            if (*pHead != 0) {
                removeNodeFromList(pHead); // FUN_004daf90 - removes the node at head
            }
            *pHead = newHead; // set new head
            if (newHead != 0) {
                // Set the new node's next pointer to point to the address of the head pointer (intrusive list with back pointer)
                *(int*)(this + 0x9c) = *(int*)(newHead + 4); // store old node->next in this field (maybe used for iteration or removal?)
                *(int**)(newHead + 4) = pHead; // node->next = &head
            }
        }
    }
    return;
}