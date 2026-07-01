//FUNC_NAME: cleanupObjectHierarchy
void cleanupObjectHierarchy(void)
{
    // Global pointer at DAT_011298a0, offset +0x24 points to a container structure
    int* outerContainer = *(int**)(DAT_011298a0 + 0x24);
    uint outerIndex = 0;

    if (outerContainer != 0 && *(int*)(outerContainer + 0x10) != 0) {
        int outerOffset = 0;
        do {
            // Each outer element is a container at outerContainer->base + outerOffset
            int* innerContainer = (int*)(*(int*)(outerContainer + 0xc) + outerOffset);
            uint innerIndex = 0;

            if (innerContainer != 0 && *(int*)(innerContainer + 0x10) != 0) {
                int innerOffset = 0;
                do {
                    // Each inner element is at innerContainer->base + innerOffset
                    int* element = (int*)(*(int*)(innerContainer + 0xc) + innerOffset);

                    if (*element == 1) {
                        // Element is a group: contains sub-elements at element[3] (offset +0xc) with count element[4] (offset +0x10)
                        uint subCount = (uint)*(element + 4);
                        if (subCount != 0) {
                            uint subIndex = 0;
                            do {
                                // Each sub-element is 0x2c bytes
                                FUN_009103c0(*(element + 3) + subIndex * 0x2c);
                                subIndex++;
                            } while (subIndex < subCount);
                        }
                    } else {
                        // Leaf element: cleanup directly
                        FUN_009103c0(element);
                    }

                    innerOffset += 0x2c;
                    innerIndex++;
                } while (innerIndex < *(uint*)(innerContainer + 0x10));
            }

            outerOffset += 0x2c;
            outerIndex++;
        } while (outerIndex < *(uint*)(outerContainer + 0x10));
    }
}