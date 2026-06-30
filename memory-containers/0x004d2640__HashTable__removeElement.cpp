// FUNC_NAME: HashTable::removeElement
int HashTable::removeElement(void* element) // __thiscall, this in EDI
{
    // Element fields:
    // +0x00: unknown (used later)
    // +0x0C: uint32_t hash (masked with 0x1FFF -> 13-bit bucket index)
    // +0x10: void* next (pointer to next element in same bucket)
    uint32_t bucketIndex = *(uint32_t*)((uint8_t*)element + 0x0C) & 0x1FFF;
    void* bucketHead = *(void**)((uint8_t*)this + bucketIndex * 4);
    if (bucketHead == nullptr)
        return 1;

    void* prevNode = nullptr;
    void* currentNode = bucketHead;
    while (currentNode != element)
    {
        prevNode = currentNode;
        currentNode = *(void**)((uint8_t*)currentNode + 0x10);
        if (currentNode == nullptr)
            return 1;
    }
    // Unlink from chain
    if (prevNode != nullptr)
    {
        // Not the first node: connect previous to current's next
        *(void**)((uint8_t*)prevNode + 0x10) = *(void**)((uint8_t*)currentNode + 0x10);
    }
    else
    {
        // First node: update bucket head
        *(void**)((uint8_t*)this + bucketIndex * 4) = *(void**)((uint8_t*)currentNode + 0x10);
    }
    // Decrement total element count (stored at offset 0x8000 from hash table base)
    (*(int32_t*)((uint8_t*)this + 0x8000))--;
    return 0;
}