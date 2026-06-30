// FUNC_NAME: RingBuffer::init
void RingBuffer::init(void)
{
    // Set buffer size to 0x3ff8 (16376 bytes) - almost 16KB
    this->bufferSize = 0x3ff8;                         // +0x0C

    // Allocate a 12-byte control structure
    BufferControl* control = (BufferControl*)FUN_009c8e50(0xC);

    if (control != (BufferControl*)0x0)
    {
        // Allocate the actual data buffer of the specified size
        control->buffer = (undefined4)FUN_009c8e80(0x3ff8);  // +0x04
    }

    // Store pointer to control structure in this
    this->control = control;                           // +0x08

    // Initialize control fields
    control->writePos = 0;                             // +0x00
    control->readPos = 0;                              // +0x08

    // Call secondary initialization (virtual or member)
    FUN_0065c810(this);
}