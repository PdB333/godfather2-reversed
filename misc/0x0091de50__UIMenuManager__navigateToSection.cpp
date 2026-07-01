// FUNC_NAME: UIMenuManager::navigateToSection
void __fastcall UIMenuManager::navigateToSection(int thisPtr)
{
    uint newSectionId;

    // Read current section ID from object at offset 0xB8
    switch (*(uint*)(thisPtr + 0xB8))
    {
    case 0xD:  // FamilyTree?
    case 0x11: // Crew?
        resetSectionData(&DAT_01130208, 0);
        newSectionId = 0x10;
        break;
    case 0xE:  // Compound?
        resetSectionData(&DAT_01130208, 0);
        newSectionId = 0xD;
        break;
    case 0xF:  // Businesses?
        resetSectionData(&DAT_01130208, 0);
        newSectionId = 0xE;
        break;
    case 0x10: // DonControl?
        resetSectionData(&DAT_01130208, 0);
        newSectionId = 0xF;
        break;
    case 0x12: // ??? 
        resetSectionData(&DAT_01130208, 0);
        newSectionId = 0x18;
        break;
    case 0x13: // ???
        resetSectionData(&DAT_01130208, 0);
        newSectionId = 0x12;
        break;
    case 0x14:
        resetSectionData(&DAT_01130208, 0);
        newSectionId = 0x13;
        break;
    case 0x15:
        resetSectionData(&DAT_01130208, 0);
        newSectionId = 0x14;
        break;
    case 0x16:
        resetSectionData(&DAT_01130208, 0);
        newSectionId = 0x15;
        break;
    case 0x17:
        resetSectionData(&DAT_01130208, 0);
        newSectionId = 0x16;
        break;
    case 0x18:
        resetSectionData(&DAT_01130208, 0);
        newSectionId = 0x17;
        break;
    default:
        return; // No action for unrecognized section
    }

    // Set the new active section
    setCurrentSection(newSectionId);
    // Update UI tabs via scripting call
    callScriptFunction("SetSectionTabs", 0, &DAT_00d8510c, 0);
    // Refresh display
    refreshDisplay(1, 0);
}