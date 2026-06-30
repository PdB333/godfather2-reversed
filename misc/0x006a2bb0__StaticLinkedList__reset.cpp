// FUNC_NAME: StaticLinkedList::reset
// Function address: 0x006a2bb0
// Role: Destroys all nodes in a static singly linked list (with sentinel head) and reinitializes list to empty with count=6.
// The function also zeroes the first field of the passed object (this pointer), acting as a constructor/initializer.

// Assumes a node structure with a 'next' pointer at offset 0.
// The linked list uses a sentinel trick: the head pointer itself acts as the dummy node.
// The global variables are static members of this class.

typedef struct StaticNode {
    StaticNode* next; // +0x00
    // Additional node data follows
} StaticNode;

class StaticLinkedList {
public:
    int field_0; // First field, set to 0 in reset()
    // Static list management globals (replacement for the global data at 0x00e50c80)
    static StaticNode* s_head;   // PTR_LOOP_00e50c80
    static StaticNode* s_tail;   // PTR_PTR_LOOP_00e50c84
    static int s_count;          // DAT_00e50c7c

    // Called to reset both the instance and the static list
    StaticLinkedList* reset() {
        this->field_0 = 0;

        // Destroy all nodes in the static linked list
        StaticNode* current = s_head;
        while (current != reinterpret_cast<StaticNode*>(&s_head)) { // sentinel: address of s_head
            StaticNode* next = current->next;
            destroyNode(current);  // FUN_009c8f10 - frees node resources
            current = next;
        }

        // Reinitialize sentinel: head and tail both point to the dummy (s_head's own address)
        s_head = reinterpret_cast<StaticNode*>(&s_head);
        s_tail = reinterpret_cast<StaticNode*>(&s_head);
        s_count = 6; // Reason unknown, possibly a default max capacity

        return this; // Constructors in MSVC often return this
    }

private:
    // Destructor for individual node (the callee FUN_009c8f10)
    static void destroyNode(StaticNode* node);
};