// FUNC_NAME: EARSBuffer::EARSBuffer
// Constructor initializes fields and allocates a buffer via global allocator.
// Offsets: +0x00 vtable, +0x04 someID (0x19), +0x08 flags?, +0x0C bufferPtr, +0x10 unknown, +0x14 unknown, +0x18 unknown, +0x44 bufferSize?
void __thiscall EARSBuffer::EARSBuffer(void)
{
    // Local allocation parameters: 2, 4, 0 (likely alignment/pool flags)
    struct AllocParams
    {
        int field0;
        int field4;
        int field8;
    };

    // Set vtable pointer
    this->vtable = &PTR_FUN_00e36f74; // +0x00

    // Initialize fields
    this->field_0x04 = 0x19;           // +0x04
    this->field_0x08 = 0;              // +0x08
    this->field_0x10 = 0;              // +0x10
    this->field_0x14 = 0;              // +0x14
    this->field_0x18 = 0;              // +0x18

    // Get the global allocator instance
    Allocator* alloc = FUN_009c8f80(); // Allocator::GetInstance()

    // Prepare allocation parameters (size=100, flags=2,4,0)
    AllocParams params;
    params.field0 = 2;
    params.field4 = 4;
    params.field8 = 0;

    // Allocate 100 bytes via allocator
    this->field_0x0C = alloc->allocate(100, &params); // +0x0C

    this->field_0x44 = 0; // +0x44
}