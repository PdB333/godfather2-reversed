// FUNC_NAME: EntitySerializer::packToBitBuffer

void __thiscall EntitySerializer::packToBitBuffer(int this) // this = param_1
{
    int eax; // return value from hashTableCreate
    int edi; // unaff_EDI - likely a global or parameter (e.g., entity pointer)
    // Local variables from decompilation
    char local_53d; // version/type = 3
    undefined** local_53c; // pointer to global table PTR_LAB_00e42f38
    int local_538, local_534; // counters or sizes
    undefined4 local_52c; // 0x400 (1024)
    char *local_530; // pointer to local buffer
    undefined4 local_510, local_50c; // 0x2000 (8192) - hash table sizes
    char local_528; // flag
    int local_524; // bit count (?) initialized to 0
    char local_520, local_51f; // reserved
    undefined4 local_508; // reserved
    char local_504; // reserved
    char local_404[1028]; // main output buffer

    if (edi != 0) {
        // Initialize local variables for hash table or bit stream
        local_530 = local_404;
        local_510 = 0x2000;  // 8192 bits (1024 bytes)
        local_50c = 0x2000;
        local_538 = 0;
        local_534 = 0;
        local_52c = 0x400;   // 1024 bits (128 bytes)
        local_528 = 0;
        local_524 = 0;
        local_520 = 0;
        local_51f = 0;
        local_504 = 0;
        local_508 = 0;
        local_53c = &PTR_LAB_00e42f38; // external global table
        local_53d = 3;                  // version/type indicator

        // Create/initialize a hash table (or similar structure)
        // First call: type=8, data=&local_53d (value 3)
        eax = hashTableCreate(8, &local_53d);
        // Subsequent writes to the created structure at offsets
        hashTableWrite(0x40, eax + 3);   // write 64 bytes at offset 3
        hashTableWrite(0x40, eax + 0xb); // write 64 bytes at offset 11

        // Clear the entity's memory region? (unlikely, but 0xff fill)
        memClear(edi, 0xff); // Actually FUN_0064c760 could be memset with 0xFF

        // Pack bits from this object's member at offset 0x5c into local buffer
        // Third argument: number of bytes = (local_524 + 7) >> 3, but local_524 is 0 => 0 bytes.
        // Possibly it's updated by previous calls? We assume it's correct.
        packBitsFromObject(this + 0x5c, local_404, (local_524 + 7) >> 3, 1);

        // Finalize packing/compression
        finalizePacking();
    }
}