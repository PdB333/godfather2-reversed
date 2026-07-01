// FUNC_NAME: SomeManager::sumFloatAtOffsetD0

float __fastcall SomeManager::sumFloatAtOffsetD0(int thisPtr)
{
    // totalSize = count of elements; pointerArray = array of pointers to objects
    uint32_t count = *(uint32_t*)(thisPtr + 0x118);
    uint32_t processed = 0;
    float sum = _DAT_00d5780c;  // global float initializer

    // Process in groups of 4 (unrolled)
    if (count > 3)
    {
        int* ptrArray = (int*)(*(int*)(thisPtr + 0x114) + 8); // +8 to skip first two? Actually base+8, but pointer arithmetic per iteration shifts by 4 ints (16 bytes). Look carefully:
        // The loop increments ptrArray by 4 each iteration (piVar2 = piVar2 + 4). Since pointer to int, that's +16 bytes.
        // But starting from base+8? That's odd. Let's correct:
        // Original: piVar2 = (int *)(*(int *)(param_1 + 0x114) + 8);
        // That means: take the pointer at +0x114, dereference it to get address of array, then add 8 bytes (so skip 2 ints? Or 2 pointers? Actually array of pointers, each 4 bytes, so +8 means skip first two elements). That is suspicious because later they index at piVar2[-2], piVar2[-1], piVar2[0], piVar2[1]. So they start at index 2? That might be an artifact of loop unrolling. Actually the loop processes 4 elements per iteration, but starts at index 2? Wait.

        // Let's reinterpret: The loop intends to process batches of 4. If we start the pointer at the beginning of the array (base), we can use piVar2[-2] etc. But that would underflow for first iteration. So the +8 is to adjust so that piVar2[0] is the third element? That is weird.

        // Actually the original code: piVar2 = base + 8; then it uses piVar2[-2], piVar2[-1], piVar2[0], piVar2[1]. So that accesses elements at indices 0,1,2,3 if base is the start of array? Let's calculate:
        // base = *(+0x114) (pointer to array of ints? Actually array of pointers to objects, each pointer is 4 bytes)
        // piVar2 = base + 8 (bytes) => base + 2 elements (since each element is 4 bytes)
        // piVar2[-2] = element at index 0
        // piVar2[-1] = element at index 1
        // piVar2[0] = element at index 2
        // piVar2[1] = element at index 3
        // So the first batch processes elements 0,1,2,3. Then piVar2 += 4 (add 16 bytes) -> now piVar2 points to element 6? Actually after adding 4 (each int is 4 bytes, so piVar2 = base + 2 + 4 = base + 6 -> piVar2[-2] = element 4, piVar2[-1] = element 5, etc. So it processes elements 4,5,6,7. That works.

        // So the pointer increment by 4 moves to next batch of 4, starting from index 2+4k. This is a standard way to unroll 4-element loops.
        int numBatches = (count - 4) / 4 + 1; // because if count=4, numBatches=1
        processed = numBatches * 4; // but careful: when count=4, numBatches=1, processed=4, correct.
        // But the original computes iVar3 = (uVar1 - 4 >> 2) + 1; which is (count-4)/4 + 1.
        // The loop condition: while (iVar3 != 0) -> decrement iVar3 each iteration.
        // So we'll replicate.

        int iVar3 = (count - 4) / 4 + 1;
        while (iVar3 != 0)
        {
            // For each batch, sum floats at offset 0xd0 from the four objects pointed to by piVar2[-2], piVar2[-1], piVar2[0], piVar2[1].
            sum += *(float*)(*(int*)(piVar2[-2]) + 0xd0)
                 + *(float*)(*(int*)(piVar2[-1]) + 0xd0)
                 + *(float*)(*(int*)(piVar2[0]) + 0xd0)
                 + *(float*)(*(int*)(piVar2[1]) + 0xd0);
            piVar2 += 4;  // advance pointer by 4 ints (16 bytes)
            iVar3--;
        }
    }

    // Process remaining elements (count - processed)
    int remaining = count - processed;
    if (remaining > 0)
    {
        int* ptrArray = (int*)(*(int*)(thisPtr + 0x114) + processed * 4); // start at the first unprocessed element
        while (remaining > 0)
        {
            sum += *(float*)(*(int*)(*ptrArray) + 0xd0);
            ptrArray++;
            remaining--;
        }
    }

    return sum;
}