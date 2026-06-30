// FUNC_NAME: ContainerClass::Initialize (guessed)

int ContainerClass::Initialize(int param_1, int *this) // __thiscall, param_1 unknown, this = param_2
{
    int *bufferPtr;        // pointer to element buffer
    int defaultVal;        // default fill value
    int cap;               // requested capacity
    int oldCap;            // current capacity (masked)
    int iVar6;             // loop index
    int iVar7;             // loop counter
    int newBlock;          // allocated header block
    int container;         // container object (result of getContainer)
    int numElements;       // number of elements to fill
    int iVar4;             // temporary

    // Get initial capacity from base class virtual function (vtable offset 0x220)
    cap = (*(int (__thiscall **)(int *))(*(int *)this + 0x220))(this);

    // TLS usage (likely per-thread allocator)
    TlsGetValue(DAT_01139810);

    // Allocate a new block of size 0x18, pool tag 0xb
    newBlock = FUN_00aa2680(0x18, 0xb);
    // Set size field at offset +4 (two bytes)
    *(unsigned short *)(newBlock + 4) = 0x18;

    // Obtain the container object (this may be a static or member pointer)
    container = FUN_00bef230();

    // Container layout:
    // +0x08: pointer to element buffer (int*)
    // +0x0c: current element count (written later)
    // +0x10: current capacity (lower 30 bits)
    bufferPtr = (int *)(container + 8);
    oldCap = *(int *)(container + 0x10) & 0x3fffffff;

    // If current capacity is less than requested, reallocate buffer
    if (oldCap < cap)
    {
        numElements = oldCap * 2;
        if (numElements <= cap)
        {
            numElements = cap;
        }
        // Reallocate buffer: new capacity numElements, element size 0xc
        FUN_00aa4110(bufferPtr, numElements, 0xc);
    }

    defaultVal = DAT_00e2b1a4; // global default value (probably 0 or -1)
    numElements = 0;
    // Store the new capacity (or element count?) at offset +0x0c
    *(int *)(container + 0xc) = cap;

    // Initialize elements in groups of 4 (each element is 0xc bytes = 3 ints)
    if (3 < cap)
    {
        iVar6 = 0;
        // Number of groups of 4 elements
        iVar7 = (cap - 4 >> 2) + 1;
        numElements = iVar7 * 4;
        do
        {
            // For each group, set only the first two ints of each element
            // Offsets: 0,4  (first element); 0xc,0x10 (second); 0x18,0x1c (third); 0x24,0x28 (fourth)
            *(int *)(iVar6 + *bufferPtr) = defaultVal;
            *(int *)(iVar6 + 4 + *bufferPtr) = defaultVal;
            *(int *)(iVar6 + 0xc + *bufferPtr) = defaultVal;
            *(int *)(iVar6 + 0x10 + *bufferPtr) = defaultVal;
            *(int *)(iVar6 + 0x18 + *bufferPtr) = defaultVal;
            *(int *)(iVar6 + 0x1c + *bufferPtr) = defaultVal;
            *(int *)(iVar6 + 0x24 + *bufferPtr) = defaultVal;
            *(int *)(iVar6 + 0x28 + *bufferPtr) = defaultVal;
            iVar6 += 0x30; // 0x30 = 4 elements * 0xc
            --iVar7;
        } while (iVar7 != 0);
    }

    // Handle remaining elements (less than 4)
    if (numElements < cap)
    {
        iVar6 = numElements * 0xc;
        iVar7 = cap - numElements;
        do
        {
            // Set first two ints of each remaining element
            *(int *)(iVar6 + *bufferPtr) = defaultVal;
            *(int *)(iVar6 + 4 + *bufferPtr) = defaultVal;
            iVar6 += 0xc;
            --iVar7;
        } while (iVar7 != 0);
    }

    // Call another initialization function (possibly for the container itself)
    FUN_00548440(param_1, this);
    return container; // return the container object pointer
}