// FUNC_NAME: WindowManager::applyWindowProperties
void __fastcall WindowManager::applyWindowProperties(void* window)
{
    // Get thread-local storage pointer (offset 0x2c = pointer to per-thread data)
    int* tlsData = *(int**)(__readfsdword(0x2c));
    int* currentObject = (int*)*tlsData; // Actually tlsData points to a struct containing useful pointers
    int* windowList = (int*)(*(int*)(currentObject + 0x28) = (int)window); // Store window handle? Offset 0x28

    int prevWidth = DAT_011f38f4;
    int prevHeight = DAT_011f38f0;

    if (*(int*)(currentObject + 0x34) == 0) // First initialization path?
    {
        // Initialize window list at DAT_01206880 + 0x14
        int* listPtr = (int*)(DAT_01206880 + 0x14);
        *listPtr = (int)&PTR_LAB_0110b6f4; // Set vtable pointer
        *listPtr += (int)(listPtr + 4); // Advance pointer? Actually it's *((int*)(listPtr)) = *((int*)(listPtr)) + 4
        // Above is messy - likely appends to a dynamic array
        *(int*)(*listPtr) = (int)window;
        *listPtr += 4;

        FUN_004236f0(); // Call window procedure?
        return;
    }

    // Update path - store new dimensions/state
    DAT_011f38f4 = *(unsigned short*)((int)window + 0x174);
    DAT_011f38f0 = *(int*)((int)window + 0x16c);
    FUN_00609340(0, prevWidth, DAT_011f38f4); // Set width (index 0)

    int prevX = DAT_011f3914;
    int prevY = DAT_011f3910;
    DAT_011f3914 = *(unsigned short*)((int)window + 0x176);
    DAT_011f3910 = *(int*)((int)window + 0x170);
    FUN_00609340(4, prevX, DAT_011f3914); // Set height? (index 4)

    if ((*(int*)((int)window + 0x16c) == 0) && (*(int*)((int)window + 0x170) != 0))
    {
        // Case: width == 0 but height != 0 (minimized? fullscreen vertical bar?)
        FUN_0060db60(4,
                     *(int*)((int)window + 0x15c), *(int*)((int)window + 0x160),
                     *(int*)((int)window + 0x164), *(int*)((int)window + 0x168));
        FUN_004236f0();
        return;
    }

    // Normal size/position update
    FUN_0060db60(0,
                 *(int*)((int)window + 0x15c), *(int*)((int)window + 0x160),
                 *(int*)((int)window + 0x164), *(int*)((int)window + 0x168));
    FUN_004236f0();
    return;
}