// FUNC_NAME: FlashUIContainer::setSection
// Function address: 0x009243b0
// Role: Sets the current section of a Flash UI container, initializes related fields, navigates to the section label, and cleans up a temporary string.

void __thiscall FlashUIContainer::setSection(int thisPtr, int sectionIndex)
{
    // Local buffer for constructing the section label string
    char sectionBuffer[16];

    // Store the section index
    *(int *)(thisPtr + 0x58) = sectionIndex;        // +0x58: sectionId
    // Reset sub-section index or state flag
    *(int *)(thisPtr + 0x5c) = 0;                   // +0x5c: subSectionId (or zero)
    // Store a value from a global table indexed by sectionIndex*2
    *(int *)(thisPtr + 0x60) = globalSectionTable[sectionIndex * 2]; // +0x60: sectionParam

    // Initialize some internal state (may reset animation, etc.)
    FUN_00923500();

    // Clear another field (maybe related to current frame)
    *(int *)(thisPtr + 0x54) = 0;                   // +0x54: currentFrameOrState

    // Build the section label string: "section_%d"
    FUN_00923870(sectionBuffer, "section_%d", sectionIndex); // likely sprintf

    // Navigate the embedded Flash movie to the specified section label
    // Parameters: methodName="gotoAndStop", unknown=0, globalStringRef, flags=1, label=sectionBuffer
    FUN_005a04a0("gotoAndStop", 0, &DAT_00d87288, 1, sectionBuffer);

    // Temporary string object: initialized with global data, then cleaned up.
    // The structure seems to be: { char* data, int length, char flag }
    struct TempString {
        char* data;    // +0x00
        int length;    // +0x04
        char flag;     // +0x08
    } tempStr;
    tempStr.data = DAT_01130418; // Global string pointer or constant
    tempStr.length = 0;
    tempStr.flag = 0;

    // Call destructor or release function for the temporary string
    FUN_00408a00(&tempStr, 0);
}