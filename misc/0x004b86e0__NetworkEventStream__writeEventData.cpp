// FUNC_NAME: NetworkEventStream::writeEventData
void __thiscall NetworkEventStream::writeEventData(int param2, int param3, int param4)
{
    // this is a pointer to the stream object.
    // The first member (offset +0x00) is a pointer to the buffer base.
    int bufferBase = *(int *)this; // +0x00: buffer base pointer

    // The current write pointer is stored at bufferBase + 0x14.
    // This pointer is a location within the buffer that points to the next free slot.
    int *writePtr = (int *)(bufferBase + 0x14); // +0x14: current write position

    // Write the event type identifier.
    // PTR_LAB_0112471c is a static pointer (likely a vtable or type descriptor)
    // Stored as a pointer value (4 bytes).
    *(void **)*writePtr = (void *)&PTR_LAB_0112471c;

    // Advance the write pointer past the type identifier (4 bytes).
    *writePtr += 4;

    // Re‑read bufferBase (present in original code, probably redundant).
    bufferBase = *(int *)this;

    // Write param2 at the current write pointer.
    *(int *)*writePtr = param2;

    // Align the write pointer to the next 4‑byte boundary.
    // This ensures subsequent writes are aligned.
    int aligned = (*writePtr + 7) & ~3;
    *writePtr = aligned;

    // Write param3 at the aligned position.
    *(int *)aligned = param3;

    // Align again for the next parameter.
    aligned = (aligned + 7) & ~3;
    *writePtr = aligned;

    // Write param4 at the aligned position.
    *(int *)aligned = param4;

    // Advance write pointer past param4 (4 bytes).
    *writePtr += 4;
}