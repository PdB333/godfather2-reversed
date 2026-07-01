// FUNC_NAME: cleanupObjectPoolTree
void cleanupObjectPoolTree(void)
{
    int* poolManagerPtr;
    int* outerArray;
    int outerCount;
    int outerIndex;
    int outerOffset;

    // Global memory manager at DAT_011298a0, offset +0x24 is pointer to pool manager structure
    poolManagerPtr = *(int**)(DAT_011298a0 + 0x24);
    outerIndex = 0;

    // Pool manager structure: +0x10 = number of outer arrays, +0x0C = pointer to array of outer array descriptors
    if (*(int*)(poolManagerPtr + 0x10) != 0) {
        outerOffset = 0;
        do {
            // Each outer array descriptor at poolManagerPtr[+0x0C] + offset, size 0x2C
            int* outerDescriptor = (int*)(*(int*)(poolManagerPtr + 0x0C) + outerOffset);

            int innerIndex = 0;
            int innerCount = *(int*)(outerDescriptor + 0x10); // +0x10 = number of elements in inner array
            if (innerCount != 0) {
                int innerOffset = 0;
                do {
                    // Each inner array element at outerDescriptor[+0x0C] + innerOffset, size 0x2C
                    int* element = (int*)(*(int*)(outerDescriptor + 0x0C) + innerOffset);

                    if (*element == 1) {
                        // Type 1: element is a container with a list of sub-elements
                        // +0x0C (element[3]) = pointer to sub-list
                        // +0x10 (element[4]) = number of sub-elements (each size 0x2C)
                        int* subList = (int*)(element[3]);
                        int subCount = (uint)(element[4]);
                        if (subCount != 0) {
                            int subIndex = 0;
                            do {
                                // Free each sub-element
                                FUN_0090fdb0(subList + subIndex);
                                subIndex = subIndex + 0x2C / 4; // step 0x2C bytes = 11 ints
                            } while (subIndex < subCount);
                        }
                    }
                    else {
                        // Other types: directly free the element
                        FUN_0090fdb0(element);
                    }

                    innerIndex = innerIndex + 1;
                    innerOffset = innerOffset + 0x2C;
                } while (innerIndex < (uint)innerCount);
            }

            outerIndex = outerIndex + 1;
            outerOffset = outerOffset + 0x2C;
        } while (outerIndex < *(uint*)(poolManagerPtr + 0x10));
    }
}