// FUNC_NAME: serializeBufferEntryList
struct StreamWriter {
    void* streamHandle; // +0x00
    void (*writeFunc)(void*, void*, int, void*); // +0x04
    void* writeContext; // +0x08
};

struct BufferObject {
    int unknown_0x00;  // +0x00
    int unknown_0x04;  // +0x04
    int unknown_0x08;  // +0x08
    int dataLen;       // +0x0C
    char* data;        // +0x10
};

struct BufferEntry {
    BufferObject* buffer; // +0x00
    int field4;           // +0x04
    int field8;           // +0x08
};

struct EntryList {
    int unknown_0x00;      // +0x00
    BufferEntry* entries;  // +0x18
    int entryCount;        // +0x38
};

// param_1 = pointer to EntryList
void serializeBufferEntryList(int param_1) {
    // ESI is assumed to point to a StreamWriter object (pre‑set by caller)
    StreamWriter* stream = (StreamWriter*)unaff_ESI; // approximating ESI usage

    EntryList* list = (EntryList*)param_1;
    int count = list->entryCount; // +0x38

    // Write count as 4-byte integer
    stream->writeFunc(stream->streamHandle, &count, 4, stream->writeContext);

    if (count > 0) {
        int offset = 0;
        do {
            BufferEntry* entry = (BufferEntry*)((char*)list->entries + offset); // each entry is 12 bytes
            BufferObject* buffer = entry->buffer;

            if (buffer == NULL || buffer->data == NULL) {
                int zero = 0;
                stream->writeFunc(stream->streamHandle, &zero, 4, stream->writeContext);
            } else {
                int dataSize = buffer->dataLen + 1; // include null terminator
                stream->writeFunc(stream->streamHandle, &dataSize, 4, stream->writeContext);
                stream->writeFunc(stream->streamHandle, buffer->data, dataSize, stream->writeContext);
            }

            // Write the two int fields after the buffer data
            stream->writeFunc(stream->streamHandle, &entry->field4, 4, stream->writeContext);
            stream->writeFunc(stream->streamHandle, &entry->field8, 4, stream->writeContext);

            offset += 12;
            count--;
        } while (count != 0);
    }
}