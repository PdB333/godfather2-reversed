// FUNC_NAME: CoverHintNodeManager::createNode
void CoverHintNodeManager::createNode() {
    // Allocate memory for a new CoverHintNode (0xF0 = 240 bytes)
    void* rawMemory = operator new(0xF0); // FUN_009c8e50
    if (rawMemory) {
        // Call constructor on the allocated memory with type argument 0
        CoverHintNode* newNode = new (rawMemory) CoverHintNode(0); // FUN_00982280

        // Set the node as active (+0x0C = 1)
        newNode->isActive = 1; // *(undefined4 *)(newNode + 0xC) = 1

        // Set a global node enable flag (argument 1)
        setNodeEnabledFlag(1); // FUN_00982400

        // Perform manager-level preprocessing (stores this pointer)
        this->preprocessNode(); // FUN_00981eb0(this)

        // Assign the node's update handler function (+0x14)
        newNode->pUpdateFunction = &CoverHintNode::defaultUpdate; // FUN_00960540

        // Finalize node creation in the manager
        CoverHintNodeManager::finalizeCreation(); // FUN_00982e10
    }
}