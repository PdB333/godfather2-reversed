// FUNC_NAME: LinkedListIterator::getNext
int __fastcall LinkedListIterator::getNext(int this)
{
    int currentNode;
    int currentData;
    
    getCurrentState(&currentNode, &currentData);
    int storedIndex = *(int *)(this + 0x10);
    if ((currentNode == 0) || (currentNode != this + 0x0c)) {
        assert();
    }
    if (currentData != storedIndex) {
        if (currentNode == 0) {
            assert();
        }
        if (currentData == *(int *)(currentNode + 4)) {
            assert();
        }
        return currentData + 0x10;
    }
    return 0;
}