// FUNC_NAME: mergeDataArrays

// Address: 0x008d6740
// Role: Merges two arrays (int array and struct array) into a combined output. 
// The arrays are obtained via subroutines and compared by sizes/keys to select merge method.

void mergeDataArrays(void** outArray) // outArray is pointer to be filled with result
{
    int* arrayA; // local_48
    int sizeA;   // local_58
    int offsetA; // local_54[0] - extra offset for second part
    int countB;  // local_4c - used as count or offset

    // Get first array components
    FUN_008d6600(&arrayA, &sizeA, &offsetA, &countB);

    int* ptrA = arrayA;  // puVar3
    int totalSize = countB + sizeA;  // iVar1

    if (arrayA != nullptr)
    {
        int firstElement = arrayA[0];                // local_3c
        int lastElement;
        if (countB == 0 || offsetA == 0)
        {
            lastElement = arrayA[sizeA - 1];         // local_40 (from arrayA)
        }
        else
        {
            // Access element from a different location using offsetA and countB
            lastElement = *(int*)(offsetA - 4 + countB * 4); // local_40
        }

        *outArray = nullptr;   // param_1
        int sizeOut = 0;       // local_44
        int offsetOut = 0;     // local_4c (reused)
        int* arrayB = nullptr; // local_48 (reused)

        FUN_008d6480(outArray, &sizeOut, &offsetOut, &arrayB);

        // Structure of elements in outArray (28 bytes each):
        // struct ArrayElement { int64 a; int64 b; int64 c; int d; };
        // But we treat as 7 ints for simplicity.
        if (*outArray == nullptr)
        {
            // Set local_38..local_20 to zero
            int a1 = 0, a2 = 0, a3 = 0, a4 = 0; // local_38, local_30, local_28, local_20
            int lastKey = 0; // iVar5
        }
        else
        {
            // Read first element of outArray (28 bytes)
            int* outFirst = (int*)*outArray; // pointer to first element
            int a1 = outFirst[0];            // local_38 (low 32 bits of first 8 bytes)
            int a2 = outFirst[1];            // local_30 (high 32 bits? Actually next 8 bytes)
            int a3 = outFirst[2];            // local_28
            int a4 = outFirst[3];            // local_20
            // Note: outFirst[0] and outFirst[1] together form first 8 bytes, but we split.

            int* lastElemPtr;
            if (arrayB == nullptr || offsetOut == 0)
            {
                lastElemPtr = (int*)((char*)*outArray + sizeOut * 28 - 28);
            }
            else
            {
                lastElemPtr = (int*)(offsetOut - 28 + (int)arrayB * 28);
            }
            // Read last element (7 ints)
            int lastElem[7];
            lastElem[0] = lastElemPtr[0];
            lastElem[1] = lastElemPtr[1];
            lastElem[2] = lastElemPtr[2];
            lastElem[3] = lastElemPtr[3];
            lastElem[4] = lastElemPtr[4];
            lastElem[5] = lastElemPtr[5];
            lastElem[6] = lastElemPtr[6]; // local_4

            int lastKey = lastElem[0]; // iVar5
        }

        if (totalSize != 0)
        {
            if (totalSize == a1 && totalSize == lastKey)
            {
                // Sizes match: direct merge
                FUN_008d5f20(&lastElem, &a1, &lastElem, firstElement, lastElement, totalSize);
                FUN_008d6410(&lastElem); // cleanup
                return;
            }
            if (countB == 0 || offsetA == 0)
            {
                // Simple merge
                FUN_008d6270(&lastElem, ptrA, sizeA);
            }
            else
            {
                // Merge with offset
                FUN_008d5fe0(&lastElem, ptrA, sizeA, offsetA, countB);
            }
            FUN_008d6410(&lastElem);
        }
    }
    return;
}