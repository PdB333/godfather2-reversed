// FUNC_NAME: SomeManager::updateListFlags
// Address: 0x005dc900
// Role: Iterates over a circular linked list of objects and sets a flag at offset 0x298 based on a comparison with a value from FUN_005dc670.
// The list is stored as a container at this+8, with head pointer at container+0x1c.
// Each list node has data pointer at +0x10 and next pointer at +0x1c.
// The flag at object+0x298 is set to 0 if param_2 is zero, or to 1 if param_2 is non-zero and object+0x299 is zero.
// The loop uses FUN_005e09e0 to advance the iterator (likely a member or global iterator).

struct ListNode {
    int field_0x00; // unknown
    int field_0x04;
    int field_0x08;
    int field_0x0c;
    void* data; // +0x10
    int field_0x14;
    int field_0x18;
    ListNode* next; // +0x1c
};

struct ListContainer {
    int field_0x00;
    int field_0x04;
    int field_0x08;
    int field_0x0c;
    int field_0x10;
    int field_0x14;
    int field_0x18;
    ListNode* head; // +0x1c
};

// Forward declarations of external functions
int FUN_005dc670(void* this); // Returns some value used for comparison
void FUN_00b97aea(void); // Assertion or error handler
void FUN_005e09e0(void); // Advances iterator (likely modifies global or member state)

int SomeManager::updateListFlags(char param_2) {
    int iVar4 = FUN_005dc670(this);
    if (iVar4 != 0) {
        ListContainer* container = *(ListContainer**)((int)this + 8);
        ListNode* iVar2 = container->head; // First node
        ListNode* head = container->head; // Sentinel for circular list

        while (true) {
            // Sanity checks
            if (container == 0 || container != *(ListContainer**)((int)this + 8)) {
                FUN_00b97aea();
            }
            if (iVar2 == head) break; // End of circular list
            if (container == 0) {
                FUN_00b97aea();
            }
            if (iVar2 == container->head) { // Check if node is the head
                FUN_00b97aea();
            }

            void* obj = iVar2->data; // Object at node+0x10
            if (obj != (void*)iVar4) {
                if (param_2 == 0) {
                    *(char*)((int)obj + 0x298) = 0;
                } else if (*(char*)((int)obj + 0x299) == 0) {
                    *(char*)((int)obj + 0x298) = 1;
                }
            }
            FUN_005e09e0(); // Advance to next node (likely modifies iVar2 via global/state)
        }
        return 1;
    }
    return 0;
}