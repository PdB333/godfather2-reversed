// FUNC_NAME: AnimationNode::applyMatrix

void AnimationNode::applyMatrix(void)
{
    // +0x70, +0x74, +0x78, +0x7c: blend channel flags (channel 0-3 active)
    if (    *(int*)(this + 0x70) != 0 
         || *(int*)(this + 0x74) != 0 
         || *(int*)(this + 0x78) != 0 
         || *(int*)(this + 0x7c) != 0)
    {
        // +0x0C: pointer to a matrix provider object (interface)
        // vtable entry +0x60: getMatrix() -> returns pointer to 16 floats (4x4 matrix)
        float* matrix = (*(code**)(**(int**)(this + 0x0C) + 0x60))();

        // Copy the matrix onto the stack
        float localMatrix[16];
        localMatrix[0]  = matrix[0];
        localMatrix[1]  = matrix[1];
        localMatrix[2]  = matrix[2];
        localMatrix[3]  = matrix[3];
        localMatrix[4]  = matrix[4];
        localMatrix[5]  = matrix[5];
        localMatrix[6]  = matrix[6];
        localMatrix[7]  = matrix[7];
        localMatrix[8]  = matrix[8];
        localMatrix[9]  = matrix[9];
        localMatrix[10] = matrix[10];
        localMatrix[11] = matrix[11];
        localMatrix[12] = matrix[12];
        localMatrix[13] = matrix[13];
        localMatrix[14] = matrix[14];
        localMatrix[15] = matrix[15];

        // +0x2C: matrix type (e.g., bind pose vs animation)
        int type = *(int*)(this + 0x2C);
        
        // Global constant (DAT_0110ac04) – possibly kMatrixTypeBindPose
        if (type == g_BindPoseType)
        {
            // +0x08: pointer to an animation data owner
            int* animData = *(int**)(this + 8);
            if (animData != 0)
            {
                // +0x08 within animData: vtable pointer; +0x24: getBlendData() method
                int* blendData = (*(code**)(*(int**)(animData + 8) + 0x24))(); // vtable offset 0x24
                if (blendData != 0)
                {
                    // vtable offset 0x58: maybe getBlendWeight() or something
                    type = (*(code**)(*blendData + 0x58))();
                }
            }
        }

        int resultNode = 0;
        // FUN_004df270: Adds the matrix to a queue (linked list of pending updates)
        // Args: output node, flags at +0x70, stack matrix, type, padding=0, &zero
        int newHead = FUN_004df270(&resultNode, this + 0x70, localMatrix, type, 0, &resultNode);

        // +0x80: head pointer of linked list of nodes waiting for processing
        int* pHead = (int*)(this + 0x80);
        if (*pHead != 0)
        {
            // Old head node: clear its back pointer (+8)
            *(int*)(*pHead + 8) = 0;
            *pHead = 0;
        }
        // Install new head node
        *pHead = newHead;
        if (newHead != 0)
        {
            // Node's +8 points to the head pointer itself (so node knows where it is linked)
            *(int**)(newHead + 8) = pHead;
        }

        // If we have a valid new head and +0x24 points to a parent/owner
        if (*pHead != 0 && *(int*)(this + 0x24) != 0)
        {
            // Notify the owner that a new matrix is pending
            FUN_004df7f0((int*)(this + 0x24));
        }
    }
}