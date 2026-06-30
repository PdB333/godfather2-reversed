// FUNC_NAME: LinkedList::allocAndPushBack
void __thiscall LinkedList::allocAndPushBack(void *this)
{
    int *listStruct = (int *)this; // this is a pointer to a list structure
    void *allocatorContext;
    void *allocator;
    int newNode;

    // Determine allocator context; if null, use global default
    allocatorContext = (void *)listStruct[3];
    if (allocatorContext == (void *)0x0) {
        allocatorContext = &DAT_01218a14;
    }

    // Call first virtual function of allocator to allocate a node (size 0x1c = 28 bytes)
    allocator = (void *)listStruct[4]; // pointer to allocator object
    newNode = (*(int (**)(int, void *)) * (int *)allocator)(0x1c, allocatorContext);
    if (newNode != 0) {
        // Initialize the newly allocated node (likely sets node data from list context)
        FUN_006f8540(/* this */ (int)this); // unaff_ESI is actually the 'this' pointer passed in ESI, but Ghidra misidentified it
    }

    // Insert the new node at the tail of the doubly linked list
    if (listStruct[1] != 0) { // if list is not empty (tail exists)
        // Set old tail's next to new node
        *(int *)(listStruct[1] + 0x14) = newNode;
        // Set new node's prev to old tail
        *(int *)(newNode + 0x18) = listStruct[1];
        // Update tail to new node
        listStruct[1] = newNode;
    } else { // list was empty
        listStruct[1] = newNode; // tail = newNode
        listStruct[0] = newNode; // head = newNode
    }
    // Increment count
    listStruct[2] = listStruct[2] + 1;
}