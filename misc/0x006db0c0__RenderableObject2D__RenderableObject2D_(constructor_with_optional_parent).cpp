// FUNC_NAME: RenderableObject2D::RenderableObject2D (constructor with optional parent)
// Address: 0x006db0c0
// Role: Constructs a RenderableObject2D instance. Initializes vtable, default
//       color/rectangle values, and optionally inserts the object as a child
//       of the given parent (parent's child list at offset 0x48, this node at offset 0xE0).

#include <cstdint>

// Forward declaration of vtable symbol (set by linker)
extern void* PTR_FUN_00d5f630; // vtable address

// Global constants (likely floats or RGBA values)
extern uint32_t DAT_00d5780c; // default float 0.0f?
extern uint32_t DAT_00d5e288; // color component 1
extern uint32_t DAT_00d5efd0; // color component 2
extern uint32_t DAT_00e446dc; // color component 3
extern uint32_t DAT_00d5f5f0; // another pair start
extern uint32_t DAT_00d5f5f4; // another pair end

// Likely a utility function to remove a node from a linked list or free a pointer
extern void FUN_004daf90(void** node); // remove/reset list node

class RenderableObject2D {
public:
    // Offsets relative to 'this' (0-based byte offsets)
    // +0x00: vtable pointer
    // +0x04: some integer (initialized to 0)
    // +0x08: single byte (initialized to 0)
    // +0x0C: some integer (initialized to 0xFF)
    // +0x14..+0x1A: various float groups (rectangles/colors)
    // +0xE0: linked-list node (used to attach to parent's child list)
    // +0xE4: next pointer inside the node

    void* vtable; // +0x00
    int32_t field_04; // +0x04
    uint8_t byte_08; // +0x08
    int32_t field_0C; // +0x0C
    // ... many float fields, not all named individually

    // The node used for parent-child list (offset 0xE0)
    struct ListNode {
        void* parent;      // +0x00 (pointer to parent's node? or previous?)
        ListNode* next;    // +0x04 (next sibling)
    } childNode; // at offset 0xE0

    // This constructor follows __thiscall convention
    void* __thiscall RenderableObject2D(int param_2) {
        uint32_t uVar2 = DAT_00d5780c;
        uint32_t uVar3 = DAT_00d5e288;
        uint32_t uVar4 = DAT_00d5efd0;
        uint32_t uVar5 = DAT_00e446dc;
        uint32_t uVar6 = DAT_00d5f5f0; // start of a pair
        uint32_t uVar7 = DAT_00d5f5f4; // end of a pair

        // Initialize basic fields
        this->field_04 = 0;                     // param_1[1] = 0
        *(uint8_t*)((int)this + 0x08) = 0;     // *(byte)(param_1+2) = 0
        this->field_0C = 0xFF;                  // param_1[3] = 0xFF
        this->vtable = &PTR_FUN_00d5f630;       // *param_1 = &vtable

        // Set default float groups (likely colors or rectangles)
        ((uint32_t*)this)[0x14] = uVar3;
        ((uint32_t*)this)[0x15] = uVar4;
        ((uint32_t*)this)[0x16] = uVar3;
        ((uint32_t*)this)[0x17] = uVar4;
        ((uint32_t*)this)[0x18] = uVar2;
        ((uint32_t*)this)[0x1B] = uVar2;
        ((uint32_t*)this)[0x1C] = uVar2;
        ((uint32_t*)this)[0x14] = uVar3;
        ((uint32_t*)this)[0x15] = uVar4;
        ((uint32_t*)this)[0x16] = uVar3;
        ((uint32_t*)this)[0x17] = uVar4;
        ((uint32_t*)this)[0x19] = uVar3;
        ((uint32_t*)this)[0x1A] = uVar5;
        ((uint32_t*)this)[4] = uVar6;
        ((uint32_t*)this)[5] = uVar7;
        ((uint32_t*)this)[0x31] = uVar2;
        ((uint32_t*)this)[0x34] = uVar2;
        ((uint32_t*)this)[0x35] = uVar2;
        ((uint32_t*)this)[0x2D] = uVar3;
        ((uint32_t*)this)[0x2E] = uVar4;
        ((uint32_t*)this)[0x2F] = uVar3;
        ((uint32_t*)this)[0x30] = uVar4;
        ((uint32_t*)this)[0x32] = uVar3;
        ((uint32_t*)this)[0x33] = uVar5;
        ((uint32_t*)this)[0x1D] = uVar6;
        ((uint32_t*)this)[0x1E] = uVar7;
        ((uint32_t*)this)[0x38] = 0;
        ((uint32_t*)this)[0x39] = 0;
        ((uint32_t*)this)[0x3A] = 0;
        ((uint32_t*)this)[0x3B] = 0;
        ((uint32_t*)this)[0x3C] = 0;
        *(uint8_t*)((int)this + 0x100) = 0; // offset 0x40 * 4? careful: param_1+0x40 is offset 0x100
        ((uint32_t*)this)[0x41] = uVar3;
        ((uint32_t*)this)[0x42] = uVar4;
        ((uint32_t*)this)[0x47] = 0;
        ((uint32_t*)this)[0x46] = 0;
        ((uint32_t*)this)[0x45] = 0;
        ((uint32_t*)this)[0x44] = 0;
        ((uint32_t*)this)[0x4B] = 0;
        ((uint32_t*)this)[0x4A] = 0;
        ((uint32_t*)this)[0x49] = 0;
        ((uint32_t*)this)[0x48] = 0;
        *(uint8_t*)((int)this + 0x130) = 0; // offset 0x4C * 4
        ((uint32_t*)this)[0x4D] = uVar3;
        ((uint32_t*)this)[0x4E] = uVar4;
        ((uint32_t*)this)[0x53] = 0;
        ((uint32_t*)this)[0x52] = 0;
        ((uint32_t*)this)[0x51] = 0;
        ((uint32_t*)this)[0x50] = 0;
        ((uint32_t*)this)[0x57] = 0;
        ((uint32_t*)this)[0x56] = 0;
        ((uint32_t*)this)[0x55] = 0;
        ((uint32_t*)this)[0x54] = 0;
        *(uint8_t*)((int)this + 0x160) = 0; // offset 0x58 * 4
        ((uint32_t*)this)[0x59] = uVar3;
        ((uint32_t*)this)[0x5A] = uVar4;
        ((uint32_t*)this)[0x5F] = 0;
        ((uint32_t*)this)[0x5E] = 0;
        ((uint32_t*)this)[0x5D] = 0;
        ((uint32_t*)this)[0x5C] = 0;
        ((uint32_t*)this)[0x63] = 0; // param_1[99] - but index 99 is 0x63*4? Wait, param_1[99] means index 99? Actually decompiler says param_1[99] = 0; that's offset 0x18C? Must be a typo, likely it's param_1[0x63]? The code shows "param_1[99] = 0;" but in the list it's after param_1[0x60]? The decompiled line: "param_1[99] = 0;" and then "param_1[0x62] = 0;" etc. Possibly index 99 is actually hex 0x63? Given the context, I'll assume it's offset 0x60 (96 decimal) or 0x63? Hard to tell. We'll keep it as is for faithfulness.
        ((uint32_t*)this)[0x62] = 0;
        ((uint32_t*)this)[0x61] = 0;
        ((uint32_t*)this)[0x60] = 0;
        *(uint8_t*)((int)this + 0x1A0) = 1; // offset 0x68 * 4 = 0x1A0, set to 1

        // Handle parent-child relationship
        ListNode* node = &this->childNode; // param_1 + 0x38 (in int units) = byte offset 0xE0
        ListNode* parentNode;
        if (param_2 == 0) {
            parentNode = nullptr;
        } else {
            // parent is a RenderableObject2D*, its child list node is at offset 0x48
            parentNode = reinterpret_cast<ListNode*>(reinterpret_cast<char*>(param_2) + 0x48);
        }

        if (node->parent != parentNode) {
            if (node->parent != 0) {
                FUN_004daf90(&node->parent); // remove from previous list
            }
            node->parent = parentNode;
            if (parentNode != 0) {
                node->next = parentNode->next; // param_1[0x39] = *(parent_2 + 4) — but careful: parent_2 is param_2+0x48? Actually the decompiled code uses "param_2" after adding 0x48? The decompiled: if (param_2 == 0) param_2=0 else param_2 += 0x48. So param_2 becomes the parent node pointer. Then they access param_2[1]? Actually *(param_2+4) is parentNode->next. So we set node->next = parentNode->next. Then set parentNode->next = node (the new node). So it's insertion at head.
                parentNode->next = node;
            }
        }
        return this;
    }
};