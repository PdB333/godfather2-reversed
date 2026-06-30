// FUNC_NAME: ScriptContext::adjustExpressionDepth
// Address: 0x00642d40
// Role: Adjusts expression depth/complexity counter. If new depth exceeds recorded maximum (byte at node+0x47),
// updates it. If depth > 0xF9 (249), triggers an error "function or expression too complex".
// Then increments the depth field at exprInfo[9] and calls FUN_00642c40 with the previous depth.
void __fastcall ScriptContext::adjustExpressionDepth(int *exprInfo)
{
    // Magic check: first dword of this must be 0xB (valid context identifier)
    if (*(int *)this != 0xB)
        return;

    int *node = (int *)exprInfo[0];   // expression node pointer (offset +0x00)
    int oldDepth = exprInfo[9];       // current depth at offset +0x24 (9*4)
    int newDepth = oldDepth + 1;

    // Update maximum depth recorded in the node (byte at node+0x47)
    unsigned char maxDepth = *(unsigned char *)((int)node + 0x47);
    if (maxDepth < newDepth)
    {
        if (newDepth > 0xF9) // hard limit
        {
            // Error output: expression too complex (exprInfo[3] may hold context)
            FUN_00638b80("function or expression too complex");
        }
        *(unsigned char *)((int)node + 0x47) = (unsigned char)newDepth;
    }

    // Increment depth counter
    exprInfo[9] = oldDepth + 1;

    // Call with the pre-increment depth (oldDepth)
    FUN_00642c40(oldDepth);
}