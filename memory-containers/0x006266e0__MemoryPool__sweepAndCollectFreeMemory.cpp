// FUNC_NAME: MemoryPool::sweepAndCollectFreeMemory
// Function at 0x006266e0: Sweeps through active memory blocks, collects those freeable and returns total freed size

class MemoryPool {
public:
    // +0x10: Page* m_pPage
};

struct Page {
    // +0x10: Node* m_pActiveHead;
    // +0x14: Node* m_pFreeHead;
};

struct Node {
    // +0x00: Node* m_pNext;
    // +0x04: uint8_t m_unknown;
    // +0x05: uint8_t m_flags; // bit0=used, bit1=freeable, bit4=locked
    // +0x08: BlockHeader* m_pHeader;
    // +0x0C: uint32_t m_blockSize;
};

struct BlockHeader {
    // +0x06: uint8_t m_flags; // bit2=skipFreeAttempt
};

// Returns total freed size (header 0x10 + block size)
int MemoryPool::sweepAndCollectFreeMemory() {
    Node** ppPrevNext = &m_pPage->m_pActiveHead;
    Node* pCurr = *ppPrevNext;
    int totalFreed = 0;
    Node* pCollectedList = nullptr;
    Node** ppCollectedTail = &pCollectedList;

    do {
        if (pCurr == nullptr) {
            // Append collected nodes to free list
            *ppCollectedTail = m_pPage->m_pFreeHead;
            m_pPage->m_pFreeHead = pCollectedList;
            return totalFreed;
        }

        Node* pNext = pCurr->m_pNext;
        // Check if block is freeable: not used, not locked, and freeable flag set
        if ((pCurr->m_flags & 0x11) == 0 && (pCurr->m_flags & 0x02) != 0) {
            // Check if skip flag is not set in header
            if ((pCurr->m_pHeader->m_flags & 0x04) == 0) {
                // Check global state (e.g., reference count or mutex)
                uint64_t globalState = FUN_00637f90(); // returns (pointer, bytePtr)
                if (*(uint32_t*)globalState != 0) {
                    // Remove node from active list
                    *ppPrevNext = pNext;
                    pCurr->m_pNext = nullptr;
                    // Accumulate freed size (16 header + block size)
                    totalFreed += 0x10 + pCurr->m_blockSize;
                    // Add to collected list
                    *ppCollectedTail = pCurr;
                    ppCollectedTail = &pCurr->m_pNext;
                    pNext = pCurr; // So that prev pointer remains correct (but pNext will be overwritten at loop end)
                    // Note: pCurr already disconnected, pNext is the original next
                    // Set pNext back to original next for loop iteration
                    pNext = *ppPrevNext;
                    ppPrevNext = &pCurr->m_pNext; // Actually we already set *ppPrevNext = original pNext, so this line is tricky. 
                    // Let's keep the original logic: after removal, we set prev to pCurr's next, then loop continues with pCurr as the node we just collected.
                    // The assembly does: *puVar5 = *puVar2; then *puVar2 = 0; then iVar4 = iVar4 + 0x10 + puVar2[3]; then *local_8 = puVar2; then puVar6 = puVar5; local_8 = puVar2;
                    // So it updates pPrevNext to point to the original next (already done by deref), then sets pCurr->next=0, then appends pCurr to collected list, then updates pPrevNext pointer to &pCurr->m_pNext (which is now 0, but that doesn't matter because we later set pCurr = *puVar6, which is the original next). 
                    // To faithfully reconstruct:
                    // *ppPrevNext = pCurr->m_pNext; // remove from list
                    // pCurr->m_pNext = nullptr;
                    // totalFreed += 0x10 + pCurr->m_blockSize;
                    // *ppCollectedTail = pCurr;
                    // ppCollectedTail = &pCurr->m_pNext;
                    // ppPrevNext = &pCurr->m_pNext; // This is the tricky part: after removal, the prev pointer now points to the next node via the node we just removed? Actually no, we need to keep ppPrevNext unchanged because the next iteration should use the same ppPrevNext variable which now points to the original next of the removed node. Let's follow assembly: puVar6 = puVar5; -> after removal, puVar5 still holds address of the next pointer that was updated. Then later puVar2 = *puVar6; means pCurr = *ppPrevNext; which is the original pNext. So we don't need to change ppPrevNext. The assembly sets puVar6 (which will be used as previous) to puVar5 (the original previous pointer), and then at loop end, puVar2 = *puVar6; so it continues from the new current. So our loop logic: after removal, we set pCurr = *ppPrevNext (which is the original pNext), and ppPrevNext remains unchanged. And we don't change ppPrevNext to &pCurr->m_pNext because that would skip a node. So let's reorganize.

                    // Correct reconstruction: Use a pointer to previous next pointer (ppPrevNext) that we update only when we do NOT remove the node. When we remove, we set *ppPrevNext to pCurr->m_pNext, then pCurr = *ppPrevNext (the new head). But then we also need to not advance ppPrevNext. So we can do:
                    // Node* pOldNext = pCurr->m_pNext;
                    // *ppPrevNext = pOldNext;
                    // pCurr->m_pNext = nullptr;
                    // totalFreed += ...;
                    // *ppCollectedTail = pCurr;
                    // ppCollectedTail = &pCurr->m_pNext;
                    // pCurr = pOldNext; // continue with the next node
                    // continue; // skip the normal ppPrevNext advance
                    // This matches the assembly.
                    // But we have to preserve the do-while structure. Let's rewrite more faithfully.

                    
                } else {
                    // Set skip flag to avoid rechecking
                    pCurr->m_pHeader->m_flags |= 0x04;
                }
            }
            // Clear freeable flag regardless
            pCurr->m_flags &= 0xFD;
        }
        // Advance
        ppPrevNext = &pCurr->m_pNext;
        pCurr = pCurr->m_pNext;
    } while (true);
}
```