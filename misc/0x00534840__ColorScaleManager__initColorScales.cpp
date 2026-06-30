// FUNC_NAME: ColorScaleManager::initColorScales

// Reconstructed from 0x00534840 - Initializes color scale data structures
// Uses three global resource handles and fills arrays with color scale values

class ColorScaleManager {
public:
    // Offsets in this object:
    // +0x1E0: handle0 (4 bytes)
    // +0x1E4: handle1 (4 bytes)
    // +0x1E8: handle2 (4 bytes)
    // +0x1EC: handleArray[20] (80 bytes)
    // +0x23C: colorScaleArray[3][12] (144 bytes) - 3 sets of 12 floats
    // +0x2CC: lookupTable[20][15] (1200 bytes) - 20 sets of 15 values

    void initColorScales() {
        int index;
        int count;
        int result;
        int* ptr1;
        int* ptr2;
        int baseOffset;

        // First loop: initialize three color scale handles and their 12-element arrays
        index = 0;
        do {
            if (index == 2) {
                result = createHandle(); // FUN_0060a380
                *(int*)((int)this + 0x1E8) = result;
            } else {
                result = createHandle(); // FUN_0060a380
                *(int*)((int)this + 0x1E0 + index * 4) = result;
            }

            ptr1 = (int*)(index * 0x30 + 0x23C + (int)this);
            // Calculate offset to global color scale data
            baseOffset = (int)&g_colorScaleData - (int)ptr1;
            count = 12;
            do {
                result = setResourceValue(*(int*)((int)this + 0x1E0 + index * 4),
                                          *(int*)((int)ptr1 + baseOffset)); // FUN_0060a580
                *ptr1 = result;
                ptr1++;
                count--;
            } while (count != 0);

            index++;
        } while (index < 3);

        // Second loop: initialize 20 handle entries and their 15-element lookup tables
        ptr1 = (int*)((int)this + 0x1EC); // handleArray
        ptr2 = (int*)((int)this + 0x2CC); // lookupTable
        baseOffset = (int)&g_lookupTableBase - (int)this; // 0x10C1EB4 - this
        index = 0;
        do {
            result = createObject(*(int*)((int)&g_resourcePointers + index)); // FUN_0060a2e0
            *ptr1 = result;
            count = 15;
            do {
                result = setResourceValue(*ptr1,
                                          *(int*)((int)ptr2 + baseOffset)); // FUN_0060a580
                *ptr2 = result;
                ptr2++;
                count--;
            } while (count != 0);
            index += 4;
            ptr1++;
            baseOffset -= 0x3C;
        } while (index < 0x50);
    }

private:
    // External engine functions (addresses from Ghidra)
    int createHandle();          // FUN_0060a380
    int setResourceValue(int handle, int value); // FUN_0060a580
    int createObject(int param); // FUN_0060a2e0

    // Global data references
    static int g_colorScaleData;       // PTR_s_color_scale_010c2150
    static int g_lookupTableBase;      // 0x10C1EB4
    static int g_resourcePointers[];   // PTR_PTR_011281b0
};