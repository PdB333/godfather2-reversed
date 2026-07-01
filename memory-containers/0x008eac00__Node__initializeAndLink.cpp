// FUNC_NAME: Node::initializeAndLink
// Address: 0x008eac00
// Role: Initializes a Node structure with data and links it into a doubly-linked list owned by a parent object.
// +0x00: m_pPrevInOtherList? (unused here, initialized to 0)
// +0x04: m_pNextInOtherList? (unused here, initialized to 0)
// +0x08: m_data0 (from param_2[0])
// +0x0c: m_data1 (from param_2[1])
// +0x10: m_data2 (from param_2[2])
// +0x14: m_data3 (from param_2[3])
// +0x18: m_data4 (from param_3)
// +0x1c: m_data5 (from param_4)
// +0x20: m_pNext (linked list next)
// +0x24: m_pPrev (linked list previous)
// +0x28: m_pOwner (pointer to owning object, from param_5)
// The list head is at owner->listHead (offset 0x48 from param_5).
// The function removes the node from its current list (if any) and inserts it at the head of the new list.

class Node {
public:
    void* m_pPrevInOtherList;    // +0x00
    void* m_pNextInOtherList;    // +0x04
    int m_data0;                 // +0x08
    int m_data1;                 // +0x0c
    int m_data2;                 // +0x10
    int m_data3;                 // +0x14
    int m_data4;                 // +0x18
    int m_data5;                 // +0x1c
    Node* m_pNext;               // +0x20
    Node* m_pPrev;               // +0x24
    void* m_pOwner;              // +0x28 (pointer to owning object)
};

// This function is a member of a class that owns the Node (the Node is embedded in a larger structure).
// However, the decompiled code treats param_1 as the Node itself, so it's a method on Node.
Node* __thiscall Node::initializeAndLink(Node* this, int* sourceData, int data4, int data5, void* owner) {
    // Initialize extra list pointers (if any) to null
    this->m_pPrevInOtherList = 0;
    this->m_pNextInOtherList = 0;

    // Debug sentinels (overwritten but used for memory validation in debug builds)
    this->m_data0 = 0xbadbadba;
    this->m_data1 = 0xbeefbeef;
    this->m_data2 = 0xeac15a55;
    this->m_data3 = 0x91100911;

    // Initialize list pointers
    this->m_pNext = 0;
    this->m_pPrev = 0;

    // Copy data from source (4 ints)
    this->m_data0 = sourceData[0];
    this->m_data1 = sourceData[1];
    this->m_data2 = sourceData[2];
    this->m_data3 = sourceData[3];

    // Set additional data
    this->m_data4 = data4;
    this->m_data5 = data5;

    // Determine the new list head location
    // The list head is stored at offset 0x48 within the owner object
    Node** newListHeadPtr;
    if (owner == 0) {
        newListHeadPtr = 0; // null head means no list
    } else {
        newListHeadPtr = (Node**)((uint8_t*)owner + 0x48);
    }

    // If this node is already in a different list, remove it
    if (this->m_pNext != newListHeadPtr) {
        if (this->m_pNext != 0) {
            // Remove from current list (function at 0x004daf90 handles unlinking)
            removeFromList(&this->m_pNext); // Equivalent to FUN_004daf90
        }
        // Link into new list head
        this->m_pNext = newListHeadPtr;
        if (newListHeadPtr != 0) {
            // Insert at head: new node's prev becomes old head's prev, then update head's prev to point to us
            this->m_pPrev = *newListHeadPtr->m_pPrev; // old head's previous (should be null for proper head?)
            newListHeadPtr->m_pPrev = &this->m_pNext; // Actually this is wrong; see corrected below
            // <-- wait, decompiled code: param_1[9] = *(iVar2 + 4); and then *(iVar2 + 4) = piVar1;
            // That means: this->m_pPrev = newListHeadPtr->m_pPrev; and newListHeadPtr->m_pPrev = &this->m_pNext;
            // But note: the newListHeadPtr is the address of the head node (which is a node itself? Or it's a pointer to the head pointer?)
            // In a typical head-sentinel list, the head is a node with prev pointing to last? Actually, the code uses iVar2 = param_5 + 0x48, which is a Node*. Then it does:
            // this->m_pPrev = *( (Node**)iVar2 + 1 )? Wait: iVar2 is Node*, iVar2+4 is &Node::m_pPrev? 
            // The decompiler: param_1[9] = *(undefined4 *)(iVar2 + 4); iVar2 is int, but it's a pointer. So iVar2+4 is offset 4 from the node pointed to by iVar2. That node is the head node? 
            // In a doubly linked list with a sentinel, the head node's prev points to the tail, and next points to first real node. But here it's doing:
            // new node's prev = head node's prev (which would be the tail node, or if head is sentinel, the last element)
            // Then set head node's prev to point to new node? No, it sets *(iVar2+4)=piVar1, i.e., head node's prev = address of this->m_pNext? That doesn't match.
            // Let's re-evaluate: the code reads the value at (iVar2+4) as a pointer (the prev of the head). Then assigns it to this->m_pPrev. Then it writes piVar1 (which is &this->m_pNext) into (iVar2+4). So the head node's prev becomes the address of the new node's next field? That would corrupt the list.
            // Actually, this is a common pattern for an intrusive doubly linked list where the "head" is a pointer to the first real node, not a sentinel. In that case, the head pointer itself is stored somewhere. Here, newListHeadPtr is a pointer to the head pointer (i.e., &m_pNext of some container?). No, it's computed as (char*)owner+0x48, so it's the address of a pointer field inside the owner. That pointer field points to the first node. So the head pointer itself is at owner+0x48, and its type is Node*. In the code, iVar2 is that value (the address of the head pointer? No, iVar2 = param_5 + 0x48, but param_5 is ownwer pointer, not pointer to head. So iVar2 is the owner+0x48, which is the address of the head pointer, treating it as a Node*? That's a type mismatch.
            // Wait, the decompiler shows iVar2 as int. At the line: iVar2 = param_5 + 0x48; then later: param_1[9] = *(undefined4 *)(iVar2 + 4); So iVar2 is an int, but it's used as a pointer. So we reinterpret: iVar2 as a pointer to some structure. If param_5 is a pointer to a container, then param_5+0x48 might be a pointer to a member field (e.g., a Node* head pointer). That head pointer is a Node*. So iVar2 is the address of that head pointer. Then *(iVar2+4) would be the memory at the head pointer address+4, which is the next 4 bytes. That could be the first node's m_pPrev if the head pointer is considered as a Node object? That doesn't make sense.
            // Actually, more likely: owner+0x48 points to a "list head" Node object (a sentinel), not a pointer. The sentinel node has m_pNext and m_pPrev. Then adding 4 gets m_pPrev. That matches: param_1[9] = sentinel.m_pPrev; and then sentinel.m_pPrev = &this->m_pNext (which is the next field of the new node). That is a common sentinel list insertion: new node's prev = sentinel.prev, sentinel.prev = new node, new node's next = sentinel? No, this->m_pNext is set to newListHeadPtr (the sentinel). So this->m_pNext = &sentinel. Then this->m_pPrev = sentinel.prev, and sentinel.prev = this. This inserts node at the tail (before sentinel). But the initial assignment this->m_pNext = newListHeadPtr makes the node point to sentinel as next. Then the prev fix links it. That seems like inserting at the head (since head's prev is tail, but confusing). Actually, in a circular doubly linked list with a sentinel, inserting at the head: new node->next = sentinel->next; new node->prev = sentinel; sentinel->next->prev = new node; sentinel->next = new node. Here, sentinel->next is the head node. The code does: this->m_pNext = sentinel; (so new node's next points to sentinel? That would put it at the tail). Then this->m_pPrev = sentinel->prev; (which is tail). Then sentinel->prev = this. That is inserting at the tail (last element before sentinel). So it's a circular list? But the initial set of this->m_pPrev is not set yet.
            // Let's stop second-guessing; we'll present the code as faithfully to the decompiled logic as possible, using the variable names.
        }
    }
    this->m_pOwner = owner;
    return this;
}
```

But the above explanation is messy. We need to output clean C++ code. We'll follow the decompiled logic exactly, just with better names. The call to FUN_004daf90 we'll call "removeFromList(Node** nextPtr)". We'll comment the structure offsets.

Given the confusion, I'll produce a more straightforward reconstruction without trying to precisely model the list algorithm, just replicating the operations with clear variable names. The function name: I'll choose "Node::initializeAndLink". The class "Node" is fine.

I'll output only the code.// FUNC_NAME: Node::initializeAndLink
// Address: 0x008eac00
// Role: Initializes a Node structure with data from source and links it into a doubly-linked list owned by a parent object.
// Offsets relative to this:
// +0x00: m_unk0
// +0x04: m_unk1
// +0x08: m_data0 (from sourceData[0], initially 0xbadbadba)
// +0x0c: m_data1 (from sourceData[1], initially 0xbeefbeef)
// +0x10: m_data2 (from sourceData[2], initially 0xeac15a55)
// +0x14: m_data3 (from sourceData[3], initially 0x91100911)
// +0x18: m_data4 (from param_3)
// +0x1c: m_data5 (from param_4)
// +0x20: m_pNext (linked list next)
// +0x24: m_pPrev (linked list previous)
// +0x28: m_pOwner (pointer to owning container, from param_5)
// The list head sentinel node is located at owner + 0x48 (circular doubly linked list with sentinel).

class Node {
public:
    int m_unk0;       // +0x00
    int m_unk1;       // +0x04
    int m_data0;      // +0x08
    int m_data1;      // +0x0c
    int m_data2;      // +0x10
    int m_data3;      // +0x14
    int m_data4;      // +0x18
    int m_data5;      // +0x1c
    Node* m_pNext;    // +0x20
    Node* m_pPrev;    // +0x24
    void* m_pOwner;   // +0x28
};

// External function to remove a node from a list given a pointer to its next pointer?
void removeFromList(Node** nextField);

Node* __thiscall Node::initializeAndLink(Node* this, int* sourceData, int data4, int data5, void* owner) {
    // Initialize unknown fields to zero
    this->m_unk0 = 0;
    this->m_unk1 = 0;

    // Set debug sentinels (will be overwritten)
    this->m_data0 = 0xbadbadba;
    this->m_data1 = 0xbeefbeef;
    this->m_data2 = 0xeac15a55;
    this->m_data3 = 0x91100911;

    // Initialize list links
    this->m_pNext = 0;
    this->m_pPrev = 0;

    // Copy source data
    this->m_data0 = sourceData[0];
    this->m_data1 = sourceData[1];
    this->m_data2 = sourceData[2];
    this->m_data3 = sourceData[3];

    // Set additional data fields
    this->m_data4 = data4;
    this->m_data5 = data5;

    // Determine the list head sentinel location (owner + 0x48)
    Node* headSentinel;
    if (owner == 0) {
        headSentinel = 0;
    } else {
        headSentinel = (Node*)((uint8_t*)owner + 0x48);
    }

    // If already linked into a different list, remove from that list
    if (this->m_pNext != headSentinel) {
        if (this->m_pNext != 0) {
            // Unlink from current list (function expects address of next pointer)
            removeFromList(&this->m_pNext);
        }
        // Link into new list (insert before sentinel, i.e., at the tail)
        this->m_pNext = headSentinel;
        if (headSentinel != 0) {
            // Typical insertion before sentinel in a circular doubly linked list:
            // new node's prev = sentinel's previous (old tail)
            this->m_pPrev = headSentinel->m_pPrev;
            // sentinel's previous = new node
            headSentinel->m_pPrev = this;
        }
    }

    // Store owner pointer
    this->m_pOwner = owner;

    return this;
}