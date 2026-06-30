// FUNC_NAME: updateRandomRingBuffer
// Address: 0x004e41b0
// This function updates a 20-element ring buffer state that is used as a simple pseudo-random number generator.
// It works by adding the value at (index+2 mod 20) to the value at (index-1 mod 20) and then decrementing the index (mod 20).
// The ring buffer is likely seeded once per game session.

static int g_ringBuffer[20];          // +0x0: 20 int32 values, initial seed unknown
static int g_ringIndex;               // +0x0: current index into the ring buffer (0-19)

void updateRandomRingBuffer(void)
{
    int prevIndex = g_ringIndex - 1;
    int nextIndex = g_ringIndex + 2;

    // Wrap prevIndex to 0x13 if negative
    if (prevIndex < 0) {
        prevIndex = 0x13;  // 19
    }
    // Wrap nextIndex to (g_ringIndex - 0x12) if it exceeds 0x13
    else if (0x13 < nextIndex) {
        nextIndex = g_ringIndex - 0x12;
    }

    // Add the value at the wrapped next index to the wrapped previous index
    g_ringBuffer[prevIndex] += g_ringBuffer[nextIndex];

    // Decrement the ring index (with wrap)
    g_ringIndex = prevIndex;
}