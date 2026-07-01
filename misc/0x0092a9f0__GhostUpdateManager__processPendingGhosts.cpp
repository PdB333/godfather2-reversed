// FUNC_NAME: GhostUpdateManager::processPendingGhosts
void __thiscall GhostUpdateManager::processPendingGhosts() {
    // Get the pointer to the item list (global array of ghost data)
    int* itemList = FUN_009b9490(this->needsInitialization != 0); // +0x50: initialization flag
    // Read the start and end indices from the array pointed by +0x118, using index at +0xf4
    uint startIndex = *(uint*)(*(int*)(this + 0x118) + this->currentSegmentIndex * 4);     // +0xf4: segment index
    uint endIndex   = *(uint*)(*(int*)(this + 0x118) + this->currentSegmentIndex * 4 + 4); // +0x118: base pointer to index pairs
    this->totalItemsInSegment = endIndex - startIndex; // +0xfc: total items in current segment
    this->processedCount = 0;                          // +0xf8: count of processed items
    // Clear the three output buffers (reliable, unreliable, and name buffers)
    **(char**)(this + 0x10c) = 0; // reliable ghost buffer
    **(char**)(this + 0x108) = 0; // unreliable ghost buffer
    **(char**)(this + 0x110) = 0; // name/random buffer

    // Allocate an initial data buffer for the segment (size 0x80)
    void* segmentBuffer = FUN_009b9990(0x80, 0);
    FUN_005c4660(*(void**)(this + 0x104), segmentBuffer); // copy to buffer at +0x104

    // Store a pointer obtained from some global (maybe current ghost resource)
    this->resourcePointer = (void*)FUN_009b8f40(); // +0x100

    uint currentIndex = startIndex;
    while (currentIndex < endIndex) {
        // Check if the segment filter flag is set, and if the entity at the current index passes the validity check
        if (this->segmentFilterEnabled != 0) { // +0x124: flag to apply filter
            int* entity = itemList[currentIndex]; // piVar4[ currentIndex-???] actually itemList[currentIndex]? The code uses *piVar4 + uVar7*4, so piVar4 is likely a pointer to the start of the array.
            // Actually piVar4 = FUN_009b9490(...) returns a pointer to the array, so we can access as itemList[uVar7].
            // But the decompiled code is: *(int*)(*piVar4 + uVar7 * 4). That suggests piVar4 is a pointer to a pointer? Let's reinterpret: piVar4 is probably a pointer to an array of pointers. So we need to double-dereference.
            // Given the usage: piVar4 = (int *)FUN_009b9490(...); then later: *(int *)(*piVar4 + uVar7*4). So *piVar4 is a base address, and we add offset uVar7*4. So it's actually: itemBase = *piVar4; then element = *(int*)(itemBase + currentIndex*4). So we need a pointer to the base.
            // For simplicity, we'll assume piVar4 is a pointer to an array pointer.
            int* itemBase = (int*)*itemList;
            int* entityPtr = (int*)*(itemBase + currentIndex);
            
            // Check if the entity's flag at offset 0x44 is valid (e.g., alive or ghost should be sent)
            char isValid = FUN_009add30(*(void**)(entityPtr + 0x44)); // offset 0x44 from entity
            if (isValid != 0) {
                // Allocate buffer for this valid entity and copy to the unreliable buffer
                void* entityBuffer = FUN_009b99c0(0x80, 0);
                FUN_005c4660(*(void**)(this + 0x108), entityBuffer);
                // Set processedCount to number of items processed (including this one)
                this->processedCount = (currentIndex - startIndex) + 1;
                goto afterLoop; // exit the loop
            }
        }
        currentIndex++;
    }
afterLoop:
    // If there are still unprocessed items, generate a random name
    if (this->processedCount < this->totalItemsInSegment) {
        float randomFloat = (float)FUN_009b9ae0(); // get random value [0,1]
        char* nameBuffer = nullptr;
        int unknown = 0;
        int zero = 0;
        void* functionPtr = nullptr; // used for cleanup if nameBuffer is allocated
        uint randomInt = (uint)(long long)(randomFloat + 0.5f); // ROUND
        FUN_00604000(randomInt, &nameBuffer, 1); // generate name from random ID
        char* sourceName = nameBuffer;
        if (nameBuffer == nullptr) {
            sourceName = (char*)0x0120546e; // default name string (global)
        }
        FUN_005c4660(*(void**)(this + 0x110), sourceName, 0x10, 0); // copy name to buffer at +0x110
        this->isNameInRange = (randomInt <= this->maxRandomValue); // bool at +0x64; maxRandomValue at +0x60
        // Allocate buffer for reliable ghost and copy
        void* reliableBuffer = FUN_009b99c0(0x80, 0);
        FUN_005c4660(*(void**)(this + 0x10c), reliableBuffer);
        // Free nameBuffer if it was allocated (assume function pointer is a destructor)
        if (nameBuffer != nullptr) {
            ((void (*)(char*))functionPtr)(nameBuffer);
        }
    }
    return;
}