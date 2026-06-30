// FUNC_NAME: dequeueNode
void __fastcall dequeueNode(int param_1, void* containerPtr)
{
    // containerPtr points to an object that has a linked list head at offset 0x2d8.
    // ListNode is the node structure with fields:
    // +0x00: next pointer (uint32)
    // +0x04: two‑byte flags (uint16)
    // +0x06: one‑byte type (uint8)
    // +0x08: int32 field_8
    // +0x0C: int32 field_C (reset to -1)
    // +0x10: int32 field_10 (reset to 0)
    struct ListNode {
        void* next;       // +0x00
        uint16 flags;     // +0x04
        uint8 type;       // +0x06
        uint8 pad;        // +0x07 (alignment padding)
        int field_8;      // +0x08
        int field_C;      // +0x0C
        int field_10;     // +0x10
    };

    ListNode* node = *(ListNode**)((char*)containerPtr + 0x2d8);
    if (node != nullptr) {
        // Remove head from the list
        *(ListNode**)((char*)containerPtr + 0x2d8) = node->next;

        // Reset node fields to default / uninitialized state
        node->next = 0;
        node->flags = 0;          // writes 2 bytes at +0x04
        *(char*)((char*)node + 6) = 0; // writes 1 byte at +0x06
        node->field_8 = 0;
        node->field_C = -1;
        node->field_10 = 0;
    }
    // param_1 (ecx) is unused in this version
}