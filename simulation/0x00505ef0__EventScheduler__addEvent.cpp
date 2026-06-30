// FUNC_NAME: EventScheduler::addEvent
// Address: 0x00505ef0
// This function adds an event node to a global event queue manager.
// It takes two float parameters (presumably time-related) and four other parameters.
// The queue is organized as a singly linked list with head pointer and count stored in a manager structure.

struct EventNode {
    EventNode* next;      // +0x00
    float timeStart;      // +0x04  (in_XMM0)
    int eventType;        // +0x08  (param_1)
    int param2;           // +0x0C  (param_2)
    int param3;           // +0x10  (param_3)
    float duration;       // +0x14  (min of in_XMM1 and a global constant)
    int param4;           // +0x18  (param_4)
};

// Global constant (DAT_00e446d8)
extern float g_maxDuration;

// Queue manager structure (returned by sub-function)
struct EventQueueManager {
    EventNode* head;      // +0x00
    // padding? (offset 4-11 unknown)
    int count;            // +0x0C
};

// Global pool pointer (DAT_0120550c)
extern void* g_eventPool;

// Forward declaration of sub-function that returns a pointer to the queue manager
// for a given pool. It may also allocate a new node from the pool.
EventQueueManager* getQueueManager(void* pool);

void __thiscall EventScheduler::addEvent(float timeStart, float duration, int eventType, int param2, int param3, int param4) {
    // Get the queue manager from the global pool
    EventQueueManager* queueMgr = getQueueManager(g_eventPool);
    
    // The new node is placed at the head of the list. The node's memory is assumed to be
    // allocated elsewhere (probably by getQueueManager or a separate allocation).
    // 'this' pointer (in ESI) points to the new node.
    EventNode* newNode = this;
    
    newNode->timeStart = timeStart;
    newNode->eventType = eventType;
    
    // Clamp duration to the global maximum
    float actualDuration = g_maxDuration;
    if (duration <= g_maxDuration) {
        actualDuration = duration;
    }
    newNode->duration = actualDuration;
    newNode->param4 = param4;
    newNode->param2 = param2;
    newNode->param3 = param3;
    
    // Insert at head: new node's next = old head
    newNode->next = queueMgr->head;
    // Increment count
    queueMgr->count++;
    // Update head to new node
    queueMgr->head = newNode;
}