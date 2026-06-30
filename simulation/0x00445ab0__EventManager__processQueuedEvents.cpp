// FUNC_NAME: EventManager::processQueuedEvents
// Address: 0x00445ab0
// This function processes a queue of events (stored in global arrays) by looking up handlers in a hash table keyed by g_contextId.
// It appears to be part of the EA EARS engine event dispatching system.

// Global variables (from data section)
extern int g_eventQueueCount;                        // DAT_01223434
extern int* g_eventQueueIds;                         // DAT_01226690 (array of event IDs, stride 2 ints each)
extern unsigned char* g_eventQueueTypes;              // DAT_01226694 (array of event types, stride 8 bytes each)
extern int* g_hashTableBase;                          // DAT_01162380 (base of hash table buckets, 0x1000 entries)
extern int g_contextId;                               // DAT_0120e93c (context ID used as hash key)

// Forward declaration of helper function (FUN_00408cf0)
extern void eventQueueCleanup(void);

// Event structure used as parameter for dispatched callbacks
struct EventCallbackData {
    int contextId;          // +0x00
    int someZero;           // +0x04
    unsigned char flag;     // +0x08
};

// Main function
void __fastcall EventManager::processQueuedEvents(void* thisPtr, unsigned char eventType, int* eventQueueItem, int eventId)
{
    int* bucketEntry;
    int* currentNode;
    int* subListNode;
    int nextSubListNode;
    unsigned int idx;
    int counter;
    bool loopAgain;
    unsigned int local_index;
    EventCallbackData callbackData;

    // Store the event in the global queue arrays
    int slot = g_eventQueueCount;
    g_eventQueueCount = g_eventQueueCount + 1;
    g_eventQueueIds[slot * 2] = eventId;
    g_eventQueueTypes[slot * 8] = eventType;

    if (g_eventQueueCount < 2) {
        local_index = 0;
        if (g_eventQueueCount != 0) {
            do {
                // Mark the event queue item as "processing" and store the event data
                *(unsigned char*)(eventQueueItem + 0x3c) = 1;   // +0x3c processing flag
                *(int*)(eventQueueItem + 0x40) = *eventQueueItem; // +0x40 copy first field

                // Hash table lookup using g_contextId
                bucketEntry = (int*)(g_hashTableBase + ((unsigned int)g_contextId & 0xFFF));
                currentNode = (int*)*bucketEntry;
                while (currentNode != 0) {
                    if (currentNode[4] != g_contextId) { // +0x10 is key
                        // Follow linked list (next node is at +0x00)
                        currentNode = (int*)*currentNode;
                        if (currentNode == 0) break;
                    } else {
                        break;
                    }
                }

                if (currentNode != 0) {
                    // Find matching node in bucket again (for setting flag)
                    int* nodeInBucket = (int*)*bucketEntry;
                    while (nodeInBucket != 0 && nodeInBucket[4] != g_contextId) {
                        nodeInBucket = (int*)*nodeInBucket;
                    }
                    if (nodeInBucket != 0) {
                        // Set bit 0 at offset +0x16 (likely a "pending" flag)
                        *(unsigned short*)((int)nodeInBucket + 0x16) |= 1;
                    }

                    // Prepare callback data
                    callbackData.contextId = g_contextId;
                    callbackData.someZero = 0;
                    callbackData.flag = 1;

                    // Follow the sub-list from currentNode[2] (offset +0x08)
                    subListNode = (int*)currentNode[2];
                    if (subListNode == 0) {
                        // Fallback: try next node in bucket
                        if (currentNode != 0 && (int*)*currentNode != 0) {
                            subListNode = (int*)((int*)*currentNode)[2];
                        }
                    }

                    // Iterate through the sub-list
                    while (subListNode != 0) {
                        // Check if subListNode has flags at +0x14 and a pointer at +0x0c
                        if ( (*(unsigned short*)((int)subListNode + 0x14) & 0x8000) == 0 ) {
                            int* handlerNode = *(int**)((int)subListNode + 0xC); // +0x0c pointer to handler
                            if (handlerNode != 0 && (((unsigned char*)handlerNode)[1] & 1) != 0) {
                                int* targetNode = 0;
                                if ( (handlerNode[1] & 0x10) != 0 ) {
                                    targetNode = handlerNode - 0xF; // offset -0x3c from handlerNode
                                } else if ( (handlerNode[1] & 0x20) != 0 ) {
                                    targetNode = (int*)handlerNode[3]; // offset +0x0c from handlerNode
                                }
                                if (targetNode != 0) {
                                    // Check conditions: eventType flag or target flags, and eventId match
                                    if ( eventType == 0 || (((unsigned int)targetNode[5] >> 0x1A) & 1) != 0 ) {
                                        if ( targetNode[7] == eventId ) {
                                            // Call the handler function (vtable entry at +0x04)
                                            void (*handlerFunc)(EventCallbackData*) = (void (*)(EventCallbackData*))(*(int*)handlerNode)[1];
                                            handlerFunc(&callbackData);
                                        }
                                    }
                                }
                            }
                        }
                        // Move to next sub-list node (stored at +0x04)
                        nextSubListNode = *(int*)((int)subListNode + 4);
                        subListNode = (int*)nextSubListNode;
                    }
                    eventQueueCleanup();
                }

                // Reset event queue item flags
                *(unsigned char*)(eventQueueItem + 0x3c) = 0;
                *(int*)(eventQueueItem + 0x40) = 0;
                eventQueueItem += 2; // advance to next event
                local_index++;
                loopAgain = local_index < (unsigned int)g_eventQueueCount;
            } while (loopAgain);
        }
        g_eventQueueCount = 0;
    }
}