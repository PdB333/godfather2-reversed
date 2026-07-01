// FUNC_NAME: Navigation::updateCurrentNode
void __thiscall Navigation::updateCurrentNode(void *this, int arg)
{
    int nodeType = *(int *)((char *)this + 0x24); // +0x24: node type (0,1,2)
    int resultNodePtr;
    char buffer108[108]; // for type 0
    char buffer96a[96];  // for type 1
    char buffer96b[96];  // for type 2 (unused but allocated)

    if (nodeType == 0) {
        resultNodePtr = computeNodeFromType0(buffer108, arg); // FUN_0082fa40
    }
    else if (nodeType == 1) {
        resultNodePtr = computeNodeFromType1or2(buffer96a, arg, 0); // FUN_0082f6f0
    }
    else {
        resultNodePtr = computeNodeFromType1or2(buffer96b, arg, 0); // FUN_0082f6f0
    }

    // Compare with current node pointer at +0x30
    if ((char *)this + 0x30 != (char *)resultNodePtr) {
        copyNodeData((void *)resultNodePtr); // FUN_00820830 - copies node data to this
        // Copy 20 bytes of node data from resultNodePtr+0x4c to this+0x7c
        *(long long *)((char *)this + 0x7c) = *(long long *)((char *)resultNodePtr + 0x4c);
        *(long long *)((char *)this + 0x84) = *(long long *)((char *)resultNodePtr + 0x54);
        *(int *)((char *)this + 0x8c) = *(int *)((char *)resultNodePtr + 0x5c);
    }
}