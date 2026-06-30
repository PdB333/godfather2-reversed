// FUNC_NAME: ActionListManager::setCurrentActionNode
void __thiscall ActionListManager::setCurrentActionNode(int this_, int actionObj)
{
    int *headPtr; // eax

    *(int *)(this_ + 0x2678) = 0x1e;                       // +0x2678: action timeout (30 seconds?)
    *(int *)(this_ + 0x1f5c) |= 0x20;                      // +0x1f5c: flags (bit 5 set)
    headPtr = (int *)(this_ + 0x2680);                     // +0x2680: pointer to head of intrusive list
    if (actionObj == 0) {
        actionObj = 0;
    } else {
        actionObj = actionObj + 0x48;                      // each action object has an intrusive node at +0x48
    }
    if (*headPtr != actionObj) {
        if (*headPtr != 0) {
            FUN_004daf90(headPtr);                         // remove old head from list
        }
        *headPtr = actionObj;                              // set new head
        if (actionObj != 0) {
            *(int *)(this_ + 0x2684) = *(int *)(actionObj + 4); // +0x2684: save original next of new node
            *(int **)(actionObj + 4) = headPtr;           // node->next = &head (intrusive list)
        }
    }
}