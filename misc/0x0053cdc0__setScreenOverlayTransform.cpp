// FUNC_NAME: setScreenOverlayTransform

// Function address: 0x0053cdc0
// Called with an index in ESI (unaff_ESI). Sets up a screen overlay transform
// using texture dimensions and a global scale factor.

void setScreenOverlayTransform(uint overlayIndex)
{
    // Global index into overlay configuration arrays (size 0x2c per entry)
    int configIndex = DAT_01125d78; // likely current overlay context index

    // +0x0: first pointer in overlay config
    int* pOverlayObj1 = *(int*)((char*)&DAT_01125c58 + configIndex * 0x2c);
    if (pOverlayObj1 != 0) {
        // Release/cleanup previous overlay object
        sub_6063B0();
    }

    // +0x4: second pointer in overlay config
    int* pOverlayObj2 = *(int*)((char*)&DAT_01125c5c + configIndex * 0x2c);
    if (pOverlayObj2 != 0) {
        // Get texture info pointer from overlay index
        // Each texture info block is 0x38 bytes
        char* pTexInfo;
        if (overlayIndex < 0x1000) {
            pTexInfo = (char*)&DAT_011a0f28 + overlayIndex * 0x38;
        } else {
            pTexInfo = 0; // potential crash below if used
        }

        // Compute scale factors using texture dimensions (stored at +2 and +4 as shorts)
        float invWidth = DAT_00e2b1a4 / (float)*(unsigned short*)(pTexInfo + 2);   // +0x2: texture width
        float invHeight = DAT_00e2b1a4 / (float)*(unsigned short*)(pTexInfo + 4);  // +0x4: texture height

        // Apply global scale factor to both
        float local_20 = invWidth;
        float local_1c = invHeight;
        float local_18 = invWidth * DAT_00e2cd54;   // +0x8? Possibly additional transform
        float local_14 = invHeight * DAT_00e2cd54;  // +0xc? Possibly additional transform

        // Set up the transform for the overlay object
        sub_60ADD0(DAT_01125ba4, pOverlayObj2, &local_20);
    }
}