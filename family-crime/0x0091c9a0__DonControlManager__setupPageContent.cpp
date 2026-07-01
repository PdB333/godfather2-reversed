// FUNC_NAME: DonControlManager::setupPageContent
void __fastcall DonControlManager::setupPageContent(DonControlManager* this)
{
    int pageIndex = *(int*)((char*)this + 0xb8); // +0xB8: currentPageIndex

    if (pageIndex == 0xd) // Family page
    {
        int titleId = 0x23;   // 35
        int descId  = 0x21;   // 33
        int iconId  = 0x22;   // 34
        int* strings[3] = { 
            (int*)getStringFromID(titleId),
            (int*)getStringFromID(descId),
            (int*)getStringFromID(iconId)
        };
        void* menuMgr = getMenuManager(g_menuManager); // DAT_00e54d0c
        registerMenuItems(menuMgr, strings, 3, menuCallback); // FUN_0091b9d0
    }
    else if (pageIndex == 0xe) // Business page
    {
        int titleId = 0x26;   // 38
        int descId  = 0x24;   // 36
        int iconId  = 0x25;   // 37
        int* strings[3] = { 
            (int*)getStringFromID(titleId),
            (int*)getStringFromID(descId),
            (int*)getStringFromID(iconId)
        };
        void* menuMgr = getMenuManager(g_menuManager);
        registerMenuItems(menuMgr, strings, 3, menuCallback);
    }
    else if (pageIndex == 0xf) // Hit page
    {
        int titleId = 0x29;   // 41
        int descId  = 0x27;   // 39
        int iconId  = 0x28;   // 40
        int* strings[3] = { 
            (int*)getStringFromID(titleId),
            (int*)getStringFromID(descId),
            (int*)getStringFromID(iconId)
        };
        void* menuMgr = getMenuManager(g_menuManager);
        registerMenuItems(menuMgr, strings, 3, menuCallback);
    }
    else if (pageIndex == 0x10) // Crew page
    {
        int titleId = 0x2c;   // 44
        int descId  = 0x2a;   // 42
        int iconId  = 0x2b;   // 43
        int* strings[3] = { 
            (int*)getStringFromID(titleId),
            (int*)getStringFromID(descId),
            (int*)getStringFromID(iconId)
        };
        void* menuMgr = getMenuManager(g_menuManager);
        registerMenuItems(menuMgr, strings, 3, menuCallback);
    }
    else if (pageIndex == 0x11) // Exit page
    {
        menuCallback(0, 0); // direct call with no data
    }
}