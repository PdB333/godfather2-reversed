// Xbox PDB: EARS_Apt_UILanguageSelect_PopulateLanguages
// FUNC_NAME: LanguageManager::enumerateAvailableLanguages
void __thiscall LanguageManager::enumerateAvailableLanguages(int this)
{
    uint *currentEntry; // puVar1
    char languageAvailable; // cVar2
    int maxLanguages; // iVar3
    int languageEntry; // uVar4
    uint languageIndex; // uVar5
    int count; // local derived

    count = 0;
    *(int *)(this + 0x60) = 0; // current count
    FUN_009c8f10(*(int *)(this + 0x5c)); // free existing array? (FUN_009c8f10 might be operator delete)
    *(int *)(this + 0x5c) = 0; // array pointer
    *(int *)(this + 0x64) = 0; // capacity
    maxLanguages = FUN_00604350(); // get total number of possible languages
    *(int *)(this + 0x50) = maxLanguages; // store max count
    if (maxLanguages != 0)
    {
        languageIndex = 0;
        do
        {
            languageAvailable = FUN_00602f00(languageIndex); // check if language index is available
            if (languageAvailable != '\0')
            {
                count = *(int *)(this + 0x60);
                if (count == *(int *)(this + 0x64))
                {
                    // reallocate array if full
                    if (count == 0)
                        count = 1;
                    else
                        count = count * 2;
                    FUN_00486800(count); // realloc or resize? (likely realloc or new array)
                }
                currentEntry = (uint *)(*(int *)(this + 0x5c) + *(int *)(this + 0x60) * 4);
                *(int *)(this + 0x60) = *(int *)(this + 0x60) + 1; // increment count
                if (currentEntry != (uint *)0x0)
                {
                    *currentEntry = languageIndex; // store language ID
                }
                languageEntry = FUN_00602e60(languageIndex); // get language code string? or ID
                FUN_005a04a0("AddLanguage", 0, &DAT_00d8bea0, 1, languageEntry); // register language
            }
            languageIndex = languageIndex + 1;
        } while (languageIndex < *(uint *)(this + 0x50));
    }
    return;
}