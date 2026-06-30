// FUNC_NAME: TextRenderer::drawString
void __thiscall TextRenderer::drawString(int this, float *pPosition, undefined4 param_3, char *pText, int alignment, float *pOffset, unsigned int *pColor)
{
    float fVar1;
    undefined4 savedColor1, savedColor2, savedColor3, savedColor4;
    char cVar6;
    int unaff_FS_OFFSET;
    bool bIsInRender;
    float xOffset;
    float yOffset;
    char transformedBuffer[2052]; // local_808, 0x800 bytes

    // Check font handle (+0x1c) and text pointer
    if ((*(int *)(this + 0x1c) != 0) && (pText != (char *)0x0)) {
        // Thread-local storage check: likely checking if we are in a render context
        bIsInRender = *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x28) == 0;
        if (bIsInRender) {
            FUN_00423410(); // Enter critical section/render guard
        }
        // If not initialized (+0x54 == 0), initialize font resources
        if (*(int *)(this + 0x54) == 0) {
            FUN_00619950(); // Initialize font system
            FUN_00489bc0(*(undefined1 *)(this + 0x58)); // load font handle
        }
        fVar1 = pPosition[1]; // Original Y position (or height)
        // Compute alignment offsets based on pPosition[0] and global constants
        if (alignment == 1) {
            yOffset = *pPosition;
            if (DAT_00e2cd54 <= yOffset) {
                yOffset = (DAT_00e2b1a4 - yOffset) * DAT_00e2b04c;
                xOffset = DAT_00e2b1a4 - yOffset;
            }
            else {
                yOffset = yOffset * DAT_00e2b04c;
                xOffset = 0.0;
            }
        }
        else {
            yOffset = *pPosition;
            if (alignment == 2) {
                xOffset = 0.0;
            }
            else {
                xOffset = yOffset;
                yOffset = DAT_00e2b1a4 - yOffset;
            }
        }
        // If there's a text transformation callback at +0x40, call it to possibly modify the string
        if ((*(code **)(this + 0x40) != (code *)0x0) &&
           (cVar6 = (**(code **)(this + 0x40))(pText, transformedBuffer, 0x800, 0), cVar6 != '\0')) {
            pText = transformedBuffer;
        }
        // Save global color state
        savedColor4 = DAT_01163da4;
        savedColor3 = DAT_01163da0;
        savedColor2 = DAT_01163d9c;
        savedColor1 = DAT_01163d98;
        // If a custom offset/color is provided, override global color temporarily
        if ((pOffset != (float *)0x0) && ((*pOffset != 0.0 || (pOffset[1] != 0.0)))) {
            DAT_01163d98 = *pColor;
            DAT_01163d9c = *pColor;
            DAT_01163da0 = *pColor;
            DAT_01163da4 = *pColor;
            FUN_0048aa50(this,
                         *(undefined4 *)(this + 0x1c),
                         *pOffset + xOffset,
                         fVar1 - pOffset[1],
                         yOffset,
                         fVar1,
                         param_3,
                         pText,
                         alignment,
                         1,
                         0,
                         0,
                         0,
                         0xffffffff,
                         1);
        }
        // Restore global color
        DAT_01163d98 = savedColor1;
        DAT_01163d9c = savedColor2;
        DAT_01163da0 = savedColor3;
        DAT_01163da4 = savedColor4;
        // Main drawing call (no color override)
        FUN_0048aa50(this,
                     *(undefined4 *)(this + 0x1c),
                     xOffset,
                     fVar1,
                     yOffset,
                     fVar1,
                     param_3,
                     pText,
                     alignment,
                     0,
                     0,
                     0,
                     0,
                     0xffffffff,
                     1);
        // Cleanup if not initialized before
        if (*(int *)(this + 0x54) == 0) {
            FUN_00489d60(*(undefined1 *)(this + 0x58)); // unload font handle
        }
        if (bIsInRender) {
            FUN_00423610(); // Leave critical section/render guard
        }
    }
    return;
}