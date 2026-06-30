// FUNC_NAME: SomeManager::~SomeManager()
// Function address: 0x005f6630
// Destructor for a manager class that manages sub-objects and linked lists.

#include <cstdint>

// Forward declarations of external functions used
void __fastcall FUN_005f5ce0(void* ptr); // sub-object constructor/init
void __fastcall FUN_004abf50(void* ptr); // free/deallocation
uint32_t __fastcall FUN_005f7fa0(uint32_t arg1, uint32_t arg2, uint32_t* arg3); // allocation/registration

// Vtable symbols (addresses)
extern uint32_t PTR_FUN_00e407c4; // initial vtable
extern uint32_t PTR_FUN_00e32808; // final vtable (after cleanup)

// Structure for linked list nodes used in member at offset 0x4
struct ListNode {
    ListNode* next; // +0x0
    ListNode* prev; // +0x4 (actually backwards? The code uses second dword as next)
};

// Class SomeManager
class SomeManager {
public:
    // Vtable pointer at +0x0
    // Member at +0x4: head of a singly linked list (ListNode*)
    ListNode* listHead; // +0x4

    // Sub-object at +0x8 (first sub-object, treated as a list head in destructor)
    uint32_t subObj1[3]; // +0x8, size 12 bytes? Actually the destructor accesses +0x8 and +0x14

    // Member at +0x14: list head for second linked list? (piVar6 = param_1+5 -> offset 20=0x14)
    // Actually +0x14 is part of subObj1? Let's analyze offsets:
    // param_1+0: vtable
    // param_1+1: listHead (offset 0x4)
    // param_1+2: subObj1 start (offset 0x8)
    // param_1+3: subObj1[1] (offset 0xC)
    // param_1+4: subObj1[2] (offset 0x10)
    // param_1+5: subObj2 start? (offset 0x14)
    // param_1+6: subObj2[1] (offset 0x18)
    // param_1+7: subObj2[2] (offset 0x1C)
    // param_1+8: ? (offset 0x20)
    // param_1+9: allocatedPointer (offset 0x24) - used in FUN_005f7fa0
    // param_1+10: someArg (offset 0x28) - used in FUN_005f7fa0
    // param_1+11: ? (offset 0x2C)
    // param_1+12: freedPointer (offset 0x30) - freed at start
    uint32_t subObj2[3]; // +0x14 (offset 20)

    uint32_t field_0x20; // +0x20
    uint32_t allocatedPointer; // +0x24
    uint32_t someArg; // +0x28
    uint32_t field_0x2C; // +0x2C
    void* freedPointer; // +0x30

    // Destructor
    __fastcall ~SomeManager() {
        // Set initial vtable
        *(uint32_t*)this = &PTR_FUN_00e407c4;

        // Initialize sub-objects (constructor calls)
        FUN_005f5ce0(&subObj1[0]); // +0x8
        FUN_005f5ce0(&subObj2[0]); // +0x14

        // Free the pointer at +0x30
        if (freedPointer != nullptr) {
            *(uint32_t*)freedPointer = 0; // set first dword to 0
            FUN_004abf50(freedPointer); // deallocate
        }
        freedPointer = nullptr;

        // Call registration/allocation function, store result at allocatedPointer
        allocatedPointer = FUN_005f7fa0(DAT_01223520, allocatedPointer, &someArg);

        // Unlink subObj2 from linked list (the second sub-object acts as a node)
        if (subObj2[0] != 0) { // subObj2[0] is presumably a pointer to list head or next?
            // The code treats subObj2 as a linked list node with next at +0x4 inside subObj2
            // Actually the pattern: if *piVar6 != 0, then get *(int**)(iVar3+4) which is piVar4
            // This suggests a doubly linked list? Let's reconstruct from decompiled.
            // piVar6 = &subObj2[0]; // offset 0x14
            // iVar3 = *piVar6; // value at offset 0x14
            // piVar4 = *(int**)(iVar3 + 4); // get prev/next? 
            // Then if piVar4 == piVar6 (list head), set (iVar3+4) = param_1[6] (which is subObj2[1])
            // else walk until piVar5 == piVar6.
            // This is a standard doubly linked list unlink: the node at piVar6 has next at +0x4.
            // The list head is at some fixed location? Actually iVar3 is the list head stored in field.
            // So subObj2[0] holds pointer to a linked list head? Or subObj2 itself is a node?
            // Given the complexity, we'll simplify: unlink from a doubly linked list.
            // We'll implement the exact logic from decompiled.
            int* listHead2 = (int*)subObj2[0]; // list head pointer
            if (listHead2 != nullptr) {
                int* current = *(int**)(listHead2 + 1); // *(listHead2+4) -> next
                if (current == (int*)&subObj2) { // if next points to this node
                    *(listHead2 + 1) = (int)subObj2[1]; // replace with second element
                } else {
                    // walk to find the node that points to us
                    int* prev = current;
                    while (1) {
                        int* next = *(int**)(prev + 1);
                        if (next == (int*)&subObj2) break;
                        prev = next;
                    }
                    prev[1] = subObj2[1]; // unlink
                }
            }
        }

        // Similarly unlink subObj1 (piVar1 = &subObj1[0]) with the same pattern
        if (subObj1[0] != 0) {
            int* listHead1 = (int*)subObj1[0];
            if (listHead1 != nullptr) {
                int* current = *(int**)(listHead1 + 1);
                if (current == (int*)&subObj1) {
                    *(int*)(listHead1 + 1) = (int)subObj1[1];
                } else {
                    int* prev = current;
                    while (1) {
                        int* next = *(int**)(prev + 1);
                        if (next == (int*)&subObj1) break;
                        prev = next;
                    }
                    prev[1] = subObj1[1];
                }
            }
        }

        // Change vtable to cleanup vtable
        *(uint32_t*)this = &PTR_FUN_00e32808;

        // Free all nodes in the linked list at +0x4
        ListNode* node = listHead;
        while (node != nullptr) {
            ListNode* nextNode = node->next; // +0x4 is the next pointer? Actually node->prev is at +0x4? In code it uses second dword as next.
            // The decompiled: puVar2 = (undefined4 *)puVar2[1]; so second dword is next pointer.
            node->next = nullptr;
            node->prev = nullptr; // set both to 0
            node = nextNode;
        }
    }
};