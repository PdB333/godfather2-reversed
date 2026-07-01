// FUNC_NAME: EventNode::EventNode
class EventNode {
public:
    // +0x00: vtable pointer
    // +0x04: param3 (value1)
    // +0x08: param5 (value3)
    // +0x0C: param4 (value2)
    // +0x10: field0 (unused)
    // +0x14: field1 (unused)
    // +0x18: field2 (unused)
    // +0x1C: field3 (unused)
    // +0x20: name[64] (0x3F chars + null)
    // +0x60: padding? (16 bytes)
    // +0x70: next pointer (linked list)
    
    void *vtable;              // 0x00
    int paramValue1;           // 0x04
    int paramValue3;           // 0x08
    int paramValue2;           // 0x0C
    int unused0;               // 0x10
    int unused1;               // 0x14
    int unused2;               // 0x18
    int unused3;               // 0x1C
    char name[64];             // 0x20
    // padding of 16 bytes at 0x60
    EventNode *next;           // 0x70
};

static EventNode *g_headEventNode = nullptr; // Likely global head pointer

EventNode * __thiscall EventNode::EventNode(EventNode *this, const char *eventName, int arg3, int arg4, int arg5) {
    // Call base class constructor or initializer
    callBaseConstructor();
    
    this->vtable = (void*)0x00d79bb0; // VTable pointer for this class
    
    // Copy event name (max 63 chars)
    strncpy(this->name, eventName, 0x3F);
    
    this->paramValue1 = arg3;
    this->paramValue2 = arg4;
    this->paramValue3 = arg5;
    
    // Initialize unused fields to 0
    this->unused0 = 0;
    this->unused1 = 0;
    this->unused2 = 0;
    this->unused3 = 0;
    
    // Link into global event chain (insert at head)
    this->next = g_headEventNode;
    g_headEventNode = this;
    
    return this;
}