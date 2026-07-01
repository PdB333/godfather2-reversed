// FUNC_NAME: UIList::setSelectedIndex
void __thiscall UIList::setSelectedIndex(uint index)
{
    // Check if index is within valid range (count stored at +0x5C)
    if (index < *(uint *)(this + 0x5C))
    {
        // Store the selected index at +0x78
        *(uint *)(this + 0x78) = index;

        // Get the item data pointer from the array at +0x58
        void *itemData = *(void **)(*(int *)(this + 0x58) + index * 4);

        // Get the name string (or ID) from the item data
        uint nameId = getItemNameString(itemData);

        // Copy the name into the buffer at +0x70 (max 32 bytes)
        stringCopy(*(undefined4 *)(this + 0x70), nameId, 0x20, 0);

        // Get the description data structure from the item data
        struct DescriptionData *descData = (struct DescriptionData *)getItemDescriptionData(itemData);

        // Get the description string pointer (first field of the struct)
        char *descStr = (char *)descData->stringPtr;
        if (descStr == (char *)0x0)
        {
            descStr = &DAT_0120546e; // Default empty string
        }

        // Copy the description into the buffer at +0x74 (max 32 bytes, with length from struct)
        stringCopy(*(undefined4 *)(this + 0x74), descStr, 0x20, descData->length);

        // Refresh the UI display
        refreshDisplay();
    }
    else
    {
        // Invalid index: clear both buffers and set selection to -1
        **(char **)(this + 0x74) = 0;
        **(char **)(this + 0x70) = 0;
        *(uint *)(this + 0x78) = 0xFFFFFFFF;
        refreshDisplay();
    }
}