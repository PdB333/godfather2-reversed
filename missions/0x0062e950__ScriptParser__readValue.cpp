// FUNC_NAME: ScriptParser::readValue
// Reconstructed C++ for function at 0x0062e950
// Reads a value from the parser's token stack, expecting a key. Pushes a new pair (1, bool result) onto the stack.
// Offsets: +0x08 = m_pCurrent (current read position, pointer to next token pair)
//          +0x0c = m_pEnd   (end of allocated buffer)
//          +0x1c = m_pLookupBase (base address for lookup table)

int ScriptParser::readValue()
{
    // m_pEnd = *(int**)(this + 0xc)
    int* pEnd = *(int**)(this + 0x0c);
    // m_pCurrent = *(int**)(this + 0x8)
    int* pCurrent = *(int**)(this + 0x08);
    int* pTempCurrent; // local_10
    int result;        // iVar2
    int* pTempShift;   // puVar3
    int* pShiftEnd;    // puVar1
    int checkBool;     // local_c

    // Validate: need at least one token pair available, and current token must not be -1 (sentinel)
    if ( (pCurrent <= pEnd) || (pEnd == nullptr) || (*pEnd == -1) )
    {
        // Error: expected a value but none found
        FUN_00627a20(this, 1, "value expected");
        // Note: extraout_ECX is likely the updated m_pEnd after error handling
        pEnd = extraout_ECX;
    }

    // Compute a temporary pointer: move back by (number of token pairs) * 2 words
    // pTempCurrent = pCurrent + ((pCurrent - pEnd) >> 3) * (-2)
    pTempCurrent = pCurrent + ((pCurrent - pEnd) >> 3) * -2;

    checkBool = 0xffffffff; // sentinel for lookup?
    // Lookup: comparing pTempCurrent to m_pLookupBase
    result = FUN_00636570(&LAB_006261e0, &pTempCurrent, (int)pTempCurrent - *(int*)(this + 0x1c));

    // Write new pair at m_pCurrent: (1, result==0)
    int* pWrite = *(int**)(this + 0x08);
    *pWrite = 1;
    pWrite[1] = (uint)(result == 0);
    // Advance m_pCurrent by one pair (8 bytes)
    *(int*)(this + 0x08) = *(int*)(this + 0x08) + 8;

    // Shift remaining pairs backward to make room for the new pair (actually moving forward from the end)
    pTempShift = *(int**)(this + 0x08); // new current position
    for (pShiftEnd = *(int**)(this + 0x0c); pShiftingEnd < pTempShift; pTempShift = pTempShift - 2)
    {
        *pTempShift = pTempShift[-2];
        pTempShift[1] = pTempShift[-1];
    }
    // Finally, copy the first shifted pair to the end position
    int* pFirstShift = *(int**)(this + 0x08);
    *pShiftEnd = *pFirstShift;
    pShiftEnd[1] = pFirstShift[1];

    // Return number of token pairs in the buffer
    return (*(int*)(this + 0x08) - *(int*)(this + 0x0c)) >> 3;
}