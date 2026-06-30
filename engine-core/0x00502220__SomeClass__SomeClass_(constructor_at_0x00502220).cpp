// FUNC_NAME: SomeClass::SomeClass (constructor at 0x00502220)
// Reconstructed constructor for an object allocated with alignment, then inserted into a hash table keyed by param_1.
// The vtable pointer is set to PTR_FUN_00e37e0c (likely a class vtable).
// Fields are stored at offsets: +0x04, +0x08, +0x0C, +0x10, +0x14, +0x18, +0x1C (7 fields + vtable at +0x00).
// The last field (+0x1C) is zeroed.
// Then the object is inserted into a hash table via FUN_00423cf0, using param_1 as key and a hash computed from param_1 modulo a table size.

void SomeClass::SomeClass(uint* param_1, uint param_2, uint param_3, uint param_4, uint param_5, uint param_6, uint param_7)
{
    uint alignmentArray[4];
    alignmentArray[1] = 2;   // alignment? (maybe 2 bytes)
    alignmentArray[2] = 0x10; // alignment? (16 bytes)
    alignmentArray[3] = 0;    // flags?

    // Allocate 0x34 bytes with alignment info
    uint* newObj = (uint*)FUN_009c8ed0(0x34, &alignmentArray[1]);
    if (newObj == nullptr) {
        newObj = nullptr;
    } else {
        newObj[0] = (uint)&PTR_FUN_00e37e0c; // vtable pointer
        newObj[1] = param_2;                 // +0x04
        newObj[2] = param_6;                 // +0x08
        newObj[3] = param_7;                 // +0x0C
        newObj[4] = param_3;                 // +0x10
        newObj[5] = param_4;                 // +0x14
        newObj[6] = param_5;                 // +0x18
        newObj[7] = 0;                       // +0x1C (zeroed)
    }

    // Prepare key for hash table insertion
    uint key = (uint)param_1;
    // Hash table size is stored at DAT_01223398 + 8 -> *(int*)(DAT_01223398+8) -> then +8 gives size
    uint tableSize = *(uint*)(*(int*)(DAT_01223398 + 8) + 8);
    uint hashIndex = key % tableSize;

    // Insert into hash table: FUN_00423cf0 takes key array, pointer to object, and hash index
    uint keyArray[1];
    keyArray[0] = key;
    uint* objPtr = newObj; // param_1 is overwritten with newObj for the call
    FUN_00423cf0(keyArray, &objPtr, hashIndex);
}