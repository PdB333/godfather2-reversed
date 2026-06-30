// FUNC_NAME: MultiTrackStream::destructor

void __thiscall MultiTrackStream::destructor(MultiTrackStream *this) {
    // Save original vtable pointer (base class)
    this->vtablePtr = &MultiTrackStream_vtable_initial;
    
    // If there is a pending callback (non-null at +0x0C)
    if (this->callbackData != 0) {
        // Call release on the source stream (object at +0x18)
        // The vtable of source stream has release at offset 4, and stop at offset 12
        MultiTrackStream *source = this->sourceStream;
        source->vtablePtr->release(this->callbackData, this->callbackArg);
        this->callbackData = 0;
        this->callbackArg = 0;
        source->vtablePtr->stop();
        this->sourceStream = 0;
    }
    
    // Switch to another base vtable (likely this class's own vtable)
    this->vtablePtr = &MultiTrackStream_vtable_derived;
    
    // Walk the linked list of tracks starting at +0x04
    TrackNode *node = this->trackList;
    while (node != 0) {
        TrackNode *nextNode = node->next;
        node->next = 0;
        node->someField = 0; // Clear first field of the node
        node = nextNode;
    }
}