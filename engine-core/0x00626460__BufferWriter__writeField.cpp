// FUNC_NAME: BufferWriter::writeField

void __thiscall BufferWriter::writeField(int value)
{
    // +0x10: pointer to buffer info struct (capacity at +0x20, used at +0x24)
    BufferInfo* bufInfo = *(BufferInfo**)(this + 0x10);

    // Flush if buffer is full (capacity <= used)
    if (bufInfo->capacity <= bufInfo->used)
    {
        flushBuffer(); // FUN_00627360
    }

    // +0x08: current write pointer
    char*& writePtr = *(char**)(this + 0x8);

    if (value > 1)
    {
        // Write a larger data block (e.g., an array or string)
        writeBlock(); // FUN_006343b0

        // Adjust write pointer. Decompiled as writePtr += (value * -8) + 8;
        // Likely intended to advance by 8*value, or possibly backfill? 
        // The exact semantics are uncertain.
        writePtr += 8 - 8 * value;
        return;
    }

    if (value == 0)
    {
        // Write a type tag (4) followed by an ID
        *(uint32_t*)writePtr = 4;               // tag indicating a "node" or "reference"
        *(uint32_t*)(writePtr + 4) = getNextId(); // FUN_00638920: returns some unique ID
        writePtr += 8;
    }
    // If value == 1, nothing is written to the buffer (only the flush check above).
}