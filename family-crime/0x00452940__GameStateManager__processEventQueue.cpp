// FUNC_NAME: GameStateManager::processEventQueue
class GameStateManager {
public:
    // Assumed member offsets (relative to this):
    // +0x10: firstEventHandler  (some callback list)
    // +0x20: secondEventHandler
    // +0x30: activeListHead   (pointer to head of a linked list)
    // +0x34: activeListTail   (pointer to tail, or next field)
    // +0x40? maybe more

    // Predeclared internal functions (callees reconstructed)
    void beginHashWalk(unsigned int magic);     // 0x0043aff0
    void handleEvent(void* event, int type);    // 0x0043ad10
    void advanceHashWalk();                     // 0x0043b140
    bool isValidPointer(void* ptr);             // 0x00402080
    void flushUpdate(void* target);             // 0x004084d0
    int getFirstFromChain(void* chain);         // 0x004211e0
    void removeFromChain(int* node);            // 0x004daf90

    void processEventQueue() {
        beginHashWalk(0x6a73ba16);

        // local variables for hash walk state
        void** currentBucket = local_8;        // iterator pointer
        uint currentIndex = local_58;          // index in current bucket
        uint totalBuckets = local_54;
        char walkMode = local_64;               // 0 = pointer-based, non-zero = index-based
        void* bucketArray = local_60;           // base of bucket array
        void* currentElement = local_5c;        // current element ptr

        // Main iteration loop
        while (true) {
            bool isEnd;
            if (walkMode == 0) {
                isEnd = (*currentBucket == nullptr);
            } else {
                isEnd = (currentIndex == totalBuckets);
            }
            if (isEnd) break;

            // Fetch the event from current position
            void* eventPointer;
            if (walkMode == 0) {
                eventPointer = currentBucket;
            } else {
                // In index mode, we have a bucket pointer in local_50
                eventPointer = &local_50;
            }

            // Check event type (field at +6)
            if (*(short*)((char*)eventPointer + 6) == 0x25e3) {
                // If it's a short pointer type, use the second word as pointer
                eventPointer = (void*)(uint)*(ushort*)((char*)eventPointer + 4);
            } else {
                // Otherwise use the next word directly
                eventPointer = *(void**)((char*)eventPointer + 4);
            }

            // Dispatch based on event pointer value
            if (eventPointer == nullptr) {
                handleEvent(this + 0x10, 0);
            } else if (eventPointer == (void*)0x1) {
                handleEvent(this + 0x20, 0);

                // Remove a node from the linked list at +0x30
                int* listHeadPtr = (int*)(this + 0x30);
                int* listNode = (int*)(*listHeadPtr);
                if (listNode != 0) {
                    int** prevNext = (int**)(listNode + 1);  // +4 offset
                    if (*prevNext == listHeadPtr) {
                        // Single element in the list
                        *(int**)(listNode + 1) = *(int**)(this + 0x34);
                        *listHeadPtr = 0;
                    } else {
                        // Traverse to find the previous node
                        int** prevTotal = (int**)(listNode[1]); // pointer to next
                        while (*prevTotal != listHeadPtr) {
                            listNode = (int*)*prevTotal;
                            prevTotal = (int**)(*(int*)(listNode + 1));
                        }
                        prevTotal[1] = *(int**)(this + 0x34);
                        *listHeadPtr = 0;
                    }
                }
            }

            // Advance to next element in the walk
            if (walkMode == 0) {
                // Pointer-based walk
                if ((int)currentIndex < 0) {
                    // Go to next bucket via computed offset
                    currentBucket = (void**)((char*)currentBucket + (int)(*currentBucket));
                    // Call advance function (maybe sets up next bucket)
                    advanceHashWalk();
                } else if ((int)currentIndex < (int)(totalBuckets - 1)) {
                    currentIndex++;
                    currentBucket = (void**)((char*)currentBucket + (int)(*currentBucket));
                } else {
                    currentBucket = &DAT_01163cf8; // sentinel end marker
                }
            } else {
                // Index-based walk (bitmap)
                currentIndex++;
                if (currentIndex != totalBuckets) {
                    // Check bitmap to see if element exists in next slot
                    unsigned char* bitmap = (unsigned char*)bucketArray;
                    if ((bitmap[currentIndex >> 3] & (1 << (currentIndex & 7))) == 0) {
                        local_50 = local_5c;
                        local_48 = *(undefined4*)local_5c;
                        local_5c = (void*)((char*)local_5c + 4);
                    } else {
                        local_50 = nullptr;
                        local_48 = 0;
                    }
                }
            }
        }

        // Flush updates on global structures
        if (DAT_012069e4 != 0 && isValidPointer(&DAT_012069e4)) {
            _DAT_012069e8++;
            flushUpdate(&DAT_012069e4);
        }
        if (DAT_012069dc != 0 && isValidPointer(&DAT_012069dc)) {
            _DAT_012069e0++;
            flushUpdate(&DAT_012069dc);
        }

        // Ensure the linked list at +0x30 is properly maintained
        int* listHead = (int*)(this + 0x30);
        if (*listHead == 0) {
            int newHead = getFirstFromChain((void*)(this + 0x20));
            if (*listHead != newHead) {
                if (*listHead != 0) {
                    removeFromChain(listHead);
                }
                *listHead = newHead;
                if (newHead != 0) {
                    *(int*)(this + 0x34) = *(int*)(newHead + 4);
                    *(int**)(newHead + 4) = listHead;
                }
            }
        }
    }

    // Declare external global variables (from provided data)
    extern int DAT_012069e4; // pointer to something
    extern int _DAT_012069e8; // counter
    extern int DAT_012069dc; // another global
    extern int _DAT_012069e0; // counter

    // Sentinel address in data segment
    static const void* DAT_01163cf8 = (void*)0x01163cf8;
};