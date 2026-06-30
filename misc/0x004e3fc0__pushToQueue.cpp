// FUNC_NAME: pushToQueue
// Function at 0x004e3fc0: Stores a 32-bit value into a global queue buffer and increments the counter.
void pushToQueue(int value)
{
    gQueueBuffer[gQueueCount] = value;
    gQueueCount++;
}