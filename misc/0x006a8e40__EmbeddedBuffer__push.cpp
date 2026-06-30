// FUNC_NAME: EmbeddedBuffer::push
// Function at 0x006a8e40: pushes an item into a circular buffer after logging it with "embedded" tag.
// Buffer fields: +0x48 = buffer array pointer, +0x4c = capacity, +0x50 = head index, +0x54 = count

void __thiscall EmbeddedBuffer::push(int data, int typeOrId)
{
    int index = head + count;                 // Next write position (pre-increment count)
    count++;                                  // Increase stored count

    if (capacity <= index) {
        index -= capacity;                    // Wrap around if past capacity
    }

    buffer[index] = data;                     // Store the data

    // Log the data for debugging/scripting purposes
    logEmbeddedMessage(data, typeOrId, "embedded");
}