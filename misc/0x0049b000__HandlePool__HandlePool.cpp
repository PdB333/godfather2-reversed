// FUNC_NAME: HandlePool::HandlePool
// Reconstructed constructor for a HandlePool class (16 slots, 64-bit handles)
// Function address: 0x0049b000
// Identified role: Initializes a pool of 16 handles (index + generation) and four free-list pointers

struct Handle64 {
    int index;      // +0x00 (low 32 bits)
    int generation; // +0x04 (high 32 bits, always 0 initially)
};

class HandlePool {
public:
    void **vtable;          // +0x00
    int m_field1;           // +0x04 (set to 0 after constructor, initial invalid -1)
    int m_field2;           // +0x08 (set to 1 after constructor, initial invalid -1)
    int m_field3;           // +0x0C (set to 2 after constructor, initial invalid -1)
    int m_field4;           // +0x10 (set to 3 after constructor, initial invalid -1)
    int pad;                // +0x14 (uninitialized)
    Handle64 handles[16];   // +0x18 (array of 16 handles, each 8 bytes)
    // Total size: 0x18 + 16*8 = 0x98 bytes (152 bytes)
};

HandlePool::HandlePool() {
    // Set vtable pointer
    vtable = &PTR_LAB_00e35174;

    // ---- Initialize handles array to zeros (by copying the first two zero words) ----
    // Set first two handle words (handles[0].index and handles[0].generation) to 0
    handles[0].index = 0;
    handles[0].generation = 0;

    // Copy the first two zeros into the remaining 30 words (offsets 0x20..0x94)
    // This effectively zeros the entire handles array before explicit fill.
    int *src = (int*)((char*)this + 0x18);   // &handles[0].index
    int *dst = (int*)((char*)this + 0x20);   // &handles[2].index
    for (int i = 0; i < 0x1e; i++) {
        *dst++ = *src++;
    }

    // ---- Initialise four fields with invalid values (later overwritten) ----
    m_field1 = -1;
    m_field2 = -1;
    m_field3 = -1;
    m_field4 = -1;

    // ---- Fill handles with consecutive indices and generation=0 ----
    int *handleBase = (int*)&handles[0].index;   // start of handles array
    int index = 0;
    do {
        handleBase[0] = index;          // low part = index
        handleBase[1] = index >> 31;    // high part = sign extension (always 0 for index >=0)
        index++;
        handleBase += 2;                // advance to next handle
    } while (index != 0x10);

    // ---- Overwrite the four field variables with sequential values 0,1,2,3 ----
    int *fieldBase = &m_field1;
    index = 0;
    do {
        *fieldBase = index;
        index++;
        fieldBase++;
    } while (index != 4);
}