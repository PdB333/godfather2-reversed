// FUNC_NAME: PacketWindow::pushSequence
void __thiscall PacketWindow::pushSequence(int thisPtr)
{
    int end = *(int *)(thisPtr + 0x68);   // +0x68: mEnd (write pointer)
    int start = *(int *)(thisPtr + 0x70); // +0x70: mStart (read pointer)
    int count = *(int *)(thisPtr + 0x5c); // +0x5c: mCount (number of queued sequences)

    // Check if there is room for one more sequence (capacity = end - start)
    if (count <= (end - start) - 1) {
        *(int *)(thisPtr + 0x5c) = count + 1;
        // Use the smaller of start and end as the sequence index to process
        if (start <= end) {
            end = start;
        }
        processSequence(end); // 0x009893a0
    }
}