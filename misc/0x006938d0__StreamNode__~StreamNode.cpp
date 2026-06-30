// FUNC_NAME: StreamNode::~StreamNode

void __thiscall StreamNode::~StreamNode(StreamNode* thisPtr) {
    // +0x1c: pointer to a sub-resource (e.g., data buffer) that needs to be freed
    if (thisPtr->field_0x1c != nullptr) {
        releaseResource(thisPtr->field_0x1c);  // FUN_009c8f10
    }

    // Global cleanup (e.g., dereference a static counter or shared pool)
    staticCleanup();  // FUN_004982b0

    // +0x18: another resource pointer
    releaseResource(thisPtr->field_0x18); // FUN_009c8f10

    // +0x4: pointer to a child node (or sibling list head)
    StreamNode* child = thisPtr->field_0x04;
    if (child != nullptr) {
        // +0x10: pointer to a deeper resource inside child
        releaseResource(child->field_0x10); // FUN_009c8f10
        // +0x4: pointer to next child in a linked list
        if (child->field_0x04 != nullptr) {
            releaseResource(child->field_0x04); // FUN_009c8f10
        }
        // Destroy the child node itself (likely its own destructor or a release function)
        destroyNode(child); // FUN_009c8eb0
    }
    return;
}