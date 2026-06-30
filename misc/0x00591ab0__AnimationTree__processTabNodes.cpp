// FUNC_NAME: AnimationTree::processTabNodes

void __thiscall AnimationTree::processTabNodes(int* errorOut, int param_2, char* node, int* animContext)
{
    // +0x7c: pointer to some object (maybe AnimationNodeTable)
    // +0x68: offset within that object, likely a sentinel node pointer
    // animContext: [0] = pointer to float array, [1] = size of array
    // node: first byte is type, possibly \t (0x09) indicates an animated node
    // Recursively processes all children except one matching a sentinel.

    undefined4 localError;
    uint index;

    localError = *errorOut; // save initial error state

    if (*node == '\t') 
    {
        int* nodeData = *(int**)(node + 4); // node + 4: pointer to animation data
        index = *(uint*)(nodeData + 1); // nodeData[1] is the animation index
        if (animContext[1] <= index) 
        {
            localError = 0; // clear error
            FUN_00591c00(&localError); // call error handler (likely assertion or logging)
        }
        // Check if current value is a special constant, if so replace
        if (*(float*)(animContext[0] + index * 4) == DAT_00e2b1a4) 
        {
            index = *(uint*)(nodeData + 1); // re-read index (could be modified?)
            if (animContext[1] <= index) 
            {
                localError = 0;
                FUN_00591c00(&localError);
            }
            *(undefined4*)(animContext[0] + index * 4) = DAT_00e2b04c;
        }
    }

    int childCount = node[1]; // second byte: number of children
    if (childCount > 0) 
    {
        int* childPtrs = (int*)(node + 0xc); // list of child node pointers
        int sentinel = *(int*)(*(int*)(param_2 + 0x7c) + 0x68); // sentinel node pointer
        do {
            if (*childPtrs != sentinel) 
            {
                processTabNodes(this, *childPtrs, animContext); // recursive call with same errorOut? Not passed.
                // Note: this recursion does not pass errorOut, likely only top-level cares.
            }
            childPtrs++;
            childCount--;
        } while (childCount != 0);
    }
    return;
}