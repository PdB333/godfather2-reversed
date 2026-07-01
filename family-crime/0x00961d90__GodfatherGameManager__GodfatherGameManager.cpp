// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Function address: 0x00961d90
// Role: Constructor for the GodfatherGameManager singleton, initializes vtable pointers, members, and allocates/initializes a large internal buffer.

void * __fastcall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager *this)
{
    void *allocatedBuffer;

    // Base class initialization (likely Engine::Object or similar)
    BaseClassConstructor();

    // Set vtable pointers:
    // Offset +0x00: primary vtable
    // Offset +0x10: secondary vtable (offset 4 in dword units)
    // Offset +0x4C: another vtable (offset 0x13 in dword units)
    this->vtable0 = (void **)&VTABLE_FUN_00d8d740;
    this->vtable4 = (void **)&PTR_LAB_00d8d718;   // likely interface vtable
    this->field_0x4C = (void **)&PTR_LAB_00d8d714; // perhaps another interface

    // Initialize singleton global pointer
    gpGodfatherGameManager = this;

    // Zero-initialize various member fields
    this->field_0x50 = 0;    // +0x50 (param_1[0x14])
    this->field_0x54 = 0;    // +0x54 (param_1[0x15])
    this->field_0x5C = 0;    // +0x5C (param_1[0x17])
    this->field_0x60 = 0;    // +0x60 (param_1[0x18])
    this->field_0x64 = 0;    // +0x64 (param_1[0x19])
    this->field_0x68 = 0;    // +0x68 (param_1[0x1a])

    this->field_0x6C = 0x7BB;    // +0x6C: likely version/constant (1979 decimal)
    this->field_0x70 = -1;       // +0x70: initialized to -1

    // Allocate a large buffer (size 0xA0C = 2572 bytes) for internal data
    allocatedBuffer = AllocateMemory(0xA0C);
    if (allocatedBuffer != nullptr)
    {
        // Initialize the allocated buffer: zero first word, then two fields at offsets 0xA04 and 0xA06
        *(int *)allocatedBuffer = 0;
        *(int *)((char *)allocatedBuffer + 0xA04) = 0;
        *(char *)((char *)allocatedBuffer + 0xA06) = 0;   // byte field

        this->field_0x84 = allocatedBuffer;  // +0x84 (param_1[0x21])
    }
    else
    {
        this->field_0x84 = nullptr;
    }

    return this;
}