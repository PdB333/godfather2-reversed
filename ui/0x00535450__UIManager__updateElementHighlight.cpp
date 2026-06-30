// FUNC_NAME: UIManager::updateElementHighlight
void UIManager::updateElementHighlight(char param_1, undefined4 param_2)
{
    // Access global arrays indexed by m_uiSlotIndex (0x30 stride) and m_secondarySlotIndex (0x3c stride)
    int primarySlotIndex = *(int*)&DAT_01219b20; // assume global variable
    int secondarySlotIndex = *(int*)&DAT_01219b21; // assume global variable

    void* primaryElementPtr = *(void**)(&DAT_01219cbc + primarySlotIndex * 0x30);
    void* secondaryElementPtr = *(void**)(&DAT_01219cc0 + primarySlotIndex * 0x30);
    void* tertiaryElementPtr = *(void**)(&DAT_01219d54 + secondarySlotIndex * 0x3c);

    // Clear previous element if present
    if (primaryElementPtr != 0)
    {
        // Remove material from primary element
        FUN_0060b020(DAT_01219a80, primaryElementPtr); // Some "removeMaterial" type call
    }
    if (secondaryElementPtr != 0)
    {
        // Remove geometry from secondary element
        FUN_0060aea0(DAT_01219a80, secondaryElementPtr); // Some "removeGeometry" type call
    }

    // Determine if we should apply a highlight color
    int objectValue = 0;
    if (tertiaryElementPtr != 0)
    {
        if (param_1 == 0)
        {
            objectValue = 0;
        }
        else
        {
            // Check if a global camera or renderer object exists
            int* rendererObj = *(int**)DAT_012234c4;
            if (rendererObj != 0 && *(int*)(rendererObj + 0x24) != 0)
            {
                // Call virtual method at offset 4 from that object to get a value
                int (*func)(int) = **(int (***)(int))(*(int*)(rendererObj + 0x24) + 4);
                objectValue = func(in_EAX + 0x30);
            }
            else
            {
                objectValue = 0;
            }
        }

        // Update the primary slot's material (if previous element exists)
        void* previousPrimary = *(void**)(&DAT_01219cb8 + primarySlotIndex * 0x30);
        if (previousPrimary != 0)
        {
            FUN_0060add0(DAT_01219a80, previousPrimary, DAT_012054dc + 0x70); // Some "addMaterial" with a base offset
        }

        if (objectValue != 0)
        {
            // Apply highlight color to tertiary element
            int* color = (int*)(objectValue + 0x10); // color offset in object
            // Build a color struct from objectValue+0x20, +0x24, +0x28 and param_2
            undefined4 colorStruct[4];
            colorStruct[0] = *(undefined4*)(objectValue + 0x20); // R
            colorStruct[1] = *(undefined4*)(objectValue + 0x24); // G
            colorStruct[2] = *(undefined4*)(objectValue + 0x28); // B
            colorStruct[3] = param_2;                              // A (alpha)
            FUN_0060add0(DAT_01219a84, *(void**)(&DAT_01219d58 + secondarySlotIndex * 0x3c), colorStruct);
            FUN_0060add0(DAT_01219a80, *(void**)(&DAT_01219cb4 + primarySlotIndex * 0x30), (void*)objectValue);
            return;
        }

        // If objectValue is zero, set highlight to transparent (zero color)
        undefined4 clearColor[4] = {0, 0, 0, 0};
        FUN_0060add0(DAT_01219a80, *(void**)(&DAT_01219cb4 + primarySlotIndex * 0x30), clearColor);
        FUN_0060ab00(DAT_01219a84, *(void**)(&DAT_01219d54 + secondarySlotIndex * 0x3c), clearColor, 4);
    }
    return;
}