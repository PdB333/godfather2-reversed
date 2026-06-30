// FUNC_NAME: MemoryPool::initialize
class MemoryPool {
public:
    // vtable pointer at +0x00
    // +0x04: block1 pointer (array of structs of size 0x10 each)
    // +0x08: block2 pointer
    // +0x0c: block3 pointer
    // +0x10: block4 pointer (or some field, stored from in_EAX)
    // +0x14: freeList pointer (or list head)
    // +0x18: some byte flags? Actually at +0x19 and +0x1a
    // +0x1c: allocated block for lookup
    // +0x20: some counters
    // +0x24: 
    // +0x28: linked list header / array
    // +0x2c: 
    // +0x30: capacity value
    // +0x34: element size (param_1)
    // +0x38: something
    // +0x650: something
    // +0x654: something
};

// Global constant used to initialize elements
extern unsigned int g_initialValue; // DAT_00e2eff4

void __thiscall MemoryPool::initialize(int elementSize, bool useFreeList)
{
    // in_EAX is passed as this->field at +0x10
    this->fieldAt0x10 = /*some return from caller?*/; // actually set from in_EAX in the assembly

    // Base class pointer or inheritance
    if (basePointer == nullptr) { // unaff_EDI = this->vtable? Actually this is the base class pointer
        // First time allocation: allocate a new base object via FUN_009c89b0
        basePointer = FUN_009c89b0(); // likely a singleton allocator
    }
    // this->base = basePointer;
    this->base = basePointer; // *unaff_ESI = unaff_EDI

    this->useFreeListFlag = useFreeList; // +0x0f

    this->elementSize = elementSize; // +0x34

    // Allocate first block: size = (elementSize * 0x10 + 0x7f) & 0xffffff80
    this->block1 = (Block1Entry*)((*(code**)this->base)[0])( ((elementSize * 0x10) + 0x7f) & 0xffffff80 ); // +0x04
    // Allocate second block: size = (elementSize + 0x7f) & 0xffffff80
    this->block2 = (Block2Entry*)((*(code**)this->base)[0])( (elementSize + 0x7f) & 0xffffff80 ); // +0x08
    // Allocate third block: size = (elementSize * 2 + 0x7f) & 0xffffff80
    this->block3 = (Block3Entry*)((*(code**)this->base)[0])( (elementSize * 2 + 0x7f) & 0xffffff80 ); // +0x0c
    // Allocate fourth block: size = (elementSize * 0x20 + 0x7f) & 0xffffff80
    this->block4 = (Block4Entry*)((*(code**)this->base)[0])( (elementSize * 0x20 + 0x7f) & 0xffffff80 ); // +0x10

    if (!useFreeList) {
        // No free list: zero out relevant fields
        this->freeListHeader = nullptr; // +0x28
        this->freeListCapacity = 0;      // +0x30
        this->freeListCount = 0;         // +0x2c
        this->freeListHead = nullptr;    // +0x14
    } else {
        // Initialize free list
        int capacity = elementSize / 5 + elementSize; // approximate number of blocks
        this->freeListCapacity = capacity; // +0x30
        // Allocate linked list of BlockLink nodes (size = capacity * 0x10 + 0x83 & 0xffffff80)
        BlockLink* list = (BlockLink*)((*(code**)this->base)[0])( (capacity * 0x10 + 0x83u) & 0xffffff80 );
        this->freeListHeader = list; // +0x28
        list->next = nullptr; // first node next = 0
        this->freeList = &list[1]; // +0x2c points to second node? Actually +4 from list start
        // Initialize linked list of free nodes
        for (int i = 1; i < capacity; i++) {
            this->freeList[i-1].next = &this->freeList[i];
        }
        this->freeList[capacity-1].next = nullptr; // last node next = 0

        // Allocate additional block for free list pointers? size = (elementSize * 2 + 0x7f) & 0xffffff80
        this->freeListAlloc = (int*)((*(code**)this->base)[0])( (elementSize * 2 + 0x7f) & 0xffffff80 ); // +0x14
    }

    *(short*)((int)this + 0x1a) = 0; // some short flag

    // Allocate another block: size = (elementSize * 2 + 0x7f) & 0xffffff80
    this->someBlock = (int*)((*(code**)this->base)[0])( (elementSize * 2 + 0x7f) & 0xffffff80 ); // +0x1c

    this->counter1 = 0; // +0x20
    this->counter2 = 0; // +0x24

    // Initialize block1 entries with a global constant
    for (int i = 0; i < elementSize; i++) {
        this->block1[i].someField = g_initialValue; // DAT_00e2eff4
    }

    this->someFlag = 0;       // +0x38
    this->largeField1 = 0;    // +0x650
    this->largeField2 = 0;    // +0x654
    *(char*)((int)this + 6) = 0; // +0x06
    *(char*)((int)this + 0x19) = 0; // +0x19
}