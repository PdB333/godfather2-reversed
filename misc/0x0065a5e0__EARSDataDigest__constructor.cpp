// FUNC_NAME: EARSDataDigest::constructor
undefined4* __thiscall EARSDataDigest::constructor(EARSDataDigest* this, EARSDataDigest* digestObj)
{
    undefined8 hashPart1;
    undefined8 hashPart2;
    int hashSize;
    undefined4 local_10a0 [1063]; // Temporary hash state buffer
    undefined8 localInitHash1; // Local initial hash if size != 0x20
    undefined8 localInitHash2; // Local initial hash if size != 0x20

    // Initialize vtable pointer and clear flags
    digestObj[0] = &PTR_LAB_00e433dc; // Set vtable
    digestObj[1] = 0; // +0x04: flags/counter
    digestObj[2] = 0; // +0x08: maybe byte count

    // Check if the digest size is 0x20 (32 bytes, i.e., SHA256)
    hashSize = *(int*)(this + 0x10);
    if (hashSize == 0x20) {
        // Compute initial hash from data at this+0xc with size 0x10, flags=0
        // Store result in local_10a0 (temporary buffer)
        FUN_00660a10(*(undefined4*)(this + 0xc), 0x10, 0, local_10a0);
        // Copy the first 16 bytes from computed hash into digest object
        int dataPtr = *(int*)(this + 0xc);
        *(undefined8*)(digestObj + 7) = *(undefined8*)(dataPtr + 0x10); // +0x1c
        hashPart1 = *(undefined8*)(dataPtr + 0x18); // Next 8 bytes at +0x18
    } else {
        // For other sizes, use zero-initialized hash
        localInitHash1 = 0;
        localInitHash2 = 0;
        FUN_00660a10(&localInitHash1, 0x10, 0, local_10a0);
        *(undefined8*)(digestObj + 7) = localInitHash1;
        hashPart1 = localInitHash2;
    }

    // Copy 0x81 dwords (0x204 bytes) from temporary buffer to digest object at offset 0x6c
    undefined4* src = local_10a0;
    undefined4* dst = digestObj + 0x1b; // +0x6c
    for (int i = 0x81; i != 0; i--) {
        *dst = *src;
        src++;
        dst++;
    }

    // Set the second part of the hash (8 bytes) at offset 0x24
    *(undefined8*)(digestObj + 9) = hashPart1; // +0x24? Actually +0x24 = 0x24
    // Duplicate the initial hash parts to offsets 0x0c and 0x14
    *(undefined8*)(digestObj + 3) = *(undefined8*)(digestObj + 7); // +0x0c
    *(undefined8*)(digestObj + 5) = *(undefined8*)(digestObj + 9); // +0x14

    // Finalize/combine hash using temporary buffer
    FUN_00661210(digestObj + 3, digestObj + 0x17, local_10a0); // +0x0c, +0x5c, temp

    // Clear a flag at offset 0x270
    digestObj[0x9c] = 0; // +0x270

    return digestObj;
}