// FUNC_NAME: initializePoolNodesArray
// Function at 0x00667820 - Initializes an array of pool nodes (linked list of dynamic arrays)
// Each node is 16 bytes: [nextPtr (4), capacity (4), size (4), dataPtr (4)]
// The parameter is a null-terminated array of pointers to these nodes.
// For each node, allocates a buffer of 64 integers (256 bytes) and sets capacity=64, size=0, next=0.
// Returns 0 on success, -2 if allocation fails (with partial cleanup).

int initializePoolNodesArray(int** nodePtrArray) {
    int count = 0;
    int** arrayIter;
    int* currentNode;
    void* allocBuf;

    if (nodePtrArray != (int**)0x0) {
        arrayIter = nodePtrArray;                     // pointer to current element in array
        currentNode = *nodePtrArray;                  // first node pointer
        do {
            allocBuf = _calloc(4, 0x40);             // allocate 64 ints (256 bytes)
            currentNode[3] = (int)allocBuf;           // store data pointer at offset +0xC
            if (allocBuf == (void*)0x0) {
                // allocation failed – clean up already initialized nodes
                if (count != 0) {
                    arrayIter = nodePtrArray;         // reset iterator
                    currentNode = *nodePtrArray;
                    do {
                        count = count - 1;
                        if ((void*)currentNode[3] != (void*)0x0) {
                            _memset((void*)currentNode[3], 0, currentNode[0] * 4); // Zero the data buffer
                            _free((void*)currentNode[3]);
                            currentNode[3] = 0;
                            currentNode[0] = 0;       // next = NULL
                            currentNode[1] = 0;       // capacity = 0
                            currentNode[2] = 0;       // size = 0
                        }
                        arrayIter = arrayIter + 1;
                        currentNode = (int*)*arrayIter;
                    } while (count != 0);
                }
                return 0xfffffffe;                    // -2 failure code
            }
            arrayIter = arrayIter + 1;                // move to next element in array
            currentNode[0] = 0;                       // next pointer = NULL (offset +0x0)
            currentNode[1] = 0x40;                    // capacity = 64 (offset +0x4)
            currentNode[2] = 0;                       // size = 0 (offset +0x8)
            currentNode = (int*)*arrayIter;           // get next node pointer from array
            count = count + 1;
        } while (currentNode != (int*)0x0);
    }
    return 0;
}