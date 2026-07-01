// FUNC_NAME: Entity::reattachChildComponents
void __fastcall Entity::reattachChildComponents(void* thisPtr)
{
    // Check and update each of the 7 child component pointers with their associated embedded data blocks.
    // Offsets: child pointers at +0x70 to +0x88, data blocks at +0x12c to +0x18c (0x10 stride)
    int* pChild0 = *(int**)((int)thisPtr + 0x70); // +0x70
    if (pChild0 != nullptr) {
        SetChildDataBlock(pChild0, (void*)((int)thisPtr + 0x12c)); // +0x12c
    }

    int* pChild1 = *(int**)((int)thisPtr + 0x74); // +0x74
    if (pChild1 != nullptr) {
        SetChildDataBlock(pChild1, (void*)((int)thisPtr + 0x13c)); // +0x13c
    }

    int* pChild2 = *(int**)((int)thisPtr + 0x78); // +0x78
    if (pChild2 != nullptr) {
        SetChildDataBlock(pChild2, (void*)((int)thisPtr + 0x14c)); // +0x14c
    }

    int* pChild3 = *(int**)((int)thisPtr + 0x7c); // +0x7c
    if (pChild3 != nullptr) {
        SetChildDataBlock(pChild3, (void*)((int)thisPtr + 0x15c)); // +0x15c
    }

    int* pChild4 = *(int**)((int)thisPtr + 0x80); // +0x80
    if (pChild4 != nullptr) {
        SetChildDataBlock(pChild4, (void*)((int)thisPtr + 0x16c)); // +0x16c
    }

    int* pChild5 = *(int**)((int)thisPtr + 0x84); // +0x84
    if (pChild5 != nullptr) {
        SetChildDataBlock(pChild5, (void*)((int)thisPtr + 0x17c)); // +0x17c
    }

    int* pChild6 = *(int**)((int)thisPtr + 0x88); // +0x88
    if (pChild6 != nullptr) {
        SetChildDataBlock(pChild6, (void*)((int)thisPtr + 0x18c)); // +0x18c
    }
}