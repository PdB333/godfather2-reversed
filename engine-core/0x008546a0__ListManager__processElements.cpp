// FUNC_NAME: ListManager::processElements
void ListManager::processElements(int* listContainer) {
    int* basePtr = listContainer;
    // Initialize various fields of the container
    FUN_004a9b90(this, basePtr + 5);   // +0x14
    FUN_004a9b90(this, basePtr + 8);   // +0x20
    FUN_004a9b90(this, basePtr + 0xe); // +0x38
    FUN_004a9b90(this, basePtr + 0xb); // +0x2c
    FUN_004a9320(this, basePtr + 3);   // +0x0c

    int* elementArray = (int*)basePtr[1]; // count? Actually basePtr[1] is the count, but cast to pointer
    FUN_0064b810(0x20, &elementArray);   // Allocate or initialize something with size 0x20

    int offset = 0;
    int* counter = (int*)0x0; // used as loop counter

    if (basePtr[1] != 0) {
        do {
            int* element = (int*)(basePtr[0] + offset); // basePtr[0] is the array pointer
            FUN_004a9b90(this, element); // Process the element
            FUN_0064bb50(*(char*)(element + 0xc)); // Check byte at +0x0c
            char flag = FUN_0064bb50(*(char*)(element + 0xd)); // Check byte at +0x0d
            if (flag != '\0') {
                FUN_00854520(this, element + 0x10); // Process sub-element at +0x10
            }
            counter = (int*)((int)counter + 1);
            offset += 0x2c; // 44 bytes per element
        } while ((int)counter < basePtr[1]);
    }
}