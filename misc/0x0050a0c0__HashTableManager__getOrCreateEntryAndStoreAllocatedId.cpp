// FUNC_NAME: HashTableManager::getOrCreateEntryAndStoreAllocatedId
void HashTableManager::getOrCreateEntryAndStoreAllocatedId(uint param_1, uint param_2, int param_3)
{
    int iVar1;
    uint* puVar2;
    undefined4 uVar3;
    uint uVar4;
    // Allocation parameters: type=2, size=0x10, flags=0
    undefined4 local_c = 2;
    undefined4 local_8 = 0x10;
    undefined4 local_4 = 0;
    // Allocate a resource ID (e.g., a handle or index)
    uVar3 = MemoryManager::allocate(0x50, &local_c);  // 0x50 likely size or type
    // Access global hash table manager (DAT_01223398)
    iVar1 = *(int*)(DAT_01223398 + 8);  // +8 is pointer to table structure
    // Compute bucket index using param_2 (the key)
    uint bucketIndex = param_2 % *(uint*)(iVar1 + 8);  // +8 is number of buckets
    // Get first entry in the bucket (array of pointers at iVar1+4)
    puVar2 = *(uint**)(*(int*)(iVar1 + 4) + bucketIndex * 4);
    do {
        if (puVar2 == (uint*)0x0) {
LAB_0050a11b:
            uVar4 = 0;
            goto LAB_0050a11d;
        }
        // Check if key matches (first word is key)
        if (*puVar2 == param_2) {
            // If entry exists, retrieve its value (second word is value)
            if ((puVar2 != (uint*)0x0) && (puVar2 + 1 != (uint*)0x0)) {
                uVar4 = puVar2[1];  // value is the object pointer
                goto LAB_0050a11d;
            }
            goto LAB_0050a11b;
        }
        // Follow next pointer (third word is next)
        puVar2 = (uint*)puVar2[2];
    } while (true);

LAB_0050a11d:
    // Update param_2 to the allocated ID
    param_2 = uVar3;
    // Insert or update hash entry (first param is pointer to this?,
    // second is pointer to key/value, third is bucket index)
    HashTableInsertOrUpdate(&param_1, &param_2, param_1 % *(uint*)(iVar1 + 8));
    // Store the allocated ID into the object's array at offset 0x54 + param_3*4
    *(undefined4*)(*(int*)(uVar4 + 0x54) + param_3 * 4) = uVar3;
    return;
}