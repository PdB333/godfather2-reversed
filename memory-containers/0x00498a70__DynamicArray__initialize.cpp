// FUNC_NAME: DynamicArray::initialize

class DynamicArray
{
public:
    void initialize(uint count);

private:
    struct InternalArrayData
    {
        int field_4;      // +0x04
        int field_8;      // +0x08
        int field_C;      // +0x0C
        int* dataArray;   // +0x10
    };

    InternalArrayData* m_internal;  // +0x00
    int m_initialized;              // +0x04
    uint m_capacity;                // +0x08
    int m_unknownConstant;          // +0x0C
    int m_flags;                    // +0x10
    int* m_extraArray;              // +0x14
};

void DynamicArray::initialize(uint count)
{
    // Allocator functions (likely from EARS memory manager)
    // FUN_009c8e50: allocates raw memory (size in bytes)
    // FUN_009c8e80: allocates and returns pointer (size in bytes)

    m_unknownConstant = DAT_00e35654; // constant, possibly a sentinel or flag
    m_initialized = 0;
    m_capacity = count;
    m_flags = 0;

    // Allocate internal header (size 0x14 = 20 bytes)
    InternalArrayData* header = (InternalArrayData*)FUN_009c8e50(20);
    if (header)
    {
        // Initialize header fields
        header->field_4 = 0;
        header->field_8 = 0;
        header->field_C = 0;
        // Allocate primary data array (count+1 elements)
        header->dataArray = (int*)FUN_009c8e80((count + 1) * 4);
    }
    m_internal = header;

    // Zero out the primary array
    for (uint i = 0; i <= count; i++)
    {
        m_internal->dataArray[i] = 0; // note: potential null dereference if header allocation failed
    }

    // Allocate secondary array (same size)
    m_extraArray = (int*)FUN_009c8e80((count + 1) * 4);
}