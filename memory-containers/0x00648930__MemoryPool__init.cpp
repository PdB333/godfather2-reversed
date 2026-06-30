// FUNC_NAME: MemoryPool::init
void MemoryPool::init(void)
{
    // Zero first 3 bytes (perhaps flags or small counters)
    this->field_00[0] = 0;
    this->field_00[1] = 0;
    this->field_00[2] = 0;

    // Set default packet size or maximum block size to 16
    this->maxPacketSize = 0x10;          // +0x178

    // Zero some configuration fields
    this->field_17c = 0;                 // +0x17c

    // Store memory operation function pointers
    this->memcpyFunc = _memcpy;          // +0x180
    this->memsetFunc = _memset;          // +0x184

    // Store static addresses (likely virtual tables or static data)
    this->vtableOrData1 = &LAB_0064acb0; // +0x188

    // Initialize remaining fields to zero
    this->field_18c = 0;                 // +0x18c
    this->field_190 = 0;                 // +0x190
    this->field_194 = 0;                 // +0x194
    this->field_198 = 0;                 // +0x198
    this->field_19c = 0;                 // +0x19c

    // Set alignment or stream count to 4
    this->alignmentOrStreamCount = 4;    // +0x1a0

    // More static addresses
    this->vtableOrData2 = &LAB_00649db0; // +0x1a4
    this->field_1a8 = 0;                 // +0x1a8
    this->vtableOrData3 = &LAB_0064ac80; // +0x1ac
    this->field_1b0 = 0;                 // +0x1b0

    // Version or ID fields
    this->field_1b4 = 9;                 // +0x1b4
    this->field_1b5 = 10;                // +0x1b5
    this->field_1b6 = 0;                 // +0x1b6

    // Zero more fields
    this->field_1b8 = 0;                 // +0x1b8
    this->field_1c0 = 0;                 // +0x1c0, +0x1c8?
    this->field_1c8 = 0;                 // +0x1c8
    this->field_1d0 = 0;                 // +0x1d0
    this->field_1d8 = 0;                 // +0x1d8

    // Call sub-initialization
    subInit_00649ec0();

    // Initialize first linked list (possibly main free list)
    // Node at offset 4 in this structure
    this->listRoot = 0;                  // +0x04
    this->listNext = 0;                  // +0x0c
    this->listPrev = 0;                  // +0x14
    this->listHead = 0;                  // +0x1c, set to &listRoot
    this->listTail = 0;                  // +0x18, set to &listRoot
    this->listHead = &this->listRoot;    // +0x1c = this+4
    this->listTail = &this->listRoot;    // +0x18 = this+4

    // Clear next fields
    this->field_2c = 0;                  // +0x2c
    this->field_34 = 0;                  // +0x34
    this->field_3c = 0;                  // +0x3c

    // Clear and set up buffer for fixed-size blocks (256 bytes at +0x78)
    char* buffer = &this->buffer[0];     // +0x78
    _memset(buffer, 0, 0x100);

    // Initialize multiple free lists with sentinel nodes inside the buffer
    // Each sentinel occupies 8 bytes (two pointers) at specific offsets in buffer
    // List 0: sentinel at buffer[0] (offset 0 in buffer)
    this->list0Head = buffer;            // +0x8c? Wait, careful with offsets
    this->list0Tail = buffer;            // +0x90? The code shows +0x8c and +0x90

    // List 1: sentinel at buffer[0x20] (offset 0x98 - 0x78 = 0x20)
    this->list1Head = &buffer[0x20];     // +0xac
    this->list1Tail = &buffer[0x20];     // +0xb0

    // List 2: sentinel at buffer[0x40] (offset 0xb8 - 0x78 = 0x40)
    this->list2Head = &buffer[0x40];     // +0xcc
    this->list2Tail = &buffer[0x40];     // +0xd0

    // List 3: sentinel at buffer[0x60] (offset 0xd8 - 0x78 = 0x60)
    this->list3Head = &buffer[0x60];     // +0xec
    this->list3Tail = &buffer[0x60];     // +0xf0

    // List 4: sentinel at buffer[0x80] (offset 0xf8 - 0x78 = 0x80)
    this->list4Head = &buffer[0x80];     // +0x10c
    this->list4Tail = &buffer[0x80];     // +0x110

    // List 5: sentinel at buffer[0xa0] (offset 0x118 - 0x78 = 0xa0)
    this->list5Head = &buffer[0xa0];     // +0x12c
    this->list5Tail = &buffer[0xa0];     // +0x130

    // List 6: sentinel at buffer[0xc0] (offset 0x138 - 0x78 = 0xc0)
    this->list6Head = &buffer[0xc0];     // +0x14c
    this->list6Tail = &buffer[0xc0];     // +0x150

    // List 7: sentinel at buffer[0xe0] (offset 0x158 - 0x78 = 0xe0)
    this->list7Head = &buffer[0xe0];     // +0x16c
    this->list7Tail = &buffer[0xe0];     // +0x170
}