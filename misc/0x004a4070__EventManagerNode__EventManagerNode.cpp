// FUNC_NAME: EventManagerNode::EventManagerNode
// Location: 0x004a4070 - Constructor for a doubly-linked list node with an embedded dynamic event array
// The node holds a vtable pointer, some global data, and manages an array of events (each 0x10 bytes).
// It allocates memory for events and inserts itself into a global linked list.
// Called from two initialization functions (0x0046edb0, 0x0046ee30).

class EventManagerNode {
public:
    // Vtable pointer at offset +0x00
    // Next pointer at +0x04 (param_1[1])
    // Unknown value at +0x08 (param_1[2]) - from EAX (second parameter)
    // Global data pointer at +0x0C (param_1[3])
    // Various counters/pointers:
    // +0x10 (param_1[4]) - unknown
    // +0x34 (param_1[0xD]) - 0
    // +0x38 (param_1[0xE]) - 0
    // ... up to +0x94 (param_1[0x25]) - many zeros
    // Flags at +0x82 - set to 0x7FE
    // +0x20 (param_1[8]) - 0
    // +0x24 (param_1[9]) - 0
    // +0x28 (param_1[10]) - 0
    // +0x2C (param_1[0xB]) - 0
    // Array pointer at +0x68 (param_1[0x1A]) - points to allocated event storage
    // Count of events at +0x6C (param_1[0x1B])
    // Capacity of events at +0x70 (param_1[0x1C])
    // Previous linked list pointer at +0x8C (param_1[0x23])
    // Next linked list pointer at +0x90 (param_1[0x24]) - initially 0

    // Global linked list head (DAT_01205488) and tail (DAT_0120548C) are used
    static EventManagerNode* sm_listHead;   // DAT_01205488
    static EventManagerNode* sm_listTail;   // DAT_0120548C
    static int sm_someGlobalIndex;          // DAT_0120547C

    // Global pointer table (DAT_01163ffc) indexed by sm_someGlobalIndex
    static void* sm_globalDataTable[];      // DAT_01163ffc

    // Memory manager singleton (FUN_009c8f80)
    static MemoryManager* GetMemoryManager();

    // Allocator (FUN_00416980) returns allocator object from a block
    static Allocator* GetAllocatorFromBlock(void* block);

    // Resize event buffer (FUN_004a7bf0)
    static void* ResizeEventBuffer(int newCapacity);

    // Additional initialization (FUN_004a6110)
    static void AdditionalInitA();

    // Additional initialization (FUN_004a6a80)
    static void AdditionalInitB(int value);

    // Constructor: receives a value in EAX (likely an event type or ID)
    void __fastcall EventManagerNode(int eaxParam) {
        // Local variables for allocation info
        int allocSize = 0x70;                // Size of allocation block
        int subAllocSize = 2;                // local_18
        int subAllocAlignment = 0x10;        // local_14
        int subAllocFlags = 0;               // local_10

        // Set vtable pointer
        this->vtable = &_vtable_00e35378;    // param_1[0]
        this->field_4 = 0;                   // param_1[1]
        this->field_8 = eaxParam;            // param_1[2] = in_EAX

        // Fetch global data based on index
        int index = sm_someGlobalIndex;
        void* globalData = nullptr;
        if (index != 0) {
            globalData = sm_globalDataTable[index];
        }
        this->globalData = globalData;       // param_1[3]

        // Clear fields
        this->field_10 = 0;                  // param_1[4]
        this->field_34 = 0;                  // param_1[0xD]
        this->field_38 = 0;                  // param_1[0xE]
        this->field_3C = 0;                  // param_1[0xF]
        this->field_40 = 0;                  // param_1[0x10]
        this->field_44 = 0;                  // param_1[0x11]
        this->field_48 = 0;                  // param_1[0x12]
        this->field_4C = 0;                  // param_1[0x13]
        this->field_50 = 0;                  // param_1[0x14]
        this->field_54 = 0;                  // param_1[0x15]
        this->field_58 = 0;                  // param_1[0x16] as ushort
        this->field_5C = 0;                  // param_1[0x17]
        this->field_60 = 0;                  // param_1[0x18]
        this->field_64 = 0;                  // param_1[0x19]
        this->eventArray = nullptr;          // param_1[0x1A]
        this->eventCount = 0;                // param_1[0x1B]
        this->eventCapacity = 0;             // param_1[0x1C]
        this->field_74 = 0;                  // param_1[0x1D]
        this->field_78 = 0;                  // param_1[0x1E]
        this->field_7C = 0;                  // param_1[0x1F]
        this->field_80 = 0;                  // param_1[0x20]
        this->field_84 = 0;                  // param_1[0x21]
        this->field_88 = 0;                  // param_1[0x22]
        // Set flags at offset +0x82: clear bit0, set bits 1-10 (0x7FE)
        *(unsigned short*)((int)this + 0x82) &= 0xFFFE;
        *(unsigned short*)((int)this + 0x82) |= 0x7FE;
        // More zero fields
        this->field_2C = 0;                  // param_1[0xB]
        this->field_28 = 0;                  // param_1[10]
        this->field_24 = 0;                  // param_1[9]
        this->field_20 = 0;                  // param_1[8]

        // Allocate initial event storage
        MemoryManager* memMgr = GetMemoryManager();
        // Call virtual function on memory manager: alloc(0x70, &subAllocInfo)
        // subAllocInfo = { size=2, align=0x10, flags=0 }
        void* allocBlock = memMgr->Alloc(allocSize, &subAllocSize, &subAllocAlignment, &subAllocFlags);
        if (allocBlock != nullptr) {
            Allocator* allocator = GetAllocatorFromBlock(allocBlock);
            if (allocator != nullptr) {
                allocator->Initialize();      // Virtual call at offset 0x24 (vtable+0x24)
                // Check if we need to resize event buffer (first event allocation)
                int cap = this->eventCapacity;
                int cnt = this->eventCount;
                if (cnt == cap) {
                    int newCap;
                    if (cap == 0) {
                        newCap = 1;
                    } else {
                        newCap = cap * 2;
                    }
                    this->eventArray = ResizeEventBuffer(newCap);
                }
                // Add an event entry: each event is 0x10 bytes
                // eventArray is pointer to array of structures; eventCount is index
                Event* event = (Event*)(this->eventArray + this->eventCount * sizeof(Event)); // 0x10 = sizeof(Event)
                this->eventCount++;
                if (event != nullptr) {
                    // Build event: first qword = CONCAT26(uStack_1a, CONCAT24(3, allocator))
                    // uStack_1a and 3 are unknown; likely event type = 3 and allocator pointer
                    event->data1 = (allocator << 8) | 3;  // approximation
                    event->data2 = (subAllocFlags << 32) | subAllocSize; // based on local_14/local_18
                }
            }
        }

        // Additional initialization steps
        AdditionalInitA();
        AdditionalInitB(0);

        // Insert this node into global linked list
        EventManagerNode* tail = sm_listTail;          // DAT_0120548C
        if (tail != nullptr) {
            tail->next = this;                         // +0x90 (param_1[0x24])? Wait, offset 0x90 is param_1[0x24]
            // Actually param_1[0x24] is at +0x90, which we set to 0 later
            // The code does: *(undefined4 **)((int)DAT_0120548c + 0x90) = param_1;
            // So it sets the next pointer of the old tail to this.
            // But then DAT_01205488 = puVar2; where puVar2 started as param_1, then changed to DAT_01205488 if tail existed.
            // This logic is weird. Let's re-analyze:
            // Initially puVar2 = param_1.
            // If DAT_0120548c (tail) is not null:
            //   *(tail+0x90) = param_1;   // set tail's next to this
            //   puVar2 = DAT_01205488;    // puVar2 becomes old head
            // else: puVar2 stays as this (the new node)
            // Then DAT_01205488 = puVar2; // head becomes old head (if existed) or this
            // param_1[0x23] = DAT_0120548c; // this's previous = old tail
            // param_1[0x24] = 0;           // this's next = null
            // DAT_0120548c = param_1;      // tail becomes this
            // So it's a doubly linked list where head points to oldest, tail to newest.
        }
        // Simplified insertion:
        EventManagerNode* oldTail = sm_listTail;
        if (oldTail != nullptr) {
            oldTail->next = this;          // set next of old tail to this
        }
        // Set head of list (if list was empty, head is this; otherwise keep old head)
        sm_listHead = (oldTail != nullptr) ? sm_listHead : this;
        // Set previous pointer
        this->prev = oldTail;              // param_1[0x23]
        // Set next pointer to 0
        this->next = nullptr;              // param_1[0x24]
        // Update tail
        sm_listTail = this;

        return this;
    }

    // Member variables (guessed layout)
    void* vtable;                  // +0x00
    void* field_4;                 // +0x04
    int field_8;                   // +0x08 (eaxParam)
    void* globalData;              // +0x0C
    void* field_10;                // +0x10
    char pad_14[0x20];             // from +0x14 to +0x33 (zeros)
    int field_34;                  // +0x34
    int field_38;                  // +0x38
    int field_3C;                  // +0x3C
    int field_40;                  // +0x40
    int field_44;                  // +0x44
    int field_48;                  // +0x48
    int field_4C;                  // +0x4C
    int field_50;                  // +0x50
    int field_54;                  // +0x54
    short field_58;                // +0x58 (ushort)
    int field_5C;                  // +0x5C
    int field_60;                  // +0x60
    int field_64;                  // +0x64
    void* eventArray;              // +0x68  (pointer to array of Event, 16 bytes each)
    int eventCount;                // +0x6C
    int eventCapacity;             // +0x70
    int field_74;                  // +0x74
    int field_78;                  // +0x78
    int field_7C;                  // +0x7C
    int field_80;                  // +0x80
    int field_84;                  // +0x84
    int field_88;                  // +0x88
    // Flags at +0x82 (within field_80 or separate)
    EventManagerNode* prev;        // +0x8C (param_1[0x23])
    EventManagerNode* next;        // +0x90 (param_1[0x24])
};

// Event structure (size 0x10)
struct Event {
    uint64_t data1;  // first 8 bytes
    uint64_t data2;  // second 8 bytes
};