// FUNC_NAME: CExpressionCompiler::RemapIndices
void __fastcall CExpressionCompiler::RemapIndices(int* pNodeList, int* pFunctionContext)
// ECX = this, EDX = pNodeList (linked list of AST nodes)
{
    bool bModified = false;
    CompilerState* pState = *(CompilerState**)(this + 0x1c); // +0x1c: pointer to compiler state
    int nNewIndex = pState->nCurrentID; // pState[9]
    
    if (pNodeList == nullptr)
        return;
    
    AstNode* pNode = (AstNode*)pNodeList;
    do {
        if (pNode->nType == 8) // kNodeType_VariableReference
        {
            int nOldID = *(int*)(pFunctionContext + 4); // some context-specific ID
            if (pNode->nOldIndex1 == nOldID)
            {
                bModified = true;
                pNode->nOldIndex1 = nNewIndex;
            }
            if (pNode->nOldIndex2 == nOldID)
            {
                bModified = true;
                pNode->nOldIndex2 = nNewIndex;
            }
        }
        pNode = pNode->pNext;
    } while (pNode != nullptr);
    
    if (bModified)
    {
        // Register the mapping: (nNewIndex << 9 | nOldID) << 15
        int encoded = ((nNewIndex << 9) | *(uint*)(pFunctionContext + 4)) << 0xf;
        // pState[3] is a pointer to some data buffer, offset +8 is probably a function pointer or sink
        FUN_006438e0(encoded, *(undefined4*)(pState->pDataBuffer + 8));
        
        // Update max ID if needed
        int nNextID = nNewIndex + 1;
        char* pMaxID = (char*)(pState->pMemory + 0x47); // pState[0] points to a memory block, +0x47 is max allowed ID
        if (*pMaxID < nNextID)
        {
            if (nNextID > 0xf9)
            {
                // Error: too many variables
                pState = (CompilerState*)pState->pDataBuffer; // likely an error handler
                FUN_00638b80("function or expression too complex");
            }
            else
            {
                *pMaxID = (char)nNextID;
            }
        }
        pState->nCurrentID = nNextID;
    }
}