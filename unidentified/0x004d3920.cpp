// FUNC_004D3920: EAString::eraseAt
int* __thiscall EAString::eraseAt(int* pThis, int index)
{
    // pThis[0] = char* pData (pointer to character buffer)
    // pThis[1] = int mLength (current string length, not including null terminator)
    if ((uint)pThis[1] <= index + 1U) {
        // Index is at or beyond the last character: truncate to index length
        pThis[1] = index;
        // Ensure null termination at new length
        *(char*)(index + *pThis) = 0;
    } else {
        // Remove character at 'index' by shifting subsequent characters left
        _memmove((void*)(*pThis + index), (void*)(*pThis + index + 1),
                 (pThis[1] - index) - 1);
        // Decrease length and null-terminate
        pThis[1] = pThis[1] - 1;
        *(char*)(pThis[1] + *pThis) = 0;
    }
    return pThis;
}