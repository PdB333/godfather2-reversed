// FUNC_NAME: NodeStack::push
void NodeStack::push(void)
{
    uint *defaultData;
    Node *newNode;

    // Determine default data value from global pointer or fallback
    defaultData = g_pDefaultData;
    if (g_pDefaultData == nullptr) {
        defaultData = &g_fallbackDefault;
    }

    // Allocate new node (size 0xC) using custom allocator
    newNode = (Node*)(*(code **)g_pAllocator)(0xC);
    if (newNode != nullptr) {
        newNode->data = *defaultData;
        newNode->next = nullptr;
        newNode->prev = nullptr;
    }

    // Insert at head (stack push)
    if (g_pHead != nullptr) {
        // Link new node after current head
        g_pHead->next = newNode;
        newNode->prev = g_pHead;
        // Advance head to new node (new head)
        g_pHead = g_pHead->next;
    } else {
        // First node: both head and tail point to it
        g_pTail = newNode;
        g_pHead = newNode;
    }
    g_count++;
}