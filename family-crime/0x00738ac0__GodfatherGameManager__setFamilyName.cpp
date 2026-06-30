// FUNC_NAME: GodfatherGameManager::setFamilyName
void __fastcall GodfatherGameManager::setFamilyName(int this)
{
    // Likely initializes or logs something for the family manager
    FAM_004719a0(); 

    // Get the family name pointer, or use a default string if null
    char* familyName = *(char**)(this + 0x2108);
    if (familyName == nullptr) {
        familyName = reinterpret_cast<char*>(0x0120546e); // Default family name constant
    }

    // Set the name for the family ID stored at +0x2104
    FUN_00737940(*(int*)(this + 0x2104), familyName); // Probably setNameForID(id, name)
}