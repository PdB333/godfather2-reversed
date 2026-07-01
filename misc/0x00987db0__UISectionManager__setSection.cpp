// FUNC_NAME: UISectionManager::setSection

void __thiscall UISectionManager::setSection(int this, int sectionId)
{
    char sectionName[64]; // buffer for "section_%d"
    // Local struct for some transformation or identity
    struct {
        int a; // +0x00
        int b; // +0x04
        int c; // +0x08
    } tempStruct; // used by FUN_00408a00

    // Store the section ID
    *(int *)(this + 0x58) = sectionId;
    // Clear auxiliary states
    *(int *)(this + 0x5c) = 0;
    *(int *)(this + 0x64) = 0; // offset 100 decimal

    // Map section ID to a page/frame index
    if (sectionId == 0) {
        *(int *)(this + 0x60) = 4;
    }
    else if (sectionId == 1) {
        *(int *)(this + 0x60) = 17;
    }
    else if (sectionId == 2) {
        *(int *)(this + 0x60) = 12;
    }

    // Call global reset (likely clears some UI state)
    FUN_00987970();

    // Clear a flag at +0x54
    *(int *)(this + 0x54) = 0;

    // Build the section name like "section_0", "section_1", etc.
    _sprintf(sectionName, "section_%d", sectionId);

    // Invoke Scaleform ActionScript: gotoAndStop(sectionName)
    // Parameters: method name "gotoAndStop", target path 0, movie reference (DAT_00d90fa8), numArgs=1, args=sectionName
    FUN_005a04a0("gotoAndStop", 0, &DAT_00d90fa8, 1, sectionName);

    // Set up a temporary structure with a constant value and zeros, then maybe apply a transformation
    tempStruct.a = DAT_01130418;
    tempStruct.b = 0;
    tempStruct.c = 0;
    FUN_00408a00(&tempStruct, 0);
}