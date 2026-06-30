// FUNC_NAME: MemoryPool::allocate
// Function address: 0x006482d0
// This is a page-based memory allocator using VirtualAlloc.
// It manages a doubly-linked list of allocated pages and carves blocks from them.

class MemoryPool {
public:
    // ... other members ...

    // Allocate a block of at least 'size' bytes.
    // 'allowPartial' determines whether to allocate only the committed portion if the full commit fails.
    void* allocate(unsigned int size, char allowPartial) {
        int granularity = *(int*)((char*)this + 0x4d4);     // +0x4d4: allocation granularity (e.g., page size)
        unsigned int alignedSize = (granularity - 1 + size) & ~(granularity - 1U);
        unsigned int totalSize = alignedSize;
        unsigned int commitSize = totalSize;

        if (commitSize < *(unsigned int*)((char*)this + 0x4dc)) {   // +0x4dc: minimum commit size?
            commitSize = (*(unsigned int*)((char*)this + 0x4dc) - 1 + granularity) & ~(granularity - 1U);
        }

        unsigned int reservedSize = commitSize + 0xffff & 0xffff0000; // Round up to 64KB boundary

        void* baseAddress = VirtualAlloc(NULL, reservedSize, MEM_RESERVE, PAGE_READWRITE);
        if (baseAddress != NULL) {
            if (totalSize < *(unsigned int*)((char*)this + 0x4e0)) {   // +0x4e0: another threshold
                totalSize = (*(unsigned int*)((char*)this + 0x4e0) - 1 + granularity) & ~(granularity - 1U);
            }
            if ((reservedSize < totalSize) || (allowPartial != '\0')) {
                totalSize = reservedSize;
            }
            void* committed = VirtualAlloc(baseAddress, totalSize, MEM_COMMIT, PAGE_READWRITE);
            if (committed != NULL) {
                // Use the committed memory as a new page
                goto allocPage;
            }
        }

        // Fallback: reserve and commit in one call
        unsigned int allocType = MEM_RESERVE | MEM_COMMIT;
        if (*(char*)((char*)this + 0x498) != '\0') {        // +0x498: flag for large page allocation?
            allocType = MEM_RESERVE | MEM_COMMIT | MEM_LARGE_PAGES;
        }
        baseAddress = VirtualAlloc(NULL, commitSize, allocType, PAGE_READWRITE);
        if (baseAddress == NULL) {
            return NULL;
        }
        totalSize = commitSize;
        reservedSize = commitSize;

allocPage:
        // Initialize the page header and carve out a block
        unsigned int* page = (unsigned int*)baseAddress;
        unsigned int headerSize = ((unsigned int)page + 0x27) & 0xfffffff8; // Align to 8 bytes
        page[0] = headerSize;            // Start of usable memory after header
        *(unsigned char*)(page + 3) = (unsigned char)(3 >> 1); // +12 bytes: flags? (3 >> 1 = 1)
        page[2] = reservedSize;          // Total reserved size
        page[1] = reservedSize;          // Total committed size? (duplicate)
        bool hasList = *(unsigned int*)((char*)this + 0x464) != (unsigned int)((char*)this + 0x448); // +0x464 and +0x448: linked list head/tail?
        page[7] = (unsigned int)((char*)this + 0x448); // +0x7*4 = 28: pointer to list head
        *(bool*)((char*)page + 0xd) = hasList;   // +13 bytes
        *(bool*)((char*)page + 0xf) = hasList;   // +15 bytes
        *(unsigned char*)((char*)page + 0xe) = 1; // +14 bytes
        page[4] = 0;                // +16 bytes: next pointer?
        page[5] = 0;                // +20 bytes: previous pointer?
        page[6] = *(unsigned int*)((char*)this + 0x460); // +24 bytes: current end? Link to previous page's next
        *(unsigned int**)((char*)this + 0x460) = page;   // +0x460: update last page pointer
        *(unsigned int**)(page[6] + 0x1c) = page;        // Update previous page's next pointer (offset 0x1c = 28? but page[6] points to a page header?)

        page[2] = totalSize;  // Update to actual committed size

        // If no active list, mark that we have at least one page
        if ((*(char*)((char*)this + 0x46c) == '\0') && (*(int*)((char*)this + 0x464) != *(int*)((char*)this + 0x460))) {
            *(unsigned char*)((char*)this + 0x46c) = 1; // +0x46c: flag indicating non-empty list
            *(unsigned int*)((char*)this + 0x468) = 0;  // +0x468: some counter
        }

        // Carve a block from the page
        unsigned int* userData = (unsigned int*)page[0]; // page[0] is pointer to usable area
        unsigned int remaining = (unsigned int)page + reservedSize - (unsigned int)userData;
        unsigned int blockSize = remaining & 0x7ffffff8;
        unsigned int blockHeaderSize = blockSize - 0x10;
        userData[1] = (remaining & 0x80000007) | 3 | blockSize; // Set block size and flags
        userData[0] = 0; // Previous block? Actually, store a zero (maybe sentinel)
        *(unsigned int*)(blockHeaderSize + (unsigned int)userData) = blockHeaderSize; // Footer with same size
        *(unsigned int*)((blockSize - 0xc) + (unsigned int)userData) = 8;  // Magic values?
        *(unsigned int*)((blockSize - 8) + (unsigned int)userData) = 8;
        *(unsigned int*)((blockSize - 4) + (unsigned int)userData) = 9;

        return (void*)userData;
    }
};