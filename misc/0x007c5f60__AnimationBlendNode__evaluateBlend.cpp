// FUNC_NAME: AnimationBlendNode::evaluateBlend
void __fastcall AnimationBlendNode::evaluateBlend(int thisPtr)
{
    int *nodePtr;
    undefined4 blendID;
    int index;
    int local_174[4]; // four ints from this+0x2bb4
    int local_164; // blend ID (from global array)
    int local_160; // child transform node pointer
    int local_158; // other child node pointer
    undefined4 local_15c; // used for linking
    undefined4 local_154; // used for linking

    index = *(int *)(thisPtr + 0x58); // current node index
    local_164 = *(undefined4 *)(&gBlendIDArray + index); // global array of blend IDs

    // Read four ints from the current node's transform block (likely a quaternion)
    local_174[0] = *(int *)(index + 0x2bb4);
    local_174[1] = *(int *)(index + 0x2bb8);
    local_174[2] = *(int *)(index + 0x2bbc);
    local_174[3] = *(int *)(index + 0x2bc0);

    resetTransformState(); // FUN_006dc940

    // If the transform is zero, skip blending
    if (local_174[0] == 0 && local_174[1] == 0 && local_174[2] == 0 && local_174[3] == 0)
        goto cleanup;

    // Find a node matching these coordinates (likely a bone)
    int foundNode = findNodeByPosition(&local_174[0], 0); // FUN_00446130
    int *targetNodeLink = (int *)(thisPtr + 0x8c); // pointer to node link field

    int newTargetNode;
    if (foundNode == 0)
        newTargetNode = 0;
    else
        newTargetNode = foundNode + 0x48; // node data offset

    if (*targetNodeLink != newTargetNode)
    {
        if (*targetNodeLink != 0)
            releaseNode(targetNodeLink); // FUN_004daf90
        *targetNodeLink = newTargetNode;
        if (newTargetNode != 0)
        {
            *(undefined4 *)(thisPtr + 0x90) = *(undefined4 *)(newTargetNode + 4);
            *(int **)(newTargetNode + 4) = targetNodeLink; // link into chain
        }
    }

    // Now get the child transform node from index + 0x48
    int childTransformNode = index + 0x48;
    if (local_160 != childTransformNode)
    {
        if (local_160 != 0)
            releaseNode(&local_160);
        local_160 = childTransformNode;
        if (childTransformNode != 0)
        {
            local_15c = *(undefined4 *)(index + 0x4c);
            *(int **)(index + 0x4c) = &local_160; // link as child
        }
    }

    // Determine the other child node (source or target)
    int otherNode = 0;
    int nodeFromA = *(int *)(thisPtr + 0x84); // first alternative node
    int nodeFromB = *(int *)(thisPtr + 0x7c); // second alternative node

    if (nodeFromA != 0 && nodeFromA != 0x48)
        otherNode = nodeFromA;
    else if (nodeFromB != 0 && nodeFromB != 0x48)
        otherNode = nodeFromB;
    else
        otherNode = 0;

    if (local_158 != otherNode)
    {
        if (local_158 != 0)
            releaseNode(&local_158);
        local_158 = otherNode;
        if (otherNode != 0)
        {
            local_154 = *(undefined4 *)(otherNode + 4);
            *(int **)(otherNode + 4) = &local_158;
        }
    }

    // Update the hierarchy for the child transform node (calculate world matrix)
    updateLocalTransform(&local_160); // FUN_006dd610 (might be computeLocalTransform given name conflict)
    // Actually FUN_006dd610 is called with &local_160; we'll name computeLocalTransform

    // Compute blend factor between blendID and the child transform
    float blendFactor = (float)calculateBlendFactor(local_164, &local_160); // FUN_006dc860

    // Get the target node pointer from the link
    int targetNode;
    if (*targetNodeLink == 0)
        targetNode = 0;
    else
        targetNode = *targetNodeLink - 0x48;

    // Apply the blend with weight blendFactor, into the system (5 = blend type, 0 = slot)
    applyBlend(blendID, targetNode, blendFactor, 5, 0); // FUN_00424dc0

cleanup:
    if (local_158 != 0)
        releaseNode(&local_158);
    if (local_160 != 0)
        releaseNode(&local_160);
    return;
}