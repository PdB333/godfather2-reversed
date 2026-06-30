// FUNC_NAME: TransformNode::propagateTransform
void __thiscall TransformNode::propagateTransform(TransformNode* thisPtr) {
    // Check if this node's own transform is already computed (flag at +0x80)
    // If flag is zero, copy the parent transform (at +0x40) to this node's local transform (at +0x00)
    // Otherwise, assertion failure and then traverse children anyway
    if (thisPtr->flags == 0) {
        // Copy 16 floats (64 bytes) from parent matrix to local matrix
        // This represents inheritance of the parent's world transform when the node has no local transform
        thisPtr->localMatrix[0] = thisPtr->parentMatrix[0];
        thisPtr->localMatrix[1] = thisPtr->parentMatrix[1];
        thisPtr->localMatrix[2] = thisPtr->parentMatrix[2];
        thisPtr->localMatrix[3] = thisPtr->parentMatrix[3];
        thisPtr->localMatrix[4] = thisPtr->parentMatrix[4];
        thisPtr->localMatrix[5] = thisPtr->parentMatrix[5];
        thisPtr->localMatrix[6] = thisPtr->parentMatrix[6];
        thisPtr->localMatrix[7] = thisPtr->parentMatrix[7];
        thisPtr->localMatrix[8] = thisPtr->parentMatrix[8];
        thisPtr->localMatrix[9] = thisPtr->parentMatrix[9];
        thisPtr->localMatrix[10] = thisPtr->parentMatrix[10];
        thisPtr->localMatrix[11] = thisPtr->parentMatrix[11];
        thisPtr->localMatrix[12] = thisPtr->parentMatrix[12];
        thisPtr->localMatrix[13] = thisPtr->parentMatrix[13];
        thisPtr->localMatrix[14] = thisPtr->parentMatrix[14];
        thisPtr->localMatrix[15] = thisPtr->parentMatrix[15];
    } else {
        // Flag was non-zero, indicates an invalid state; trigger assertion
        assertionFailed();
        // Falls through to traverse children regardless
    }

    // Traverse linked list of children (next pointer at +0x88 from child node)
    for (TransformNode* child = thisPtr->children; child != nullptr; child = child->next) {
        child->propagateTransform();
    }
}