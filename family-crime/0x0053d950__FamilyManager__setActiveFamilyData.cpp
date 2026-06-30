// FUNC_NAME: FamilyManager::setActiveFamilyData

void FamilyManager::setActiveFamilyData(int familyIndex, void* param_ecx)
{
    // familyIndex from EAX, param_ecx from ECX (fastcall)
    // Global table of family data entries (0x1b bytes each)
    gFamilyManager.pData2 = &gFamilyDataTable[familyIndex * sizeof(FamilyDataArrayEntry)];
    gFamilyManager.pNewFamilyParam = param_ecx;
    gFamilyManager.newFamilyIndex = familyIndex;

    // Check if the singleton manager is already initialized
    if (gpFamilyManager == &gFamilyManager) {
        // Release old family data (pData2 was just overwritten, so this may be intentional cleanup)
        FamilyData::release(gFamilyManager.pData2);
        FamilyData::release(gFamilyManager.pData1);
    }

    // If a flag is set, copy additional data from somewhere into a local buffer
    if (gFamilyManager.someFlag != 0) {
        char buffer[16] = {0};
        FamilyData::copyFromBuffer(gFamilyManager.pData1, gFamilyManager.someFlag, buffer);
    }
}