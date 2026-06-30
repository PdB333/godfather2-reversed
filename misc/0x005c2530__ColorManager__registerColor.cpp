// FUNC_NAME: ColorManager::registerColor
void ColorManager::registerColor(uint colorValue)
{
    // Store color value in global debug variables (big-endian order)
    DAT_01223564 = (byte)(colorValue >> 24);
    DAT_01223565 = (byte)(colorValue >> 16);
    DAT_01223566 = (byte)(colorValue >> 8);
    DAT_01223567 = (byte)colorValue;
    DAT_01223568 = 0; // some flag

    // Ensure singleton ColorManager exists
    if (DAT_01205664 == 0) {
        int* alloc = (int*)FUN_005c4410(200, 0); // allocate manager memory
        if (alloc != 0) {
            DAT_01205664 = (int)FUN_005c3070(); // initialize manager singleton
        }
        FUN_005c31d0(); // secondary initialization
    }

    // Check if color already registered (by some key)
    int existing = FUN_005c3df0(DAT_01205664);
    if (existing == 0) {
        // Allocate new color object (size 0x4c = 76 bytes)
        int* colorObj = (int*)FUN_005c4410(0x4c, 0);
        if (colorObj != 0) {
            colorObj = (int*)FUN_005bf9b0(); // constructor, returns pointer to initialized object
        }
        // Store the color value at offset +0x44
        *(uint*)((int)colorObj + 0x44) = colorValue;
        FUN_005c1740(); // register with global system

        // Add color object to this manager's dynamic array (this +0x10: data, +0x14: size, +0x18: capacity)
        int* countPtr = (int*)((int)this + 0x14);
        int newCount = *countPtr + 1;
        if (*(int*)((int)this + 0x18) < newCount) {
            int* newData = (int*)FUN_005c27a0(
                *(int*)((int)this + 0x10), newCount, 4,
                countPtr, (int*)((int)this + 0x18));
            *(int*)((int)this + 0x10) = (int)newData;
        }
        *countPtr = newCount;
        *(int*)(*(int*)((int)this + 0x10) + (newCount - 1) * 4) = (int)colorObj;
    }
}