// FUNC_NAME: IdAllocator::getNextId
void __fastcall IdAllocator::getNextId(int unusedParam, IdAllocator* allocator)
{
    int valA;
    int valB;

    if (allocator->listA == nullptr) {
        valA = -1;
    } else {
        valA = *allocator->listA; // +0x0C? listA is at offset 12
    }

    if (allocator->listB == nullptr) {
        valB = -1;
    } else {
        valB = *allocator->listB; // +0x08? listB is at offset 8
    }

    if (valA <= valB) {
        allocator->currentId = valB + 1; // +0x00
    } else {
        allocator->currentId = valA + 1;
    }
}