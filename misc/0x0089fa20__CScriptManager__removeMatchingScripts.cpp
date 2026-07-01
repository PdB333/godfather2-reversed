// FUNC_NAME: CScriptManager::removeMatchingScripts
void __thiscall CScriptManager::removeMatchingScripts(int* thisPtr, int filterPtr)
{
    int* currentNode;
    int* nextNode;
    int* nodeData;
    int* innerData;
    int* scriptPtr;
    int scriptContainer;

    currentNode = (int*)*thisPtr;
    do {
        if (currentNode == thisPtr) {
            return;
        }
        nextNode = (int*)*currentNode;                // node->prev
        nodeData = currentNode + 2;                   // node->data (offset +8)
        scriptContainer = 0;
        if (*nodeData != 0) {
            innerData = *(int**)(*nodeData + 8);     // data->scriptLink
            if (innerData != 0) {
                *(int**)(innerData + 4) = &innerData; // re-init list node (self-loop)
                scriptContainer = (int)((char*)innerData - 0x48); // container_of (offset to enclosing object)
                releaseScriptNode(&innerData);
            }
            if ((scriptContainer == 0) || (scriptContainer == filterPtr)) {
                goto remove_node;
            }
        } else {
remove_node:
            // unlink from doubly-linked list
            *(int*)currentNode[1] = *currentNode;   // node->next->prev = node->prev
            *(int*)(*currentNode + 4) = currentNode[1]; // node->prev->next = node->next
            if (*nodeData != 0) {
                releaseScriptNode(nodeData);
            }
            deleteScriptNode(currentNode);
        }
        currentNode = nextNode;
    } while (true);
}