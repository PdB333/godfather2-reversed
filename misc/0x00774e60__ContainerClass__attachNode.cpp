// FUNC_NAME: ContainerClass::attachNode
void __thiscall ContainerClass::attachNode(int param_1, int param_2)
{
    int* headPtr = (int*)(param_1 + 0x5c); // pointer to head of linked list (at offset 0x5c)
    int newNode;
    
    if (param_2 == 0) {
        newNode = 0;
    } else {
        newNode = param_2 + 0x48; // node is embedded at offset 0x48 in the object
    }
    
    if (*headPtr != newNode) {
        if (*headPtr != 0) {
            detachNode(headPtr); // FUN_004daf90 - remove the old head node
        }
        *headPtr = newNode; // set new head
        if (newNode != 0) {
            *(int*)(param_1 + 0x60) = *(int*)(newNode + 4); // save node's next pointer to +0x60
            *(int**)(newNode + 4) = headPtr; // node's next points back to the head pointer's location
        }
    }
}