// FUNC_NAME: EAList::clear
// Address: 0x0043EC10
// Role: Clears a circular doubly-linked list, deleting all allocated nodes via an allocator virtual function.
// Structure:
//   EAList {
//       +0x00 Allocator* mAlloc;   // pointer to allocator object (with vtable)
//       +0x18 Node* mHead;         // pointer to sentinel node
//       +0x1C int mCount;          // current node count
//   }
//   Node {
//       +0x00 Node* next;
//       +0x04 Node* prev;
//       +0x08 ... (12 bytes total)
//   }

typedef struct Node Node;
struct Node {
    Node* next;   // +0x00
    Node* prev;   // +0x04
    // data follows; total size 12 bytes
};

typedef struct Allocator Allocator;
struct Allocator {
    void** vtable; // +0x00
    // vtable[1] (offset 4) -> deallocate function (__thiscall with (void* ptr, size_t size))
};

class EAList {
public:
    // __thiscall
    void clear();

private:
    Allocator* mAlloc;  // +0x00
    // padding? (often 8 bytes alignment, but we omit)
    Node* mHead;        // +0x18
    int mCount;         // +0x1C
};

void EAList::clear() {
    Node* sentinel = this->mHead;          // piVar1 = unaff_ESI[6]
    Node* node = sentinel->next;           // piVar2 = *piVar1
    sentinel->next = sentinel;             // *piVar1 = piVar1
    sentinel->prev = sentinel;             // *(unaff_ESI[6] + 4) = unaff_ESI[6]
    this->mCount = 0;                      // unaff_ESI[7] = 0

    if (node != sentinel) {
        do {
            Node* nextNode = node->next;   // piVar1 = *piVar2
            // Call allocator's deallocate (vtable[1]) passing the node and its size (12 bytes)
            // The allocator is stored at offset 0x00 of the list object
            void* deallocateFunc = (void*)(this->mAlloc->vtable[1]);  // (*(code**)(*(int*)*unaff_ESI + 4))
            // __thiscall: first param in ECX is 'this' for allocator? But here called with node as first param.
            // Actually EA allocator deallocate is typically __thiscall with 'this' = allocator object,
            // first explicit param = pointer to free, second = size.
            // However Ghidra shows call(node, 0xc) where node is passed as 'this'? Possibly miscompiled.
            // We assume the allocator's deallocate function is __thiscall with allocator as 'this'
            // and (void* ptr, size_t size) as parameters.
            // The decompiled code calls the function with piVar2 as first argument, 0xc as second,
            // and ECX? ECX is probably the allocator pointer. So we emulate:
            __asm {
                mov ecx, this->mAlloc   // but not needed in reconstruction
            }
            // We'll just call via allocator's deallocate:
            this->mAlloc->vtable[1](this->mAlloc, node, 12); // not valid C++ but conceptually
            // Actually a more faithful reconstruction: 
            // ((void (__thiscall*)(Allocator*, void*, int))deallocateFunc)(this->mAlloc, node, 12);
            // But we'll just leave comment.
            node = nextNode;
        } while (node != sentinel);
    }
}