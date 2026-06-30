// FUNC_NAME: SimNpc::~SimNpc
// Function address: 0x005231b0
// Role: Destructor for SimNpc or base entity class. Unlinks the object from 7 singly-linked lists (registration lists) and updates vtable pointers.
// The object contains pairs of (list head pointer, node's next pointer) at offsets: (0x458/0x45C), then pairs at 0x3B0/0x3B4, 0x310/0x314, 0x270/0x274, 0x1D0/0x1D4, 0x130/0x134, 0x90/0x94.

class SimNpc {
public:
    // VTable pointer (offset 0x00)
    int* vtable;

    // Offsets of list head and next pointers (in bytes)
    // First list: head at +0x458, next at +0x45C
    int* list1Head; // +0x458 (0x116 * 4)
    int list1Next;  // +0x45C (0x117 * 4)

    // Remaining 6 lists: each has a pair (head, next) stored consecutively
    // +0x3B0: head2, +0x3B4: next2
    // +0x310: head3, +0x314: next3
    // +0x270: head4, +0x274: next4
    // +0x1D0: head5, +0x1D4: next5
    // +0x130: head6, +0x134: next6
    // +0x90:  head7, +0x94:  next7

    void __thiscall ~SimNpc(); // destructor
};

void SimNpc::~SimNpc() {
    // Set vtable to derived class (ensures correct virtual dispatch during destruction)
    this->vtable = (int*)0x00e38350; // PTR_FUN_00e38350

    // --- Unlink from first list ---
    int* head1 = this->list1Head; // +0x458
    if (head1 != nullptr) {
        int* head1Next = (int*)head1[1]; // head->next (offset 4 from head)
        if (head1Next == this) {
            head1[1] = this->list1Next; // set head->next = this->next
        } else {
            int* prev = (int*)head1Next[1];
            while (prev != this) {
                head1Next = (int*)head1Next[1];
                prev = (int*)head1Next[1];
            }
            head1Next[1] = this->list1Next;
        }
    }

    // --- Unlink from remaining 6 lists ---
    // The pairs are stored at decreasing offsets: 0x3B0/0x3B4, 0x310/0x314, 0x270/0x274, 0x1D0/0x1D4, 0x130/0x134, 0x90/0x94
    // Iterate starting from the highest offset downwards.
    int pairs[6][2] = {
        {0x3B0, 0x3B4},
        {0x310, 0x314},
        {0x270, 0x274},
        {0x1D0, 0x1D4},
        {0x130, 0x134},
        {0x90, 0x94}
    };

    for (int i = 0; i < 6; i++) {
        int* headPtr = (int*)((char*)this + pairs[i][0]);
        int* nextPtr = (int*)((char*)this + pairs[i][1]); // address of this->next for this list
        int* head = *headPtr; // list head pointer
        if (head != nullptr) {
            int* headNext = (int*)head[1]; // head->next (offset 4)
            if (headNext == this) {
                head[1] = *nextPtr; // set head->next = this->next
            } else {
                int* prev = (int*)headNext[1];
                while (prev != this) {
                    headNext = (int*)headNext[1];
                    prev = (int*)headNext[1];
                }
                headNext[1] = *nextPtr;
            }
        }
    }

    // Set vtable to base class (indicates object is partially destroyed)
    this->vtable = (int*)0x00e38340; // PTR_LAB_00e38340
}