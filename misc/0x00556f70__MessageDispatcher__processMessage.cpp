// FUNC_NAME: MessageDispatcher::processMessage
// Address: 0x00556f70
// Role: Scans a message list in `this` for message ID 0x802. If found, resolves its index and reads
// a value from a data structure accessible via `dataSource` (dataSource->+8)->+0x50 array at that index,
// then updates `target`'s field at offset 0x60 if changed.

void __thiscall MessageDispatcher::processMessage(void* messageDispatcher, void* target, void* dataSource)
{
    int messageCount = *(int*)((char*)messageDispatcher + 0x78);
    int i = 0;
    int newValue = 0;
    int indexBuffer[3];

    if (messageCount > 0) {
        int* messageList = *(int**)((char*)messageDispatcher + 0x74);
        do {
            if (messageList[i] == 0x802) {
                // Resolve message ID 0x802 into an index (uses helper function at 0x4af8c0)
                resolveMessageIndex(indexBuffer, 0x802);
                // Access dataSource->field_8->field_50 as array of ints, index = indexBuffer[0]
                newValue = *(int*)(
                    *(int*)(
                        *(int*)((char*)dataSource + 8) + 0x50
                    ) + indexBuffer[0] * 4
                );
                break;
            }
            i++;
        } while (i < messageCount);
    }

    // Update target's field at +0x60 only if the value changed
    int* targetField = (int*)((char*)target + 0x60);
    if (*targetField != newValue) {
        *targetField = newValue;
    }
}