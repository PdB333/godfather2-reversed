// FUNC_NAME: MaterialManager::setMaterialData
void __thiscall MaterialManager::setMaterialData(int index, const int* newData)
{
    // Array of 16-byte structures at offset 0x84 (each entry is 0x10 bytes)
    int* currentData = (int*)(this + 0x84 + index * 0x10);

    // Check if the 4 ints match
    if (currentData[0] != newData[0] ||
        currentData[1] != newData[1] ||
        currentData[2] != newData[2] ||
        currentData[3] != newData[3])
    {
        // Handle at offset 0x104 (array of 4-byte pointers/handles)
        int handle = *(int*)(this + 0x104 + index * 4);
        if (handle != 0)
        {
            // Release and destroy the old resource
            FUN_005e6820(handle, 0, 0);  // e.g., releaseRef(handle, 0, 0)
            FUN_005e6660(handle);        // e.g., destroyResource(handle)
            *(int*)(this + 0x104 + index * 4) = 0;
        }

        // Copy the new 16-byte data
        currentData[0] = newData[0];
        currentData[1] = newData[1];
        currentData[2] = newData[2];
        currentData[3] = newData[3];
    }
}