// FUNC_NAME: TransformNode::attachChildWithTransform
void __thiscall TransformNode::attachChildWithTransform(TransformNode* thisNode, void* parent, int someValue, char attachFlag, TransformNode* childNode, const float (*transform)[4])
{
    // +0x130: ushort flags (bit 0 marks attached)
    *(uint16_t*)((uint8_t*)thisNode + 0x130) = 0;
    if (attachFlag != '\0') {
        *(uint16_t*)((uint8_t*)thisNode + 0x130) |= 1;
    }

    // +0x12C: store parent pointer
    *(void**)((uint8_t*)thisNode + 0x12C) = parent;
    // +0x120: store some integer value
    *(int*)((uint8_t*)thisNode + 0x120) = someValue;

    // +0x124: pointer to head of child list (intrusive linked list)
    int* headPtr = (int*)((uint8_t*)thisNode + 0x124);
    int newHead = (childNode == nullptr) ? 0 : ((int)childNode + 4); // offset 4 for the 'prev' pointer field

    if (*headPtr != newHead) {
        if (*headPtr != 0) {
            FUN_004daf90(headPtr); // free old child list node
        }
        *headPtr = newHead;
        if (newHead != 0) {
            // +0x128: store old backlink of new node
            *(int*)((uint8_t*)thisNode + 0x128) = *(int*)(newHead + 4);
            // set new node's back pointer to headPtr
            *(int**)(newHead + 4) = headPtr;
        }
    }

    // Copy 4x4 transform matrix (16 floats) from EDI register
    // unaff_EDI points to a float[16] (column-major or row-major)
    *(uint32_t*)((uint8_t*)thisNode + 0xE0) = *((uint32_t*)transform + 0);
    *(uint32_t*)((uint8_t*)thisNode + 0xE4) = *((uint32_t*)transform + 1);
    *(uint32_t*)((uint8_t*)thisNode + 0xE8) = *((uint32_t*)transform + 2);
    *(uint32_t*)((uint8_t*)thisNode + 0xEC) = *((uint32_t*)transform + 3);
    *(uint32_t*)((uint8_t*)thisNode + 0xF0) = *((uint32_t*)transform + 4);
    *(uint32_t*)((uint8_t*)thisNode + 0xF4) = *((uint32_t*)transform + 5);
    *(uint32_t*)((uint8_t*)thisNode + 0xF8) = *((uint32_t*)transform + 6);
    *(uint32_t*)((uint8_t*)thisNode + 0xFC) = *((uint32_t*)transform + 7);
    *(uint32_t*)((uint8_t*)thisNode + 0x100) = *((uint32_t*)transform + 8);
    *(uint32_t*)((uint8_t*)thisNode + 0x104) = *((uint32_t*)transform + 9);
    *(uint32_t*)((uint8_t*)thisNode + 0x108) = *((uint32_t*)transform + 10);
    *(uint32_t*)((uint8_t*)thisNode + 0x10C) = *((uint32_t*)transform + 11);
    *(uint32_t*)((uint8_t*)thisNode + 0x110) = *((uint32_t*)transform + 12);
    *(uint32_t*)((uint8_t*)thisNode + 0x114) = *((uint32_t*)transform + 13);
    *(uint32_t*)((uint8_t*)thisNode + 0x118) = *((uint32_t*)transform + 14);
    *(uint32_t*)((uint8_t*)thisNode + 0x11C) = *((uint32_t*)transform + 15);

    // Initialize sub-object at +0x134 (e.g., bounding box or physics proxy)
    FUN_005205b0((uint8_t*)thisNode + 0x134);
    // Update spatial data structures
    FUN_00424470();
    FUN_00417560();
}