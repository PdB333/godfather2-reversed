// FUNC_NAME: TaskQueue::~TaskQueue
void __fastcall TaskQueue::~TaskQueue()
{
    // Set vtable to first base class vtable (probably an intermediate destructor step)
    this->vtable = &PTR_FUN_00e365f0;

    // If a managed resource object exists, release it via its own vtable methods
    if (this->resourceObject != nullptr) {
        // Call resource method at vtable+4 with two arguments (resourceArg1, resourceArg2)
        this->resourceObject->takeAction(this->resourceArg1, this->resourceArg2);
        // Clear resource arguments
        this->resourceArg1 = 0;
        this->resourceArg2 = 0;
        // Call resource cleanup method at vtable+0xC
        this->resourceObject->cleanup();
        // Null out resource object pointer
        this->resourceObject = nullptr;
    }

    // Switch vtable to second base class vtable (final destructor step)
    this->vtable = &PTR_FUN_00e32808;

    // Clear the linked list of pending nodes
    ListNode* current = this->listHead;
    while (current != nullptr) {
        ListNode* next = current->next;
        current->next = nullptr;
        current->data = nullptr;
        current = next;
    }
}