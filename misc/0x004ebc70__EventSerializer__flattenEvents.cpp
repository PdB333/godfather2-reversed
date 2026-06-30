// FUNC_NAME: EventSerializer::flattenEvents
void EventSerializer::flattenEvents(void) {
    // Iterates a linked list of serializable nodes (each with a flag), calculates total size,
    // allocates aligned memory, then copies node headers and serializes node data into the buffer.
    Node* currentNode = this;  // this is the head of the list
    int totalSize = 0;

    if (currentNode != nullptr) {
        // First pass: calculate total size (16-byte header + aligned serialization size)
        do {
            if (currentNode->flag != 0) {
                int serSize = currentNode->vtable->getSize();          // first virtual: returns size
                totalSize += 0x10 + ((serSize + 0xf) & 0xfffffff0);   // align each node's output
            }
            currentNode = currentNode->next;  // next pointer at +8
        } while (currentNode != nullptr);

        if (totalSize != 0) {
            AllocInfo allocInfo;
            allocInfo.type = 2;
            allocInfo.alignment = 0x10;
            allocInfo.result = nullptr;

            Allocator* allocator = FUN_009c8f80();                    // get global allocator
            int* buffer = (int*)allocator->allocate(totalSize, &allocInfo);

            // Buffer start stored via allocInfo.result (not used further)
            int* writePtr = buffer;

            Node* iter = this;
            Node* lastWritten = nullptr;

            while (iter != nullptr) {
                int* nextWritePtr = writePtr;  // save potential next start

                if (iter->flag != 0) {
                    // Copy node header (two qwords = 16 bytes) into buffer
                    *(undefined8*)writePtr = *(undefined8*)iter;
                    *(undefined8*)(writePtr + 2) = *(undefined8*)((char*)iter + 8);

                    // Serialize node's data (second virtual function)
                    iter->vtable->serialize(writePtr);

                    int serSize = iter->vtable->getSize();
                    // Advance write pointer: header (4 ints) + aligned serialized data
                    nextWritePtr = writePtr + ((serSize + 0xf) >> 4) + 1;  // each slot = 4 * 4 bytes?
                    // store the next buffer position in the node's copy (offset +8)
                    writePtr[2] = (int)nextWritePtr;
                    writePtr[3] = 0;
                    lastWritten = writePtr;
                }
                iter = iter->next;
                writePtr = nextWritePtr;
            }
            if (lastWritten != nullptr) {
                lastWritten[2] = 0;  // terminate chain
            }
        }
    }
}