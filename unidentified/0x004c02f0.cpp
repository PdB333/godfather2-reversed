// FUN_004c02f0: IOStream::~IOStream
void __fastcall IOStream::destructor(IOStream* this)
{
    IOStream* vtable; // unused, but zeroes
    BufferNode* currentNode;
    BufferNode* nextNode;

    // Set vtable to a static "destroyed" marker (optional, prevents further virtual calls)
    this->vtable = &PTR_FUN_00e35f48;
    this->field3 = &PTR_LAB_00e35f58;

    // If we have an underlying stream object, release it
    if (this->stream != nullptr)
    {
        // Call its release method (vtable+4) with the handle and 0
        this->stream->vtable->release(this->streamHandle);
        this->streamHandle = 0;
        this->streamBuffer = 0;

        // Call its close method (vtable+0xC)
        this->stream->vtable->close();
        this->stream = nullptr;
    }

    // Set a different static marker (possibly for cleanup tracking)
    this->field3 = &PTR_FUN_00e32808;

    // Delete all buffer nodes in the linked list
    currentNode = this->bufferListHead;
    while (currentNode != nullptr)
    {
        nextNode = currentNode->next;
        currentNode->next = nullptr;
        currentNode->data = nullptr;
        currentNode = nextNode;
    }

    // Call base destructor / final cleanup
    FUN_004083d0();
}