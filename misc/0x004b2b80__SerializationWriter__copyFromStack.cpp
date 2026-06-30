// FUNC_NAME: SerializationWriter::copyFromStack
void __fastcall SerializationWriter::copyFromStack(int unused, int **ppObject)
{
    int *pObj = *ppObject;
    // Write vtable pointer at current position in buffer
    **(int **)(pObj + 0x14) = &PTR_LAB_0112453c;  // set vtable
    int *pWritePos = (int *)(pObj + 0x14);
    *pWritePos = *pWritePos + 4;  // advance write pointer by 4

    // Copy caller's stack data (0x854 bytes = 0x215 dwords) into buffer
    int *pSrc = (int *)&stack0x00000004;  // start of caller's stack data
    int stackCopy[534];  // buffer to hold copy (size 0x85C, but only 0x854 used)
    for (int i = 0; i < 0x215; i++) {
        stackCopy[i] = *pSrc++;
    }

    // Align destination to next 4-byte boundary
    pObj = *ppObject;
    void *pDst = (void *)((*(int *)(pObj + 0x14) + 3) & 0xFFFFFFFC);
    *(int **)(pObj + 0x14) = (int *)pDst;

    memcpy(pDst, stackCopy, 0x854);
    // Advance write pointer by copied size
    *(int *)(pObj + 0x14) += 0x854;
}