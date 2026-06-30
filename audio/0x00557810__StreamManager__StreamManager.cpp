// FUNC_NAME: StreamManager::StreamManager
// Address: 0x00557810
// Role: Constructor for a streaming-related class (likely base stream manager)
// The class sets up vtables, stores parameters, and initializes a sub-object (stream handle)

void __thiscall StreamManager::StreamManager(int param1, int param2)
{
    // Debug/log call with argument 0x1e (30)
    // Probably logMessage or debugPrint
    FUN_00a72c80(0x1e);

    // Set vtable at offset 0x00
    this->vtable = &PTR_FUN_00e39ff4;
    // Set secondary vtable at offset 0x10 (unaff_ESI[4])
    this->secondaryVtable = &PTR_LAB_00e3a018; // +0x10
    // Store param2 at offset 0x18 (unaff_ESI[6])
    this->field_0x18 = param2;
    // Store param1 at offset 0x34 (unaff_ESI[0xd])
    this->field_0x34 = param1;
    // Zero out fields at offsets 0x38, 0x3c, 0x40, 0x44
    this->field_0x38 = 0;
    this->field_0x3c = 0;
    this->field_0x40 = 0;
    this->field_0x44 = 0;
    // Set byte at offset 0x48 to 1
    *(unsigned char*)((int)&this->field_0x48) = 1;

    // Allocate a 20-byte sub-object (struct/stream handle)
    int* subObject = (int*)FUN_009c8e50(0x14);
    if (subObject != nullptr)
    {
        // Local variables for initialization
        int local_c = 2;
        int local_8 = 0x10;
        int local_4 = 0;

        // Get a manager/allocator pointer
        int* allocator = (int*)FUN_009c8f80();

        // Call a function that returns something stored at subObject[3]
        subObject[3] = FUN_004265d0(&local_c, allocator);
        // Store allocator at subObject[4]
        subObject[4] = (int)allocator;

        // Call a virtual function on the allocator (third vtable entry, offset 8)
        // Typically an initialization or acquire call
        (**(code**)(*allocator + 8))();

        // Zero first three fields of subObject
        subObject[0] = 0;
        subObject[2] = 0;
        subObject[1] = 0;

        // Store subObject pointer at offset 0x30 (unaff_ESI[0xc])
        this->subObject = subObject;
    }
    else
    {
        this->subObject = nullptr;
    }
}