// FUNC_NAME: StreamManager::StreamManager(uint)
void __thiscall StreamManager::StreamManager(uint count)
{
    // Initialize fields at offsets +0x0 and +0x4 to 0
    this->field_0 = 0;
    this->field_4 = 0;

    // Fields at +0xA8 (0x2a) and +0xAC (0x2b)
    this->field_A8 = 0;
    this->field_AC = 0xFFFFFFFF;          // -1 sentinel

    // Field at +0xB0 (0x2c)
    this->field_B0 = 0xFFFFFF99;          // -103

    // Clear eight fields from +0xB4 to +0xD0 (0x2d to 0x34)
    this->field_B4 = 0;
    this->field_B8 = 0;
    this->field_BC = 0;
    this->field_C0 = 0;
    this->field_C4 = 0;
    this->field_C8 = 0;
    this->field_CC = 0;
    this->field_D0 = 0;

    // Allocate buffer of count * 4 bytes; result stored at +0xD8 (0x36)
    this->buffer = allocateMemory(count * 4);
    // Store count at +0xDC (0x37)
    this->bufferSize = count;

    // Two more fields at +0xE0, +0xE4 set to 0
    this->field_E0 = 0;
    this->field_E4 = 0;

    // Initialize critical section at offset +0xE8 (0x3a)
    InitializeCriticalSection(&this->criticalSection);

    // Four fields at +0x108, +0x10C, +0x110, +0x114 (0x42-0x45)
    this->field_108 = 0;
    this->field_10C = 0;
    this->field_110 = 0;
    this->field_114 = 0;

    // Additional initialization (likely condition variable or event)
    initializeSubsystem();

    // Set boolean/flag at offset +0x2 (byte) to 0
    *((byte*)this + 2) = 0;
}