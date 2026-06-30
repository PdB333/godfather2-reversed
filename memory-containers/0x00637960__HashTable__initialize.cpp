// FUNC_NAME: HashTable::initialize

void __thiscall HashTable::initialize(Allocator* allocator, int bucketCountLog2)
{
    int* piVar1;
    uint bucketCount;
    int iVar3;
    byte exponent;
    int iVar5;
    // 'this' is unaff_ESI
    int* this;
    
    exponent = (byte)bucketCountLog2;
    bucketCount = 1 << (bucketCountLog2 & 0x1f); // 2^bucketCountLog2 buckets
    
    if (0x18 < bucketCountLog2) {
        errorHandler(allocator, "table overflow"); // FUN_00633920
    }
    
    if (bucketCountLog2 == 0) {
        // Special case: single bucket, use inline storage from allocator
        iVar5 = *(int*)(allocator + 0x10); // allocator->inlineBuffer or current offset
        *(byte*)(this + 7) = exponent; // +0x07: exponent field
        *(int*)(this + 0x10) = iVar5 + 0x40; // +0x10: pointer to array? (offset by 0x40)
        *(int*)(this + 0x14) = iVar5 + 0x2c + bucketCount * 0x14; // +0x14: end pointer
        return;
    }
    
    uVar2 = bucketCount * 0x14; // total memory needed for bucket array (20 bytes per bucket)
    iVar5 = 0;
    if (uVar2 == 0) {
        iVar5 = 0;
    }
    else {
        if (uVar2 < 0xfffffffd) { // sanity check for allocation size
            iVar5 = allocateMemory(0, uVar2); // DAT_012059dc - global alloc? first param likely ignored
            if (iVar5 == 0) {
                if (allocator != 0) {
                    freeMemory(); // FUN_00635a80 - cleanup?
                    return;
                }
                iVar5 = 0;
                goto LAB_006379e3;
            }
        }
        else {
            errorHandler(allocator, "memory allocation error: block too big");
        }
        if (allocator != 0) {
            piVar1 = (int*)(*(int*)(allocator + 0x10) + 0x24); // allocator->currentAllocSize
            *piVar1 = *piVar1 + uVar2; // track allocated size
        }
    }
    
LAB_006379e3:
    *(int*)(this + 0x10) = iVar5; // +0x10: base of bucket array
    
    // Zero-initialize each bucket (3 ints per bucket: at offsets 0, 8, 16 within bucket)
    if (0 < bucketCount) {
        iVar3 = 0;
        iVar5 = bucketCount;
        do {
            *(undefined4*)(*(int*)(this + 0x10) + 0x10 + iVar3) = 0;
            *(undefined4*)(iVar3 + *(int*)(this + 0x10)) = 0;
            *(undefined4*)(*(int*)(this + 0x10) + 8 + iVar3) = 0;
            iVar3 = iVar3 + 0x14; // next bucket
            iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
    }
    
    *(byte*)(this + 7) = exponent; // +0x07: store exponent
    *(int*)(this + 0x14) = *(int*)(this + 0x10) + (bucketCount - 1) * 0x14; // +0x14: pointer to last bucket
    return;
}