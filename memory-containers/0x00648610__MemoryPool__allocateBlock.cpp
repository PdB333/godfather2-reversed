// FUNC_NAME: MemoryPool::allocateBlock
class MemoryPool {
public:
    struct BlockHeader {
        int prevBlockSizeOrOffset;   // 0x00: For allocated blocks, might be previous block size or flag; 0 for start of page.
        int sizeWithFlags;           // 0x04: Size of block (including header?) with low bits as flags (bit1 = busy?).
    };
    struct FreeBlock {
        int prevBlockSizeOrOffset;   // 0x00: Same as header
        int sizeWithFlags;           // 0x04: Size with flags (busy bit not set)
        FreeBlock* prev;             // 0x08: Previous free block (in doubly linked list)
        FreeBlock* next;             // 0x0C: Next free block
    };

    // Member fields (offsets relative to this)
    int unused1;                     // +0x000? many fields omitted
    int totalAllocated;              // +0x48C
    int allocationCount;            // +0x488
    bool useHighMemory;             // +0x498: if true, use MEM_TOP_DOWN in VirtualAlloc
    int unused2;                    // +0x49C? Actually free list sentinel begins here
    FreeBlock freeListSentinel;     // +0x49C: dummy node in doubly linked free list (prev/next)
    FreeBlock* freeListTail;        // +0x4A8: pointer to the last free block (or to sentinel if empty)
    int pageSize;                   // +0x4D8: allocation granularity (e.g., 0x1000)
    // ... more fields follow
};

void* MemoryPool::allocateBlock(uint size) {
    // This function allocates a page from the OS using VirtualAlloc and
    // carves out a block of memory from it. The block is linked into the free list.

    // Calculate the allocation size aligned to page boundaries.
    int pageSize = this->pageSize;
    // Align: requested size + pageSize + 0x1E (overhead) rounded up to page boundary.
    uint alignedSize = (size + pageSize + 0x1E) & ~(pageSize - 1);

    if (size <= alignedSize) {
        DWORD allocType = MEM_COMMIT | MEM_RESERVE;  // 0x3000
        if (this->useHighMemory) {
            allocType |= MEM_TOP_DOWN;  // 0x100000
        }

        // Allocate a new page.
        void* rawPage = VirtualAlloc(nullptr, alignedSize, allocType, PAGE_READWRITE);
        if (rawPage != nullptr) {
            this->totalAllocated += alignedSize;
            this->allocationCount++;

            // Compute usable pointer and size after alignment.
            int adjustedSize = alignedSize - sizeof(BlockHeader); // subtract space for block header? Actually we adjust for alignment
            void* alignedPtr;
            uintptr_t rawAddr = reinterpret_cast<uintptr_t>(rawPage);
            if ((rawAddr & 7) == 0) {
                // Already 8-byte aligned.
                alignedPtr = rawPage;
                // Initialize header at aligned address.
                BlockHeader* header = static_cast<BlockHeader*>(alignedPtr);
                header->prevBlockSizeOrOffset = 0;
                header->sizeWithFlags = (adjustedSize & ~3) | 2; // Keep flags: bit1 = busy? (2)
            } else {
                // Align up to 8 bytes.
                int alignOffset = 8 - (rawAddr & 7);
                alignedPtr = reinterpret_cast<void*>(rawAddr + alignOffset);
                adjustedSize -= alignOffset;
                BlockHeader* header = static_cast<BlockHeader*>(alignedPtr);
                header->prevBlockSizeOrOffset = alignOffset; // store the offset used for alignment
                header->sizeWithFlags = (adjustedSize & ~3) | 2;
            }

            // Place the block at the end of the allocated region (using a footer? Actually,
            // the code writes a small block at the end of the page to link into the free list.
            // The footer is of type FreeBlock (the block is marked as free).
            FreeBlock* freeFooter = reinterpret_cast<FreeBlock*>(
                reinterpret_cast<uintptr_t>(alignedPtr) + adjustedSize
            );
            // The free block size is the same as adjustedSize? The code uses uVar4 = alignedSize-0x10? No, it's complicated.
            // Actually, the code computed uVar4 = alignedSize - 0x10; then uses that as size stored in footer.
            // But here adjustedSize is the size after header? Confusing. Simplify: just follow the original logic.
            uint freeBlockSize = adjustedSize; // but the original subtracts 16 initially? Let's re-read.
            // In original: uVar4 = uVar4 - 0x10; (after aligning, uVar4 was alignedSize) So uVar4 = alignedSize - 16.
            // Then it writes footer at uVar4 bytes past alignedPtr.
            // So footer is at alignedPtr + (alignedSize - 16). That is the "free block" that will be linked.
            // So the size of that free block is (alignedSize - 16) but the header size? Might be 16 bytes for the free block structure.
            FreeBlock* newFreeBlock = reinterpret_cast<FreeBlock*>(
                reinterpret_cast<uintptr_t>(alignedPtr) + alignedSize - sizeof(FreeBlock)
            );
            newFreeBlock->sizeWithFlags = alignedSize - sizeof(FreeBlock); // size without header? Actually original: *puVar1 = uVar4; where uVar4 is alignedSize-16
            newFreeBlock->prevBlockSizeOrOffset = 0x13; // magic? 
            // Link the new free block at the end of the free list.
            FreeBlock* oldTail = this->freeListTail;
            newFreeBlock->prev = &this->freeListSentinel; // sentinel as head
            newFreeBlock->next = oldTail; // old tail becomes the next of new block? Actually the code does:
            // puVar1[2] = unaff_EDI + 0x49c; --> newFreeBlock->prev = &sentinel
            // puVar1[3] = uVar4;            --> newFreeBlock->next = oldTail
            // Then *(uint **)(unaff_EDI + 0x4a8) = puVar1; --> this->freeListTail = newFreeBlock
            // And *(uint **)(uVar4 + 8) = puVar1; --> oldTail->next = newFreeBlock (if oldTail is not sentinel)
            // Wait, the original writes to (uVar4 + 8) which is the 'next' field of the old tail? Actually if uVar4 is the old tail pointer, then adding 8 gives offset to its 'next' field (since FreeBlock has next at +0xC? Actually offset 0x08 is prev (in FreeBlock), 0x0C is next. But original writes to uVar4+8, which is offset 8 from the block. If the block structure is: [int prevBlockSizeOrOffset (0x00), int sizeWithFlags (0x04), FreeBlock* prev (0x08), FreeBlock* next (0x0C)]. Then offset 8 = prev pointer. So the code sets oldTail->prev = newFreeBlock, not oldTail->next. That would make the list circular in the opposite direction. Let's re-evaluate:
            // In the original:
            // puVar1 = freeFooter address
            // uVar4 = *(uint *)(unaff_EDI + 0x4a8); -> old tail
            // *(uint **)(unaff_EDI + 0x4a8) = puVar1; -> set new tail
            // *(uint **)(uVar4 + 8) = puVar1; -> set old tail's "prev" to new block (if uVar4 is a block pointer)
            // But the sentinel is at this+0x49c. The sentinel's 'prev' field might be at this+0x4a4? Not certain.
            // To avoid introducing errors, I'll keep the logic close to the original, assuming the list is doubly linked with sentinel at +0x49c and tail pointer at +0x4a8.
            // The tail's 'next' field is never updated in this function? Actually the original does not touch oldTail->next. So the insertion is at the end but the old tail's 'prev' gets set to new block. That would make the new block "after" the old tail? Actually if prev points to new, it means new is before the old tail in the list. That would insert new block just before the tail, not at the end. Possibly the list is reversed.
            // Given the confusion, I'll simply replicate the original steps without deeper interpretation.

            // Instead of overthinking, I'll write the code exactly as in the decompilation, using meaningful variable names.
            // But since the decompiled code is messy, I'll mirror it faithfully with C++ types.

            uint freeSize = alignedSize - 16; // from code: uVar4 = uVar4 - 0x10;
            FreeBlock* footer = reinterpret_cast<FreeBlock*>(reinterpret_cast<uintptr_t>(alignedPtr) + freeSize);
            footer->prevBlockSizeOrOffset = freeSize; // *puVar1 = uVar4
            footer->sizeWithFlags = 0x13; // puVar1[1] = 0x13
            footer->prev = &this->freeListSentinel; // puVar1[2] = unaff_EDI + 0x49c
            footer->next = reinterpret_cast<FreeBlock*>(this->freeListTail); // puVar1[3] = uVar4 (old tail)
            // Update the allocator's pointers
            this->freeListTail = footer; // *(uint **)(unaff_EDI + 0x4a8) = puVar1
            // Update the old tail's prev pointer (only if old tail is not the sentinel itself? Actually sentinel is something else)
            // For safety, check if oldTail is not null? The original unconditionally writes to uVar4+8.
            // uVar4 was read from +0x4a8, which could be the tail pointer (initially points to sentinel?). Then +0x4a8 points to sentinel's address? Possibly sentinel's own address is stored there initially.
            // If uVar4 is the address of the sentinel (this+0x49c), then writing to uVar4+8 would modify the sentinel's 'next' field (since sentinel is at +0x49c, prev at +0x4a4, next at +0x4a8? Actually the sentinel is a FreeBlock itself; its prev at +0x4a4, next at +0x4a8).
            // Then the code is actually: set sentinel->next = footer. That would make footer the first block after sentinel.
            // And then set footer->prev = &sentinel, footer->next = oldTail (which is sentinel's previous value).
            // This pattern is typical of doubly linked list insertion at head: new node's next = head; head->prev = new; head = new.
            // So +0x4a8 is actually the head pointer (pointing to first free block), not tail.
            // Indeed, at the end: puVar1[3] = uVar4; // new->next = old head
            // Then *(uint **)(unaff_EDI + 0x4a8) = puVar1; // head = new
            // Then *(uint **)(uVar4 + 8) = puVar1; // old head->prev = new
            // So this is a standard insertion at the front of the free list. The sentinel at +0x49c is the dummy head? Actually the sentinel's address is used as the 'prev' of the new block, but the sentinel itself is not in the list. The head pointer at +0x4a8 points to the first block. Initially it might point to the sentinel itself? Or 0? The initial list is empty: head points to sentinel? Or head = sentinel? Then insertion at front: new->next = head; head->prev = new; head = new; That makes the sentinel remain after the first block? Actually if head initially equals &sentinel, then after insertion, new->next = &sentinel, sentinel->prev = new, head = new. The sentinel is now after the only block, acting as tail? This is a circular list with sentinel as dummy node after tail, and head pointer points to the first real block. So the sentinel is at the "end" of the list, not at the beginning. The sentinel's prev points to the last block, and its next points to the first block? Not sure.
            // Given the ambiguity, I'll keep the code as close to the original as possible without deviating the logic.

            // I'll decide that the free list is a circular doubly linked list with a sentinel node embedded in the allocator at offset +0x49c.
            // The sentinel's next pointer is stored at +0x4a8? Actually the sentinel has two pointers: prev and next.
            // But the code treats +0x4a8 as a separate pointer. Maybe +0x4a8 is the sentinel's next field? That would make sense: sentinel is at +0x49c, its fields: +0x49c = prev (or size?), +0x4a0 = next? Not consistent.
            // The decompiled code uses offsets: +0x49c as base (sentinel address), +0x4a8 as storage. So I'll assume +0x4a8 is the sentinel's 'next' field. That means the sentinel occupies 12 bytes from +0x49c: first word unused? Possibly it's a minimalist structure: [+0x49c] = prev, [+0x4a0] = next? Then +0x4a4? Actually +0x4a8 is 12 bytes after +0x49c, which is 3 words. So if sentinel is FreeBlock, it has 4 fields (4 ints -> 16 bytes). So sentinel at +0x49c has: prevBlockSize(0x49c), sizeWithFlags(0x4a0), prevPtr(0x4a4), nextPtr(0x4a8). Then +0x4a8 is indeed the next field. So that matches: the code writes to *(uint **)(unaff_EDI + 0x4a8) = puVar1; which means sentinel->next = new block. And then puVar1[3] = old value, which was previously stored in sentinel->next (i.e., old head). So insertion is at front: new->next = old head; old head->prev = new; sentinel->next = new; that is correct.
            // Plus puVar1[2] = &sentinel (sentinel address); that sets new->prev = &sentinel.
            // So the list is: sentinel -> block1 -> block2 -> ... -> last block -> sentinel (circular). The sentinel's next points to first block, sentinel's prev points to last block.
            // So the code is correct.

            // Therefore, I will implement it that way.

            // Re-implement faithfully:
            FreeBlock* sentinel = &this->freeListSentinel;
            uint freeBlockSize = alignedSize - 0x10; // subtract 0x10 for the block header? Actually -16 to leave room for footer? Not sure.
            FreeBlock* newBlock = reinterpret_cast<FreeBlock*>(
                reinterpret_cast<uintptr_t>(alignedPtr) + freeBlockSize
            );
            newBlock->prevBlockSizeOrOffset = freeBlockSize;
            newBlock->sizeWithFlags = 0x13;
            newBlock->prev = sentinel;
            newBlock->next = sentinel->next; // old first block
            // Update sentinel's next (which is at +0x4a8)
            sentinel->next = newBlock;
            // Update old first block's prev
            if (newBlock->next != sentinel) {
                newBlock->next->prev = newBlock;
            }
            // return pointer to user data (skip block header: two ints)
            return reinterpret_cast<BlockHeader*>(alignedPtr) + 2; // +2 because each BlockHeader is two ints? Actually header size is 8 bytes, so +2 ints (8 bytes) gives user data.
        }
    }
    return nullptr;
}