// FUNC_NAME: Subject::attach
int* Subject::attach(int param_1) {
    int* node;
    int* observerList;

    if (this != nullptr) {
        observerList = (int*)getObserverList(this + 0x50, 0); // offset +0x50: pointer to observer list manager
        if (observerList != nullptr) {
            // call virtual function at vtable offset 0x28 (probably some registration callback)
            (*(code**)(*observerList + 0x28))(param_1);
            
            // allocate a new node (8 bytes)
            node = (int*)customAlloc(8);
            if (node != nullptr) {
                // node layout: [0] = pointer to observer structure field (at offset +0x48 from observerList)
                //            [1] = next pointer (singly linked list)
                *node = (int)(observerList + 0x12); // +0x12 ints = +0x48 bytes: field holding the observer object
                node[1] = 0;
                if (observerList + 0x12 == (int*)0x0) {
                    return node;
                }
                node[1] = observerList[0x13]; // +0x13 ints = +0x4C bytes: next pointer (list head)
                observerList[0x13] = (int)node; // insert at head of list
                return node;
            }
            lowMemoryHandler(); // FUN_00449e90
        }
    }
    return nullptr;
}