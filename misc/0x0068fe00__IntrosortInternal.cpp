// FUNC_NAME: IntrosortInternal

void IntrosortInternal(int* arrayStart, int* arrayEnd, int depthLimit, void* compareContext)
{
    int partitionPos;
    int pivotRight;   // local_8: right partition end after partition
    int pivotLeft;    // local_4: left partition start after partition

    int elementCount = (arrayEnd - arrayStart) >> 2; // number of 4-byte elements

    do {
        elementCount = elementCount >> 2; // Actually recalculated each iteration? The original uses iVar1 = param_2 - param_1; then iVar1 >>= 2 each loop. That seems wrong. Let's re-evaluate.

        // Wait, the decompiled code has iVar1 = param_2 - param_1; then repeatedly iVar1 = iVar1 >> 2; That's odd. Let's re-read:
        // iVar1 = param_2 - param_1;
        // do {
        //   iVar1 = iVar1 >> 2;
        //   if (iVar1 < 0x21) ...
        // } while (true);
        // So each iteration reduces iVar1 by shifting right by 2 (divide by 4)??? That would shrink quickly. But that can't be right. Probably the decompiler misrepresented the loop. The original likely compares the element count (size / 4) each time. We'll interpret it as checking if ( (end-start)/4 < 33 ).

        // Let's extract the actual logic from the decompiled pseudocode:

        // iVar1 = param_2 - param_1;   // byte difference
        // do {
        //   iVar1 = iVar1 >> 2;        // element count (since 4 bytes per element)
        //   if (iVar1 < 0x21) {        // less than 33 elements?
        //       if (1 < iVar1) {
        //           FUN_0068f510(param_1,param_2,param_4); // insertion sort
        //       }
        //       return;
        //   }
        //   if (param_3 < 1) {         // depth limit exhausted?
        //       if (0x20 < iVar1) {    // but iVar1 already < 0x21? Actually inverted logic.
        //           // Actually the condition: if (param_3 < 1) {
        //           //     if (0x20 < iVar1) { // iVar1 already < 0x21 from earlier check? This path is if iVar1 >= 0x21? But we already checked iVar1 < 0x21 above? This is confusing.
        //           // } else { goto LAB_0068fe97; }
        //       }
        //   } else {
        //       // do partition
        //   }
        // } while( true );

        // The decompiled code seems to have a control flow issue due to Ghidra's decompilation. I'll reconstruct a standard introsort logic:

        int size = (arrayEnd - arrayStart) >> 2; // element count
        if (size <= 32) {
            if (size > 1) {
                InsertionSort(arrayStart, arrayEnd, compareContext);
            }
            return;
        }

        if (depthLimit <= 0) {
            // Use heap sort for the whole range
            HeapSort(arrayStart, arrayEnd, compareContext);
            return;
        }

        // partition: returns pivot positions
        PartitionMedianOfThree(arrayStart, arrayEnd, compareContext, &pivotLeft, &pivotRight);
        // pivotLeft and pivotRight are the boundaries of the pivot section (like left and right of pivot)

        int leftSize = (pivotLeft - arrayStart) >> 2;
        int rightSize = (arrayEnd - pivotRight) >> 2;

        // Recursively sort the smaller partition first to limit stack depth
        if (leftSize < rightSize) {
            IntrosortInternal(arrayStart, pivotLeft, depthLimit - 1, compareContext);
            arrayStart = pivotRight;
        } else {
            IntrosortInternal(pivotRight, arrayEnd, depthLimit - 1, compareContext);
            arrayEnd = pivotLeft;
        }

        // Update depth limit for the next iteration (the original uses param_3 = param_3 / 2 + (param_3 / 2)/2 which is approximately param_3 * 0.75? Actually param_3 = param_3/2 + (param_3/2)/2 = param_3/2 + param_3/4 = 3*param_3/4. So depth limit is reduced by a factor 3/4 each recursion? That's unusual. In introsort, depth limit is usually log2(n) and decreases by 1 each recursion. This code seems to have a different scheme. Possibly it is a different algorithm.

        // The original code: param_3 = param_3 / 2 + (param_3 / 2) / 2; That is param_3 = (param_3/2) + (param_3/4) = 3*param_3/4. This is not standard. Maybe it's a heuristic for shallow recursion? I'll replicate as given.

        depthLimit = depthLimit / 2 + (depthLimit / 2) / 2; // roughly 0.75 * depthLimit

        // Recalculate elementCount for the new range? The original loop uses iVar1 from param_2 - param_1, which has been updated. So we need to update elementCount accordingly.

        elementCount = (arrayEnd - arrayStart) >> 2;

    } while (true);
}