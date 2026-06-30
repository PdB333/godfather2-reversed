// FUNC_NAME: UIManager::loadScreen
// Function address: 0x005be580
// Role: Creates or retrieves a UI screen based on a type identifier (hash) and screen name.
// Uses precompiled binary data for various multiplayer/HUD screens.

#include <cstring>

// Forward declarations for called functions (assumed to be part of UIManager or related)
extern void initUISystem(); // 0x005d0860
extern void destroyScreen(void* screen); // 0x005cf2d0
extern const char* getCurrentScreenName(); // 0x005d3cb0
extern void preloadScreen(); // 0x005be330
extern bool isScreenLoaded(); // 0x005be2c0
extern bool checkScreenExists(const char* name); // 0x005d17d0
extern void loadScreenData(); // 0x005be380
extern void* getScreenData(); // 0x005d17a0
extern void setupScreen(); // 0x005d3120
extern bool validateScreen(void* data); // 0x005d31c0
extern void initializeScreen(void* param, void* data); // 0x005be3d0

// Global variables (from decompilation)
extern int g_uiSystemInitialized; // DAT_01205668
extern int g_loadingState; // DAT_01205698 (0,1,2,3)
extern void* g_someGlobal; // DAT_012234f4
extern void* g_allocator; // DAT_012234ec (pointer to allocator vtable)
extern void* g_anotherGlobal; // DAT_01206880

// Static data buffers (precompiled UI data)
extern unsigned char g_onlineMenuData[0x2f2d0]; // DAT_00f17970
extern unsigned char g_communityMenuData[0x2e028]; // DAT_00f46c40
extern unsigned char g_donControlData[0x2eb8]; // DAT_00f74c68
extern unsigned char g_scoreboardData[0x1c420]; // DAT_00f77b20
extern unsigned char g_moneyPopupData[0x44430]; // DAT_00f93f40
extern unsigned char g_finalScoreData[0x11580]; // DAT_00fd8370
extern unsigned char g_hudMultiplayerData[0x4920]; // s_fxpa_I_00fe98f0
extern unsigned char g_onlineInstructData[0x21e50]; // DAT_01018fd8
extern unsigned char g_frontendOptionsData[0x18d8]; // DAT_00fee210
extern unsigned char g_systemSettingsData[0x139b0]; // DAT_00fefae8
extern unsigned char g_controlSetupData[0x15b40]; // DAT_01003498

// Static address returned when screen already loaded
extern unsigned char g_defaultScreen; // DAT_00e2f044

// Structure for allocation parameters
struct AllocParams {
    int type; // +0x00
    int alignment; // +0x04
    int unknown; // +0x08
};

// Structure for the 'this' pointer (UIManager or similar)
struct UIManager {
    void** vtable; // +0x00
    int unknown1; // +0x04
    int typeHash; // +0x08 (param_1[2])
    int unknown2; // +0x0C
    void* screenData; // +0x10 (param_1[4])
    void* currentScreen; // +0x14 (param_1[5])
    int screenSize; // +0x18 (param_1[6])
    void* storedScreen; // +0x1C (param_1[7])
};

// Reconstructed function
void* __thiscall UIManager::loadScreen(UIManager* thisPtr) {
    char isLoaded;
    void* screenData;
    char* screenName;
    int result;
    void* allocator;
    void* allocatedData;
    AllocParams allocParams;
    void* local_34;
    void* local_38;
    void* local_24;
    int local_18;

    allocator = thisPtr->screenData; // param_1[5] initially
    local_38 = nullptr;
    local_24 = nullptr;

    // Check type hash
    if (thisPtr->typeHash == 0x3a063031) {
        // "get" type: return existing screen
        thisPtr->storedScreen = thisPtr->currentScreen;
        return thisPtr->currentScreen;
    }

    if (thisPtr->typeHash == 0x378ce1fc) {
        // "destroy" type
        if (g_uiSystemInitialized == 0) {
            initUISystem();
        }
        screenData = thisPtr->currentScreen;
        thisPtr->storedScreen = screenData;
        destroyScreen(screenData);
        return screenData;
    }

    if ((thisPtr->typeHash != 0x3a063044) && (thisPtr->typeHash == 0x3033fbe9)) {
        // "create" type
        local_18 = thisPtr->screenSize; // param_1[6]
        screenData = thisPtr->currentScreen; // param_1[5]
        // Clear local variables
        memset(&local_24, 0, 0x14); // local_1c, local_20, local_10, local_c, local_24
        local_24 = screenData;
        screenName = (char*)getCurrentScreenName();
        preloadScreen();
        isLoaded = isScreenLoaded();

        if (g_loadingState == 0) {
            if (isLoaded != 0) {
                return &g_defaultScreen;
            }
        } else if ((unsigned int)(g_loadingState - 1) < 3) {
            if (isLoaded == 0) {
                result = checkScreenExists(g_someGlobal, screenName);
                if (result != 0) {
                    return &g_defaultScreen;
                }
            } else {
                loadScreenData();
            }
        }

        local_38 = getScreenData();
        if (local_38 != nullptr) {
            allocator = *(void**)(g_allocator + 4); // Get allocator vtable
            local_34 = nullptr;

            if ((screenName == nullptr) || (result = _stricmp(screenName, "onlinemenu"), result != 0)) {
                result = _stricmp(screenName, "communitymenu");
                if (result == 0) {
                    allocParams.type = 2;
                    allocParams.alignment = 0x10;
                    allocParams.unknown = 0;
                    allocatedData = (*(void* (*)(int, AllocParams*))(*allocator))(0x2e028, &allocParams);
                    memcpy(allocatedData, g_communityMenuData, 0x2e028);
                } else {
                    result = _stricmp(screenName, "doncontrol");
                    if (result == 0) {
                        allocParams.type = 2;
                        allocParams.alignment = 0x10;
                        allocParams.unknown = 0;
                        allocatedData = (*(void* (*)(int, AllocParams*))(*allocator))(0x2eb8, &allocParams);
                        memcpy(allocatedData, g_donControlData, 0x2eb8);
                    } else {
                        result = _stricmp(screenName, "scoreboard");
                        if (result == 0) {
                            allocParams.type = 2;
                            allocParams.alignment = 0x10;
                            allocParams.unknown = 0;
                            allocatedData = (*(void* (*)(int, AllocParams*))(*allocator))(0x1c420, &allocParams);
                            memcpy(allocatedData, g_scoreboardData, 0x1c420);
                        } else {
                            result = _stricmp(screenName, "moneypopup");
                            if (result == 0) {
                                allocParams.type = 2;
                                allocParams.alignment = 0x10;
                                allocParams.unknown = 0;
                                allocatedData = (*(void* (*)(int, AllocParams*))(*allocator))(0x44430, &allocParams);
                                memcpy(allocatedData, g_moneyPopupData, 0x44430);
                            } else {
                                result = _stricmp(screenName, "finalscore");
                                if (result == 0) {
                                    allocParams.type = 2;
                                    allocParams.alignment = 0x10;
                                    allocParams.unknown = 0;
                                    allocatedData = (*(void* (*)(int, AllocParams*))(*allocator))(0x11580, &allocParams);
                                    memcpy(allocatedData, g_finalScoreData, 0x11580);
                                } else {
                                    result = _stricmp(screenName, "hudmultiplayer");
                                    if (result == 0) {
                                        allocParams.type = 2;
                                        allocParams.alignment = 0x10;
                                        allocParams.unknown = 0;
                                        allocatedData = (*(void* (*)(int, AllocParams*))(*allocator))(0x4920, &allocParams);
                                        memcpy(allocatedData, g_hudMultiplayerData, 0x4920);
                                    } else {
                                        result = _stricmp(screenName, "onlineinstruct");
                                        if (result == 0) {
                                            allocParams.type = 2;
                                            allocParams.alignment = 0x10;
                                            allocParams.unknown = 0;
                                            allocatedData = (*(void* (*)(int, AllocParams*))(*allocator))(0x21e50, &allocParams);
                                            memcpy(allocatedData, g_onlineInstructData, 0x21e50);
                                        } else {
                                            result = _stricmp(screenName, "frontendoptions");
                                            if (result == 0) {
                                                allocParams.type = 2;
                                                allocParams.alignment = 0x10;
                                                allocParams.unknown = 0;
                                                allocatedData = (*(void* (*)(int, AllocParams*))(*allocator))(0x18d8, &allocParams);
                                                memcpy(allocatedData, g_frontendOptionsData, 0x18d8);
                                            } else {
                                                result = _stricmp(screenName, "systemsettings");
                                                if (result == 0) {
                                                    allocParams.type = 2;
                                                    allocParams.alignment = 0x10;
                                                    allocParams.unknown = 0;
                                                    allocatedData = (*(void* (*)(int, AllocParams*))(*allocator))(0x139b0, &allocParams);
                                                    memcpy(allocatedData, g_systemSettingsData, 0x139b0);
                                                } else {
                                                    result = _stricmp(screenName, "controlsetup");
                                                    if (result == 0) {
                                                        allocParams.type = 2;
                                                        allocParams.alignment = 0x10;
                                                        allocParams.unknown = 0;
                                                        allocatedData = (*(void* (*)(int, AllocParams*))(*allocator))(0x15b40, &allocParams);
                                                        memcpy(allocatedData, g_controlSetupData, 0x15b40);
                                                    } else {
                                                        // Unknown screen name: use generic loader
                                                        FUN_0049c9e0(&local_34, &thisPtr);
                                                        local_18 = *(int*)(extraout_ECX + 0x18); // size from some struct
                                                        allocator = thisPtr->screenData;
                                                        allocatedData = local_34;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                // "onlinemenu" case
                allocParams.type = 2;
                allocParams.alignment = 0x10;
                allocParams.unknown = 0;
                allocatedData = (*(void* (*)(int, AllocParams*))(*allocator))(0x2f2d0, &allocParams);
                memcpy(allocatedData, g_onlineMenuData, 0x2f2d0);
            }

            // Clear local variables again (redundant)
            memset(&local_24, 0, 0x14);
            local_24 = allocatedData;
            local_18 = local_18; // size from above
            setupScreen();
            isLoaded = validateScreen(local_38);
            if (isLoaded == 0) {
                local_38 = nullptr;
            }
            thisPtr = (UIManager*)g_anotherGlobal;
            initializeScreen(allocator, allocatedData);
            return local_38;
        }
    }
    return nullptr;
}