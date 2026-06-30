// FUNC_NAME: processStructureFields
void processStructureFields(int* param_2)
{
    int count = param_2[1];  // +0x04 from param_2: number of elements
    int elemBase = 0;

    // Process the count field itself (size 0x20 = 32 bytes)
    hashField(0x20, &count);

    if (count == 0) {
        return;
    }

    // Iterate through array of structures (each 0x34 bytes)
    for (int i = 0; i < count; i++) {
        int* element = (int*)(*param_2 + elemBase);  // base of current element

        // Process field at offset +0x04
        int fieldAt4 = *(int*)((uintptr_t)element + 4);
        hashField(0x20, &fieldAt4);

        // Process field at offset +0x00
        hashField(0x20, element);

        // Process field at offset +0x08
        hashField(0x20, &element[2]);

        // Process field at offset +0x30
        hashField(0x20, &element[0xC]);

        elemBase += 0x34;
    }
}