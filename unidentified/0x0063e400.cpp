// FUN_NAME: EventScheduler::processNextEvent
// Address: 0x0063e400
// Role: Processes the next scheduled event from the event queue, executing its action,
// optionally sending a message, and updating internal state counters.

// Event node structure (linked list node)
struct EventNode {
    EventNode* next;          // +0x00 next pointer in linked list
    uint32_t   unknown4;      // +0x04 (unused in this function)
    uint32_t   argument;      // +0x08 value encoded into message ID high byte
    uint32_t   callbackFlag;  // +0x0C nonzero if a message should be sent after processing
};

// Assumed class: EventScheduler
// Offsets used:
// +0x0C: pointer to an object that can receive messages (likely a component/entity)
// +0x14: head of event node linked list
// +0x18: field_18 (target value or time)
// +0x1C: field_1C (current value or time, updated from 0x18)
// +0x24: field_24 (some other value, updated from 0x34)
// +0x34: field_34 (next value, used to update 0x24)
void __thiscall EventScheduler::processNextEvent(void) {
    EventNode* node;  // popped event node

    node = this->eventHead;                             // pop head of event list
    this->eventHead = node->next;                       // remove from list

    FUN_0063df30();                                     // process the event (likely calls node's action)

    if (node->callbackFlag != 0) {
        // Build message ID: low byte 0x21, high byte from node argument
        uint32_t msgId = (node->argument << 24) | 0x21;
        // Send message to the object pointed by this->messageTarget (offset 0x0C), with value at offset 8 of that object
        uint32_t targetParam = *(uint32_t*)(this->messageTarget + 8);
        FUN_006438e0(msgId, targetParam);               // send message
    }

    // Update internal state fields (likely timers or counters)
    this->field_1C = this->field_18;                    // copy "target" to "current"
    this->field_24 = this->field_34;                    // copy another target

    FUN_00642880();                                     // final update (e.g., advance to next state)
}