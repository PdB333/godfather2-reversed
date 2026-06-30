// FUNC_NAME: ListNodeManagerOwner::addNodeToTail
void __fastcall ListNodeManagerOwner::addNodeToTail(int thisObj)
{
    ListNodeManager* listMgr = *(ListNodeManager**)(thisObj + 0x18); // +0x18: pointer to list manager
    int newTail = FUN_005fbfc0(listMgr, *(int*)(listMgr + 4), in_EAX); // allocate new node; second arg likely tail/head, third unknown (from EAX)
    FUN_005fc010(); // likely lock or ref count increment
    *(int*)(listMgr + 4) = newTail; // update tail pointer
    // Link: new node's prev->next = new node (circular doubly linked list)
    **(int**)(newTail + 4) = newTail; // newTail->prev->next = newTail
}