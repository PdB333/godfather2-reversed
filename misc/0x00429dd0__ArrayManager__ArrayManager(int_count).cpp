// FUNC_NAME: ArrayManager::ArrayManager(int count)
// Address: 0x00429dd0
// This function initializes an ArrayManager object with two arrays of (count+1) ints each.
// The object has an inner structure (0xC bytes) that holds a pointer to the first array.
// Offsets are based on this as an int* (4-byte fields).
// Offset 0: m_pInner - pointer to inner struct (size 0xC)
// Offset 4: m_field1 (set to 0)
// Offset 8: m_count - the number of elements per array (elements = count+1)
// Offset 12: m_global - some global constant (DAT_00e35654)
// Offset 16: m_field4 (set to 0)
// Offset 20: m_pArray2 - second array pointer

struct ArrayManagerInner {
    int field0;               // +0x00 (uninitialized)
    int field1;               // +0x04 (uninitialized)
    int* pArray1;             // +0x08 pointer to first int array
};

// Assume these are memory allocation functions (e.g., malloc/calloc)
extern void* __cdecl allocSmall(int size);        // FUN_009c8e50
extern int* __cdecl allocIntArray(unsigned int size); // FUN_009c8e80

void __thiscall ArrayManager::ArrayManager(int count) {
    int* pInner = (int*)allocSmall(0xC); // allocate inner struct (3 ints)
    if (pInner != 0) {
        // allocate first array: (count+1) ints
        unsigned int arraySize = (count + 1) * 4;
        int* pArray1 = allocIntArray(arraySize);
        *(int**)(pInner + 2) = pArray1; // inner->pArray1 at offset 8
    } else {
        pInner = 0; // redundant, but as per decompiled code
    }
    m_pInner = (ArrayManagerInner*)pInner; // store inner pointer at this+0

    // Initialize outer fields
    m_field1 = 0;
    m_count = count;
    m_global = DAT_00e35654; // some global value
    m_field4 = 0;

    // Zero-initialize the first array (count+1 elements)
    if (m_pInner != 0 && m_pInner->pArray1 != 0) {
        for (unsigned int i = 0; i <= (unsigned int)count; i++) {
            m_pInner->pArray1[i] = 0;
        }
    }

    // Allocate second array: (count+1) ints
    unsigned int arraySize2 = (count + 1) * 4;
    m_pArray2 = allocIntArray(arraySize2);
}