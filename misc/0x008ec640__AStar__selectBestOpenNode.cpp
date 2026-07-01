// FUNC_NAME: AStar::selectBestOpenNode
uint * __thiscall AStar::selectBestOpenNode(AStar *this, uint *outValue, int maxLevel, int *outLevel) {
    int *currentNode;
    int nodeLevel;
    uint *subNode;
    int heuristic;
    int bestHeuristic;
    int *headNode;

    *outLevel = 4;                          // initial threshold level (maybe default open list size)
    *outValue = 0xfe16702f;                 // sentinel / invalid value
    headNode = *(int **)(*(int *)(this + 0x10));  // this->openList.head (double indirection)
    bestHeuristic = 999999;

    while (true) {
        int *listHead = *(int **)(this + 0x10);
        if (this == (AStar *)-0xc) {        // assertion: this != null
            assert_failed();
        }
        if (currentNode == listHead) {
            break;                          // wrapped around open list
        }
        if (this == (AStar *)-0xc) {
            assert_failed();
        }
        if (currentNode == *(int **)(this + 0x10)) {
            assert_failed();
        }

        nodeLevel = *(int *)(currentNode + 0x1c); // node->level (g cost)
        if (nodeLevel == -1) {              // not yet computed
            subNode = *(uint **)(currentNode + 0x10); // node->childList
            nodeLevel = -1;
            while (subNode != (uint *)0x0) {
                int *childValue = (int *)(subNode + 3); // child->value at offset +0xc
                subNode = (uint *)*subNode;  // next child
                if (nodeLevel < *childValue) {
                    nodeLevel = *childValue;
                }
            }
            *(int *)(currentNode + 0x1c) = nodeLevel; // cache max child value as level
        }

        if (currentNode == *(int **)(this + 0x10)) {
            assert_failed();
        }

        if ((*(int *)(currentNode + 0x18) == 2) && (nodeLevel < maxLevel) && (nodeLevel <= *outLevel)) {
            if (currentNode == *(int **)(this + 0x10)) {
                assert_failed();
            }
            heuristic = computeHeuristic((uint *)(currentNode + 0x10)); // compute heuristic from child list
            if ((nodeLevel < *outLevel) || (heuristic < bestHeuristic)) {
                *outLevel = nodeLevel;
                if (currentNode == *(int **)(this + 0x10)) {
                    assert_failed();
                }
                *outValue = *(uint *)(currentNode + 0xc); // node->value (e.g., node ID)
                bestHeuristic = heuristic;
            }
        }
        advanceOpenList();                    // move to next node in open list
    }
    return outValue;
}