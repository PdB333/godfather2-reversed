// FUNC_NAME: Animated::updateAnimationTransform
void __thiscall Animated::updateAnimationTransform(Animated *this, int *pRenderContext)
{
  int iBoneIndex;
  float *pBoneMatrixRow;
  float fResult;
  int pTargetObject;
  float localMatrix[12]; // 3x4 matrix (48 bytes)
  int iLocalVar;
  float (__thiscall *boneFuncTable[5])(); // points to LAB_00898a60 etc.
  float *boneFuncRet[5];
  float matrixRow[4];
  float boneMatrixRow[4];
  float renderData[4];

  // Check global state: current frame counter matches, render manager exists, etc.
  if ( (g_CurrentFrameID == *pRenderContext) && 
       (g_pRenderManager != 0) )
  {
    pTargetObject = **(int **)(g_pRenderManager + 4);
    if ( (pTargetObject != 0) && 
         (pTargetObject - 0x1f30 != 0) && 
         (*(uint *)(pTargetObject - 0x3c) == (this->flags >> 31)) && // sign bit check
         (g_bSomeFlag != 0) )
    {
      // Hash-based object lookup
      iBoneIndex = 0;
      if (this->resourceHash != -0x1e98fd1)
      {
        pTargetObject = FUN_004544a0((uint)this->resourceHash, (uint)this->extraHash);
        if (pTargetObject != 0)
        {
          iBoneIndex = pTargetObject - 0x58; // offset to bone data
          int currentTime = FUN_00471610(); // Get current render time or frame interp
          FUN_00424680(&this->localTransform, currentTime + 0x30); // copy 16 bytes?
        }
      }

      // Build bone transformation matrix if bone count is zero
      if (this->boneCount == 0)
      {
        // Setup function pointer table for bone retrieval (per index)
        boneFuncTable[0] = &LAB_00898a60;
        boneFuncTable[2] = &LAB_00898a70;
        boneFuncTable[4] = &LAB_00898a80;
        boneFuncRet[0] = &LAB_00898a90;
        boneFuncRet[1] = &LAB_00898aa0;
        boneFuncRet[2] = &LAB_00898ab0;
        boneFuncRet[3] = &LAB_00898ac0;
        boneFuncTable[1] = 0;
        boneFuncTable[3] = 0;
        for (int i = 0; i < 5; i++) boneFuncTable[i] = 0;
        // Initialize local matrix to identity
        FUN_00412d90(localMatrix);
        // Copy current transform from this object
        localMatrix[0] = this->transform._11;
        localMatrix[1] = this->transform._12;
        localMatrix[2] = this->transform._13;
        localMatrix[3] = this->transform._14;
        // Get bone matrix from function table using bone index
        pBoneMatrixRow = (float *)(*(code *)boneFuncTable[this->boneIndex * 2])();
        boneMatrixRow[0] = pBoneMatrixRow[0];
        boneMatrixRow[1] = pBoneMatrixRow[1];
        boneMatrixRow[2] = pBoneMatrixRow[2];
        boneMatrixRow[3] = pBoneMatrixRow[3];
        // Multiply matrices: either with or without target object
        if (iBoneIndex == 0)
        {
          iLocalVar = 0;
          fResult = FUN_004df270(localMatrix, &boneMatrixRow, &localMatrix, 0x1ff, 0, &iLocalVar);
        }
        else
        {
          fResult = FUN_004df330(localMatrix, &boneMatrixRow, &localMatrix, 0x1ff, 0, iBoneIndex, 0xffffffff, 0);
        }
        // Push transform to render stack
        FUN_00414db0(fResult);
        FUN_00414df0();
        // If bone count changed, do cleanup
        if (this->boneCount != 0)
        {
          FUN_004df5c0();
        }
      }

      // Update parent transform if present
      if ((*(char *)(g_GlobalState + 0xd3) == '\0') && (this->pParentTransform != 0))
      {
        int currentTime = FUN_00471610();
        FUN_0089d120(currentTime + 0x30);
      }
    }
  }
}