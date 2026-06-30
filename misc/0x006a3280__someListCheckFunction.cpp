// FUNC_NAME: someListCheckFunction

int someListCheckFunction(void* param_1)
{
    int* listHead;
    int* currentNode;
    int count;
    int result;

    listHead = (int*)&listHead; // List sentinel node - points to itself initially
    
    result = FUN_006a2d70(&listHead);
    if (result != 0) {
        // If FUN_006a2d70 returned nonzero, free the list
        currentNode = (int*)*listHead;
        while (currentNode != (int*)&listHead) {
            int* next = (int*)*currentNode;
            FUN_009c8f10(currentNode); // Free node memory
            currentNode = next;
        }
        return result;
    }
    
    // Count nodes in the list
    count = 0;
    currentNode = (int*)*listHead;
    while (currentNode != (int*)&listHead) {
        currentNode = (int*)*currentNode;
        count++;
    }
    
    // Store whether list was non-empty
    *(bool*)param_1 = count != 0;
    
    // Free all nodes
    currentNode = (int*)*listHead;
    while (currentNode != (int*)&listHead) {
        int* next = (int*)*currentNode;
        FUN_009c8f10(currentNode);
        currentNode = next;
    }
    
    return 0;
}