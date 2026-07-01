// FUNC_NAME: ContainerClass::addElement
// Function at 0x00981e70: Adds an element to a fixed-size array (max 8), optionally setting it as current.
void __thiscall ContainerClass::addElement(int thisPtr, undefined4 sourceData, char setActive, undefined4 elementValue)
{
    // +4: count of elements currently stored
    int count = *(int *)(thisPtr + 4);
    if (count < 8) {
        // Process the source data (likely copy/validate/init)
        FUN_004d3d90(sourceData);
        // Store element at offset 0xCC + count*4
        *(undefined4 *)(thisPtr + 0xCC + count * 4) = elementValue;
        if (setActive != '\0') {
            // +8: index of the currently active element
            *(undefined4 *)(thisPtr + 8) = count;
        }
        // Increment element count
        *(int *)(thisPtr + 4) = count + 1;
    }
}