// FUNC_NAME: SystemManager::SystemManager
void SystemManager::SystemManager(void)
{
    // Get global data (likely a singleton pointer)
    uint* globalData = DAT_00e2b1a4;  // +0x0 (some external value)
    // Set vtable pointer (offset 0x0)
    this->vtable = &PTR_FUN_00e30bb4;
    // Initialize a pointer to a string table? (offset +0x0C)
    this->stringTable = &PTR_LAB_00e30bc8;
    // Store pointer to this instance in global static
    DAT_0122339c = this;

    // Set some control flags to 1/0 (offsets relative to this)
    this->flag1 = 1;                                     // +0x04
    this->flag2 = 0;                                     // +0x08
    this->somePointer = &PTR_LAB_00e30bc4;              // +0x0C (reassigned)
    *(byte*)(this + 0x5a) = 0;                           // +0x168? Actually 0x5a*4=0x168 but byte access
    this->field_0x5b = 0;                                // +0x16C
    *(byte*)(this + 0x39) = 0;                           // +0xE4
    *(byte*)((int)this + 0xe5) = 0;                      // +0xE5
    this->field_0x3f = 0;                                // +0xFC
    this->field_0x40 = 0;                                // +0x100
    this->field_0x3e = 0;                                // +0xF8
    this->field_0x3d = 0;                                // +0xF4
    this->field_0x43 = 0;                                // +0x10C
    this->field_0x45 = 0;                                // +0x114
    this->field_0x44 = 0;                                // +0x110
    this->field_0x42 = 0;                                // +0x108
    this->field_0x47 = 0;                                // +0x11C
    this->field_0x4a = 0;                                // +0x128
    this->field_0x49 = 0;                                // +0x124
    this->field_0x48 = 0;                                // +0x120
    this->field_0x4b = globalData;                       // +0x12C
    this->field_0x46 = globalData;                       // +0x118
    this->field_0x41 = globalData;                       // +0x104
    this->field_0x3c = globalData;                       // +0xF0
    this->field_0x4e = 0;                                // +0x138
    this->field_0x4d = 0;                                // +0x134
    this->field_0x4c = 0;                                // +0x130
    this->field_0x51 = 0;                                // +0x144
    this->field_0x50 = 0;                                // +0x140
    this->field_0x4f = 0;                                // +0x13C
    this->field_0x52 = DAT_00e2e714;                     // +0x148
    *(byte*)(this + 0x53) = 0;                           // +0x14C

    // Call an internal init function (likely for other subsystems)
    FUN_00426390();

    // Allocate an array of 4 objects (each 0x1d0 bytes) with custom allocator
    struct AllocHeader {
        int count;       // +0x00
        // followed by array data
    };
    int alignmentParams[3];
    alignmentParams[0] = 2;  // size? No, passed as &alignmentParams
    alignmentParams[1] = 0x10;
    alignmentParams[2] = 0;
    void* memBlock = FUN_009c8ef0(0x750, &alignmentParams);  // size 0x750 (1872 bytes)
    void* arrayData;
    if (memBlock != nullptr) {
        AllocHeader* header = (AllocHeader*)memBlock;
        header->count = 4;
        arrayData = memBlock + 4;  // skip header
        // Initialize each element with constructor
        vector_constructor_iterator_(arrayData, 0x1d0, 4, (void*)&LAB_004a1620);
    } else {
        arrayData = nullptr;
    }
    this->allocatedArray = arrayData;           // +0x10
    this->arrayCount = 4;                       // +0x150
    this->arrayFlag = 1;                        // +0x154

    // Initialize arrays of 4 elements (slots?) at offset 0x158 and 0x2C
    uint slotIndex = 0;
    uint* slotArrayBase = (uint*)(this + 0x56);    // +0x158
    uint* dataBlockBase = (uint*)(this + 0x0b);    // +0x2C

    do {
        // Reset fields in what appears to be a structure per slot
        slotArrayBase[-0x51] = 0;   // +0x14? (0x56-0x51=5 dwords = 0x14 bytes)
        dataBlockBase[-2] = 0;      // +0x24
        dataBlockBase[-1] = 0;      // +0x28
        dataBlockBase[0] = 0;       // +0x2C
        dataBlockBase[1] = 0;       // +0x30
        dataBlockBase[0x1e] = 0;    // +0x2C + 0x1e*4 = +0xA4
        dataBlockBase[0x1f] = 0;    // +0xA8
        dataBlockBase[0x20] = 0;    // +0xAC
        dataBlockBase[0x21] = 0;    // +0xB0
        dataBlockBase[0x0e] = 0;    // +0x64
        dataBlockBase[0x0f] = 0;    // +0x68
        dataBlockBase[0x10] = 0;    // +0x6C
        dataBlockBase[0x11] = 0;    // +0x70

        // Store index in slot array
        *slotArrayBase = slotIndex;

        slotIndex++;
        slotArrayBase++;
        dataBlockBase += 4;  // each slot takes 4 dwords (16 bytes) of the data block? Actually increments by 4 dwords, but offsets above go beyond.
    } while (slotIndex < 4);

    return;
}