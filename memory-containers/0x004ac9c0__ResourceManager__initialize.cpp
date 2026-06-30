// FUNC_NAME: ResourceManager::initialize
void ResourceManager::initialize(void* parentObject)
{
    // Set vtable pointer to global vtable table
    this->vtablePtr = &PTR_FUN_00e356f0;

    // Zero out temporary struct (maybe for resource creation)
    int temp[3] = {0, 0, 0};

    // Initialize resource slot 0
    {
        ResourceHandle handle = createResourceHandle(temp); // FUN_004265d0
        this->slot0.handle = handle;
        this->slot0.allocator = this->m_allocator;
        this->m_allocator->allocate(); // Call virtual function at offset 8
        // Zero three status fields for slot 0
        this->slot0.field1 = 0;
        this->slot0.field2 = 0;
        this->slot0.field3 = 0;
    }

    // Initialize resource slot 1 (offsets 0xb, 0xc; zero 8,10,9)
    {
        ResourceHandle handle = createResourceHandle(temp);
        this->slot1.handle = handle;
        this->slot1.allocator = this->m_allocator;
        this->m_allocator->allocate();
        this->slot1.field1 = 0;
        this->slot1.field2 = 0;
        this->slot1.field3 = 0;
    }

    // Initialize resource slot 2 (offsets 0x10,0x11; zero 0xd,0xf,0xe)
    {
        ResourceHandle handle = createResourceHandle(temp);
        this->slot2.handle = handle;
        this->slot2.allocator = this->m_allocator;
        this->m_allocator->allocate();
        this->slot2.field1 = 0;
        this->slot2.field2 = 0;
        this->slot2.field3 = 0;
    }

    // Initialize resource slot 3 (offsets 0x15,0x16; zero 0x12,0x14,0x13)
    {
        ResourceHandle handle = createResourceHandle(temp);
        this->slot3.handle = handle;
        this->slot3.allocator = this->m_allocator;
        this->m_allocator->allocate();
        this->slot3.field1 = 0;
        this->slot3.field2 = 0;
        this->slot3.field3 = 0;
    }

    // Initialize resource slot 4 (offsets 0x1a,0x1b; zero 0x17,0x19,0x18)
    {
        ResourceHandle handle = createResourceHandle(temp);
        this->slot4.handle = handle;
        this->slot4.allocator = this->m_allocator;
        this->m_allocator->allocate();
        this->slot4.field1 = 0;
        this->slot4.field2 = 0;
        this->slot4.field3 = 0;
    }

    // Initialize resource slot 5 (offsets 0x1f,0x20; zero 0x1c,0x1e,0x1d)
    {
        ResourceHandle handle = createResourceHandle(temp);
        this->slot5.handle = handle;
        this->slot5.allocator = this->m_allocator;
        this->m_allocator->allocate();
        this->slot5.field1 = 0;
        this->slot5.field2 = 0;
        this->slot5.field3 = 0;
    }

    // Zero out additional fields
    this->flagsLow = 0;   // 16-bit at offset 0x18 (byte offset 24)
    this->flagsHigh = 0;  // 16-bit at offset 0x1a (byte offset 26)
    this->extraField = 0; // int at offset 0x1c (byte offset 28)

    // Store the parent object pointer
    this->parentObject = parentObject; // offset 0x84
}

// ResourceHandle createResourceHandle(int temp[3]) is defined elsewhere