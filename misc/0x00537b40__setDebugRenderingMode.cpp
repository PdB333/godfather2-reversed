// FUNC_NAME: setDebugRenderingMode

void setDebugRenderingMode(char enable) {
    // DAT_0121a390 is likely a singleton pointer to an Engine or Application instance
    // DAT_0121b638 is a global structure with various settings at offsets
    // Offset 0x14: possibly a render mode integer or pointer
    // Offset 0x28: another configuration pointer/struct
    // The two static addresses (0x011280d0, 0x00e2e770) are likely data tables or strings

    // Call first setter with value from globals[0x14]
    FUN_0060b020(DAT_0121a390, *(undefined4 *)(DAT_0121b638 + 0x14));

    // Choose secondary data based on enable flag
    undefined *secondaryData;
    if (enable == '\0') {
        secondaryData = &DAT_00e2e770;
    } else {
        secondaryData = &DAT_011280d0;
    }

    // Call second setter with globals[0x28] and the selected data
    FUN_0060add0(DAT_0121a390, *(undefined4 *)(DAT_0121b638 + 0x28), secondaryData);
}