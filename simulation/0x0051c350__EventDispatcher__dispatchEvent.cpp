// FUNC_NAME: EventDispatcher::dispatchEvent
// Address: 0x0051c350
// Dispatches an event to registered listeners. Iterates linked list of ListenerNode.
// A listener is triggered if:
//   - listener object is null AND eventId == -1 (matches all null listeners)
//   - listener object is non-null AND listener->getEventType() == eventId
// The actual firing is delegated to fireListener(ListenerNode*).

// Global head of listener node list
ListenerNode* g_listenerListHead; // DAT_01205514

// ListenerNode structure
struct ListenerNode {
    ListenerNode* pNext;       // +0x14
    IListener* pListener;      // +0x20 (can be null)
    // Other fields not used here
};

// Interface for event listeners
struct IListener {
    virtual int getEventType(); // vtable+0xc, returns event type identifier
};

// Forward declaration of the fire function (implemented elsewhere)
void fireListener(ListenerNode* pNode); // FUN_0051bc80

void EventDispatcher::dispatchEvent(int eventId) { // eventId passed in EDI
    ListenerNode* pNode = g_listenerListHead;

    if (pNode != nullptr) {
        do {
            bool bMatch = false;
            if (pNode->pListener == nullptr) {
                // Null listener matches only if eventId is -1
                bMatch = (eventId == -1);
            } else {
                // Non-null listener: compare its event type with eventId
                int listenerType = pNode->pListener->getEventType();
                bMatch = (listenerType == eventId);
            }

            if (bMatch) {
                fireListener(pNode);
            }

            pNode = pNode->pNext;
        } while (pNode != nullptr);
    }
}