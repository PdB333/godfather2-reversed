// FUNC_NAME: MemoryManager::findBlockForPointer

uint __fastcall MemoryManager::findBlockForPointer(uintptr_t thisPtr, uintptr_t heapBase)
{
    uint32_t uVar1;

    // Check if the second dword of the object indicates an inline block?
    uVar1 = *(uint32_t *)(thisPtr + 4) & 0x7ffffff8;
    if (uVar1 < 0x10) {
        // Iterate over the linked list of memory blocks starting at heapBase+0x460
        // The list is terminated by the sentinel at heapBase+0x448
        for (uVar1 = *(uint32_t *)(heapBase + 0x460); uVar1 != heapBase + 0x448U;
             uVar1 = *(uint32_t *)(uVar1 + 0x18)) {
            // Check if thisPtr falls within the current block [blockStart, blockStart+size)
            if ((uVar1 <= thisPtr) && (thisPtr < *(int32_t *)(uVar1 + 4) + uVar1)) {
                // Calculate address of the last 16 bytes of the block
                uVar1 = *(int32_t *)(uVar1 + 4) + -0x10 + uVar1;
                if (uVar1 <= thisPtr) {
                    // Pointer is in the last 16 bytes - return a special handle
                    // High byte = 1, low 3 bytes = (uVar1 >> 8) & 0xFFFFFF
                    return (1 << 24) | ((uVar1 >> 8) & 0xFFFFFF);
                }
                break;
            }
        }
    }
    // Return the masked initial value (zero low byte)
    return uVar1 & 0xffffff00;
}
``` 

**Notes on reconstructed logic:**
- Offsets `+0x448` and `+0x460` belong to a heap descriptor (`heapBase`), likely the head and tail of a used-block list.
- Block header at offset `+0x4` holds the block size (including header/footer).
- Offset `+0x18` is the next pointer in the linked list.
- The initial mask (`thisPtr+4 & 0x7ffffff8`) may check whether the pointer references a small object from a thread-local cache; values < 0x10 indicate a "large" or non-cached block that needs full list traversal.
- The return value with set high byte (0x01) signals that the pointer falls within the final 16 bytes of a block (possibly a "busy" flag or a special allocation status).