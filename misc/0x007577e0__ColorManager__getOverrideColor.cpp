// FUNC_NAME: ColorManager::getOverrideColor
void __thiscall ColorManager::getOverrideColor(CMInstance *this, ColorOutput *outColor) {
    char getResult;
    int index;
    ColorOutput *baseColorPtr;
    ColorOutput localColor1; // 12 bytes
    ColorOutput localColor2; // 12 bytes

    // Fetch the global base color source (e.g., from a palette manager singleton)
    baseColorPtr = (ColorOutput *) (FUN_00471610() + 0x30);

    // If override system is disabled, just copy the base color
    if (g_useOverrideColors == '\0') {
        *outColor = *baseColorPtr;
        *(uint32 *)(outColor + 8) = *(uint32 *)((char *)baseColorPtr + 8);
        return;
    }

    // Check the override index for this instance
    index = this->overrideColorIndex; // offset 0x14c

    // If index is 0, attempt to fetch color with index 0 directly
    if (index == 0) {
        getResult = FUN_009a1e00(0, outColor);
        if (getResult != '\0') {
            return;
        }
    }
    else {
        // For non‑zero index, try to get the two adjacent colors for interpolation
        getResult = FUN_009a1e00(index - 1, &localColor1);
        if (getResult != '\0') {
            getResult = FUN_009a1e00(index, &localColor2);
            if (getResult != '\0') {
                // Blend the base color with the two override colors (factor 0 = full override?)
                FUN_0084cb90(baseColorPtr, &localColor1, &localColor2, outColor, 0);
                return;
            }
        }
    }

    // Fallback: copy base color if override fails
    *outColor = *baseColorPtr;
    *(uint32 *)(outColor + 8) = *(uint32 *)((char *)baseColorPtr + 8);
}