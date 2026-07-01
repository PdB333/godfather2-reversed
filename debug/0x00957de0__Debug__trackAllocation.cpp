// FUNC_NAME: Debug::trackAllocation

void __fastcall Debug::trackAllocation(void* thisPtr)
{
    // +0x10 likely vtable pointer? But we dereference +0x10 to get another pointer, then +4 to get a function.
    // +0x4a is flags (bit 1 = 2 means "initialized"?)
    // +0x49 and +0x48 are some state bytes (1 and 0)
    // +0x44 stores result of vtable function (probably thread ID or timestamp)
    // +0x18: count of allocation records
    // +0x1c: capacity of allocation records
    // +0x14: pointer to array of 0x18-sized records (6 dwords)
    // Record layout:
    //   [0] = source identifier (e.g. module name)
    //   [1] = address of allocation? (DAT_0120565c)
    //   [2] = size? (0)
    //   [3] = callback function? (LAB_005bfd90)
    //   [4] = some flag? (0)
    //   [5] = reference count? (1)

    if (*(byte *)((int)thisPtr + 0x4a) & 2)
        return;

    // Fetch a function pointer from a vtable-like structure
    // +0x10 points to a base, +4 is the function offset
    auto vtableFunc = *(code **)(*(int *)((int)thisPtr + 0x10) + 4);

    *(byte *)((int)thisPtr + 0x49) = 1;
    *(byte *)((int)thisPtr + 0x48) = 0;

    // Call the vtable function – likely returns a unique identifier (thread ID or sequence)
    int threadId = vtableFunc();
    *(int *)((int)thisPtr + 0x44) = threadId;

    // Check some global condition
    if (FUN_005c0830(&DAT_00e3e658) < 0)
    {
        // Increment allocation record count
        int* countPtr = (int*)((int)thisPtr + 0x18);
        int newCount = *countPtr + 1;
        if (*(int*)((int)thisPtr + 0x1c) < newCount)
        {
            // Reallocate array to hold more records (0x18 bytes each)
            *(int*)((int)thisPtr + 0x14) = FUN_005c27a0(
                *(int*)((int)thisPtr + 0x14), newCount, 0x18, countPtr, (int*)((int)thisPtr + 0x1c));
        }
        // Write a new record at the end of the array
        int* record = (int*)(*(int*)((int)thisPtr + 0x14) + *countPtr * 0x18);
        *countPtr = newCount;
        record[0] = (int)&DAT_00e3e658;      // source identifier (e.g. module)
        record[1] = (int)&DAT_0120565c;      // allocation address or log name
        record[2] = 0;                        // size (unknown)
        record[3] = (int)&LAB_005bfd90;      // callback (e.g. destructor or cleanup)
        record[4] = 0;                        // flag
        record[5] = 1;                        // reference count
    }

    FUN_005c0890(); // Post-logging cleanup? e.g. flush buffer

    // Mark as initialized
    *(unsigned short*)((int)thisPtr + 0x4a) |= 2;
}