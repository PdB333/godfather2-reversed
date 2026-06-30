// FUN_0043e380: Container::removeByValue

void __thiscall Container::removeByValue(void *container, void *value)
{
    Node *currentNode;
    Node *headSentinel;
    Allocator *allocator;

    // head sentinel is at container+0x38, its next pointer is the first actual node
    headSentinel = *(Node **)((int)container + 0x38);          // +0x38: head sentinel node pointer
    currentNode = headSentinel->next;                          // start from first real node

    allocator = (Allocator *)((int)container + 0x20);          // +0x20: allocator object

    while (true)
    {
        if (allocator == nullptr)
            assertionFailed();                                  // FUN_00b97aea: debug assert

        // if we've circled back to the sentinel, stop
        if (currentNode == headSentinel)
            break;

        if (allocator == nullptr)
            assertionFailed();

        if (currentNode == headSentinel)
            assertionFailed();                                 // redundant check

        // check if current node's stored value matches
        if (currentNode->value == value)
            break;

        if (currentNode == headSentinel)
            assertionFailed();

        currentNode = currentNode->next;
    }

    // after loop, currentNode is either the sentinel (not found) or the matching node
    if (currentNode != headSentinel)
    {
        // call destroy on two attached functor objects (vtbl+8)
        if (*(int *)((int)container + 0x18) != 0)
            (**(code **)(*(int *)value + 8))(*(int *)((int)container + 0x18));   // +0x18: functor/cleanup object 1
        if (*(int *)((int)container + 0x1c) != 0)
            (**(code **)(*(int *)value + 8))(*(int *)((int)container + 0x1c));   // +0x1c: functor/cleanup object 2

        // remove node from doubly linked list
        if (allocator == nullptr)
            assertionFailed();

        if (currentNode != headSentinel)
        {
            currentNode->prev->next = currentNode->next;
            currentNode->next->prev = currentNode->prev;

            // deallocate node through the allocator (vtbl+4, size 0xC)
            (**(code **)(*(int *)allocator + 4))(currentNode, 0xC);

            // decrease element count
            *(int *)((int)container + 0x3C) = *(int *)((int)container + 0x3C) - 1; // +0x3C: count
        }
    }
}