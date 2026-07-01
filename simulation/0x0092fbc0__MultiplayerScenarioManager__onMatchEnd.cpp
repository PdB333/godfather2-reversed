// FUNC_NAME: MultiplayerScenarioManager::onMatchEnd

#include <cstdint>

// Global pointer to the main game object (likely EARS::Framework::Game)
extern void* g_pGameObject; // DAT_012233a0

// Global pointer to scenario manager data (possibly MultiplayerScenarioManager)
extern void* g_pScenarioManager; // DAT_01223484

// Global for some flag/setting
extern uint8_t g_showDonForfeitFlag; // DAT_0112982c + 0x92

// Global for weapon license upgrade flag
extern uint8_t g_weaponLicenseUpgradedFlag; // DAT_01129908 + 0x19

// Engine debug print function (console)
void debugPrint(const char* format, int arg1, const char* arg2, int arg3, const char* arg4);

// Score initialization routine
void initScoreDisplay();

// Get score value (returns short)
short getScore(int playerIndex);

// Internal score evaluation functions
uint32_t evaluateScoreCondition(int condition);
uint32_t buildScoreFlags(uint32_t condition, uint32_t personalScore, uint32_t platformData);
void showFinalScore(int score, uint32_t flags, uint32_t condition, uint32_t personalScore, uint32_t platformData);

// Set text in some UI field
void setUIText(int fieldIndex, const char* text, int maxLen, int flags);

// Show personal score overlay
void showPersonalScore(uint32_t personalId, uint32_t scoreData);

// Hide/Hide screen element
void hideScreenElement(int elementId);

// Memory copy
void memcpy32(void* dest, const void* src, int size);

// Play sound effect
void playSoundFx(int soundId);

// Internal tick/update function
void engineTick();

// Object allocator for notifications
void* allocateNotificationObject(int size);

// Get notification slot by index
void* getNotificationSlot(int index);

// Show a popup notification (title string)
void showNotification(const char* title);

// Set notification text
void setNotificationString(void* notification, const char* text);

// Finalize and display the notification
void finalizeAndShowNotification();

// Get current weapon upgrade level
int getCurrentWeaponLicenseLevel(int playerId);

// Format a string into a buffer (variadic)
void formatString(char** outBuffer, int maxLen, const char* format, ...);

// String concatenation/utility
void stringCopy(char** dest, const char* src);

struct MultiplayerScenarioManager {
    // Offsets based on decompiled accesses
    // +0x50 : some data block (size 0x8000)
    // +0xe8 : int (set to 1 during match end)
    // +0x108 : string pointer (or ID)
    // +0x118 : int (compared to current frame's score)
    // +0x130 : int (personal score related)
    // +0x148 : int (personal ID)
    // +0x168 : float (timer value)
    // +0x16c : int (flag if player exists)
    // +300 (0x12c) : int (field index for text)

    void onMatchEnd(); // __thiscall at 0x0092fbc0
};

void MultiplayerScenarioManager::onMatchEnd() {
    // Local variables
    int teamDonForfeitStatus = 0; // iVar10 initially 0
    bool donForfeitVisible = false;
    int licenseLevel = 0;
    uint32_t scoreCondition = 0;
    uint32_t personalScoreData = 0;
    uint32_t platformData = 0;
    uint32_t scoreFlags = 0;
    char* notificationBuffer = nullptr;
    char* weaponUpgradeBuffer = nullptr;

    debugPrint("SetPlatform", 0, &DAT_00d88e88, 1, &DAT_00d85114); // Unknown constants

    initScoreDisplay();

    // Access to game object (global)
    void* gameObject = *(void**)(*(uintptr_t*)((uintptr_t)g_pGameObject + 4));
    int gameStateOffset; // iVar9
    if (gameObject == nullptr) {
        gameStateOffset = 0;
    } else {
        gameStateOffset = (int)gameObject - 0x1f30; // base of game state
    }

    personalScoreData = 0;
    if (g_pScenarioManager != nullptr) {
        personalScoreData = *(uint32_t*)((uintptr_t)g_pScenarioManager + 0x394);
    }

    int currentScore = *(int*)(gameStateOffset + 0x1ef4); // iVar9

    void* gameObject2 = *(void**)(*(uintptr_t*)((uintptr_t)g_pGameObject + 4));
    int gameStateOffset2;
    if (gameObject2 == nullptr) {
        gameStateOffset2 = 0;
    } else {
        gameStateOffset2 = (int)gameObject2 - 0x1f30;
    }

    if (*(int*)(this + 0x16c) != 0 && gameStateOffset2 != 0) {
        // Get player's score value
        uint32_t playerScoreId = *(uint32_t*)(gameStateOffset2 + 0x1ef8);
        short score = getScore(playerScoreId);
        teamDonForfeitStatus = (int)score;
    }

    uint32_t platformData2 = evaluateScoreCondition(0); // FUN_0092e200 - likely returns something
    uint32_t isCurrentFrameScoreMatch = (uint32_t)(*(int*)(this + 0x118) == currentScore); // uVar5
    uint32_t combinedFlags = buildScoreFlags(isCurrentFrameScoreMatch, personalScoreData, platformData2);
    showFinalScore(teamDonForfeitStatus, combinedFlags, isCurrentFrameScoreMatch, personalScoreData, platformData2);

    // Get text string for UI
    const char* textId = *(const char**)(this + 0x108);
    if (textId == nullptr) {
        textId = &DAT_0120546e; // default empty string
    }

    setUIText(*(int*)(this + 300), textId, 0x80, 0);

    debugPrint("ShowFinalScore", 0, &DAT_00d88e88, 0);
    *(int*)(this + 0xe8) = 1; // Mark score shown

    debugPrint("ShowPersonal", 0, &DAT_00d88e88, 0);

    showPersonalScore(*(uint32_t*)(this + 0x148), *(uint32_t*)(this + 0x130));

    // Dereference a global pointer for some flag
    int globalFlagAddr = DAT_0112a838;
    hideScreenElement(0);
    *(uint8_t*)(globalFlagAddr + 0xcc) = 1; // Some flag

    if (DAT_012069b4 != 0) {
        // Copy large data block into object (maybe position data)
        memcpy32((void*)(this + 0x50), &DAT_012069b4, 0x8000);
    }

    *(float*)(this + 0x168) = DAT_01205214 + _DAT_00d88e34; // Timer offset

    playSoundFx(10);

    // Call engine tick function
    (*(void (**)())(*(uintptr_t*)DAT_01129a74 + 0x28))();

    // Handle "don forfeited" notification
    if (g_pScenarioManager != nullptr) {
        int forfeitTeam = *(int*)((uintptr_t)g_pScenarioManager + 0x3b4);
        if (forfeitTeam != -1) {
            // Flag that don forfeited is shown
            *(uint8_t*)(DAT_0112982c + 0x92) = 1;

            void* notificationObj = allocateNotificationObject(0xf0);
            if (notificationObj == nullptr) {
                notificationObj = nullptr;
            } else {
                notificationObj = getNotificationSlot(0);
            }

            const char* forfeitMessage = "$mp_don_forfeited_team_red";
            if (forfeitTeam != 0) {
                forfeitMessage = "$mp_don_forfeited_team_blue";
            }
            showNotification(forfeitMessage);

            const char* notificationText = notificationBuffer;
            if (notificationBuffer == nullptr) {
                notificationText = &DAT_0120546e;
            }
            setNotificationString(notificationObj, notificationText);
            *(int*)(notificationObj + 0xc) = 3;                 // Notification type
            *(void**)(notificationObj + 0x14) = (void*)FUN_00982b30; // Callback function
            finalizeAndShowNotification();

            if (notificationBuffer != nullptr) {
                // Deallocate? The code calls a function pointer at pcStack_14
                // This seems to be a destructor or deleter
                (*(void (*)(void*))notificationObj)(notificationBuffer);
            }
        }
    }

    // Handle "weapon license upgraded" notification
    if (*(uint8_t*)(DAT_01129908 + 0x19) != 0) {
        notificationBuffer = nullptr;
        // Some cleanup? The code initializes a local stack for the string

        int playerId = *(int*)(*(uintptr_t*)(DAT_0112b9b4 + 0x28) + *(int*)(DAT_0112b9b4 + 0x34) * 4);
        int licenseLevel = getCurrentWeaponLicenseLevel(playerId);

        // Format the upgrade message
        formatString(&weaponUpgradeBuffer, 1, "{n:%d}{$mp_weapon_license_upgraded}", licenseLevel);

        const char* upgradeText = weaponUpgradeBuffer;
        if (weaponUpgradeBuffer == nullptr) {
            upgradeText = &DAT_0120546e;
        }
        stringCopy(&notificationBuffer, upgradeText);

        void* notificationObj2 = allocateNotificationObject(0xf0);
        if (notificationObj2 == nullptr) {
            notificationObj2 = nullptr;
        } else {
            notificationObj2 = getNotificationSlot(0);
        }

        const char* notificationText2 = notificationBuffer;
        if (notificationBuffer == nullptr) {
            notificationText2 = &DAT_0120546e;
        }
        setNotificationString(notificationObj2, notificationText2);
        *(int*)(notificationObj2 + 0xc) = 3;
        *(void**)(notificationObj2 + 0x14) = (void*)FUN_00982b30;
        finalizeAndShowNotification();

        // Reset the upgrade flag
        *(uint8_t*)(DAT_01129908 + 0x19) = 0;

        // Free buffers if allocated
        if (weaponUpgradeBuffer != nullptr) {
            (*(void (*)(void*))weaponUpgradeBuffer)(weaponUpgradeBuffer);
        }
        if (notificationBuffer != nullptr) {
            (*(void (*)(void*))notificationBuffer)(notificationBuffer);
        }
    }

    return;
}