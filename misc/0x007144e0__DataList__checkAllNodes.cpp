// FUNC_NAME: DataList::checkAllNodes
bool DataList::checkAllNodes(int context1, int context2, int matchValue, int context3, int** listHandle) {
    int* currNode = (int*)*listHandle; // dereference pointer to head of list
    bool result = true;
    if (currNode != nullptr) {
        while (true) {
            int nodeData = *currNode;
            bool firstBranch = (nodeData == matchValue) || (shouldSkipNode() == false);
            bool secondBranch = (checkNodeCondition(context1, context2, context3, nodeData, matchValue) != false);
            // continue loop if either branch is true
            if (!firstBranch && !secondBranch) {
                result = false;
                break;
            }
            currNode = (int*)currNode[1]; // advance to next node (next pointer)
            if (currNode == nullptr) {
                result = true;
                break;
            }
        }
    }
    return result;
}