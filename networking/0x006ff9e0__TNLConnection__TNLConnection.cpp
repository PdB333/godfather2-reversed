// FUNC_NAME: TNLConnection::TNLConnection
// Address: 0x006ff9e0
// Constructor for a network connection object. Initializes packet window slots with sentinel values,
// sets sequence counters, and registers this connection into the global NetSession's connection list.

class TNLConnection : public TNLBase {
public:
    // Offset: +0x00 vtable pointer
    // Offset: +0x3c = param_1[0xf]  (ptr to virtual table extension?)
    // Offset: +0x48 = param_1[0x12] (another vtable?)
    // Offset: +0x50 = param_1[0x14] -> sequenceNumber?
    // Offset: +0x54 = param_1[0x15] -> ackSequence?
    // Offset: +0x58 to +0xD8 (0x80 bytes) = packetWindowSlots[8]  (each slot 16 bytes)
    //   Slot structure: { uint32 magic1; uint32 magic2; uint32 magic3; uint32 magic4; }
    // Offset: +0xD8 = param_1[0x36] .. +0xFC = param_1[0x3f] : zeroed
    // Offset: +0xFC = param_1[0x3f] -> something from global
    // Offset: +0x100 = param_1[0x40] -> something from global

    TNLConnection(TNLBase* baseParam);  // baseParam passed to base constructor

    // Global: g_netSessionManager (DAT_01129980) points to a singleton of NetSessionManager
    extern NetSessionManager* g_netSessionManager;
    extern uint32 g_unknownGlobal;  // _DAT_00d5780c
    extern void* g_vtable1;        // PTR_DAT_00d60cac
    extern void* g_vtable2;        // PTR_DAT_00d60c9c
    extern void* g_vtable3;        // PTR_DAT_00d60c98

private:
    // Internal method used to initialize the connection (FUN_006ff8f0)
    void initializeSelf();
};

// Constructor implementation
TNLConnection::TNLConnection(TNLBase* baseParam)
{
    // Call base class constructor (TNLBase::TNLBase)
    TNLBase::TNLBase(baseParam);

    // Set up vtable pointers
    this->vtable = g_vtable1;                // +0x00
    *(void**)((char*)this + 0x3c) = g_vtable2;  // param_1[0xf]
    *(void**)((char*)this + 0x48) = g_vtable3;  // param_1[0x12]

    uint32 globalVal = _DAT_00d5780c; // Some global initialization value

    // Initialize packet window slots (8 slots, each 16 bytes)
    // Slot indices: 0 to 7
    for (int slot = 0; slot < 8; ++slot)
    {
        uint32* slotBase = &((uint32*)this)[0x16 + slot * 4];  // each slot: 4 consecutive uint32s
        slotBase[0] = 0xbadbadba;   // magic1
        slotBase[1] = 0xbeefbeef;   // magic2
        slotBase[2] = 0xeac15a55;   // magic3
        slotBase[3] = 0x91100911;   // magic4
    }

    // Set sequence counters
    ((uint32*)this)[0x14] = 2;   // +0x50: sequence number? (starting at 2)
    ((uint32*)this)[0x15] = 1;   // +0x54: acknowledgement sequence? (starting at 1)

    // Zero out fields from +0xD8 to +0xFB (9 words)
    for (int i = 0x36; i <= 0x3e; ++i)
        ((uint32*)this)[i] = 0;

    // Set two fields from globalVal
    ((uint32*)this)[0x3f] = globalVal;  // +0xFC
    ((uint32*)this)[0x40] = globalVal;  // +0x100

    // Get the NetSessionManager singleton
    NetSessionManager* sessionMgr = g_netSessionManager;
    int* headPtr = (int*)((char*)sessionMgr + 0x10);  // offset 0x10: pointer to linked list head
    int* tailPtr = (int*)((char*)sessionMgr + 0x14);  // offset 0x14: pointer to linked list tail (or first element)
    int* countPtr = (int*)((char*)sessionMgr + 0x18); // offset 0x18: connection count

    // Initialize this connection's local state
    initializeSelf();  // FU: 006ff8f0

    // Allocate a node for the connection list
    void* allocFunc = *(void**)((char*)sessionMgr + 0x20); // a function pointer (malloc-like)
    Node* newNode = (Node*)((int (*)(int, void*))allocFunc)(12, *(void**)((char*)sessionMgr + 0x1c));
    if (newNode == nullptr)
    {
        // Fallback allocation pool
        newNode = (Node*)&DAT_01218a14;
    }

    newNode->connection = this;   // node[0] = this
    newNode->next = nullptr;      // node[1] = 0
    newNode->prev = nullptr;      // node[2] = 0

    // Insert node at head of the list (simple linked list)
    newNode->prev = (Node*)(*headPtr);  // node[1] = *headPtr
    if (*headPtr != 0)
    {
        ((Node**)(*headPtr))->next = newNode;  // head->prev->next = newNode
    }
    *headPtr = (int)newNode;

    // If the list was empty, set tail to this node
    if (*tailPtr == 0)
    {
        *tailPtr = (int)newNode;
    }

    // Increment connection count
    (*countPtr)++;
}