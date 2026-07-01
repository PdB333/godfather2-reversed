// FUNC_NAME: LinkedListMap::getValueByKey
int __thiscall LinkedListMap::getValueByKey(int param_2) {
    // this+0x60: head pointer of linked list
    int currentNode = *(int *)(this + 0x60);
    int result = 0;
    if (currentNode != 0) {
        while (*(int *)(currentNode + 0x40) != param_2) {
            // +0x4: next node pointer
            currentNode = *(int *)(currentNode + 4);
            if (currentNode == 0) {
                return result;
            }
        }
        // +0x44: short value (sign-extended to int)
        result = (int)*(short *)(currentNode + 0x44);
    }
    return result;
}