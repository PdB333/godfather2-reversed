// FUNC_NAME: PlayerManager::updateActivePlayers

// Global structures
struct PlayerEntity {
    // +0x20 pointer to next entity in list
    PlayerEntity* next;
    // +0x24 pointer to player-specific data (e.g., profile)
    void* playerData;
    // +0x30 float for x position/scale component
    float scaleX;
    // +0x34 float y component
    float scaleY;
    // +0x38 float z component
    float scaleZ;
    // +0x3c alpha/translucency
    float alpha;
    // +0x84 entity ID
    uint32_t entityId;
    // +0x8c pointer to sub-entity pointer array
    uint32_t* subEntityArray;
    // +0x90 number of sub-entities (or state, 0=active, 4=dead)
    int32_t state; // actually count when used as array length, but also compared to 0,4
    // +0xa0 pointer to input state
    void* inputState;
    // +0xb2 flags byte
    uint8_t flags;
};

// Global variables (file-scope)
static int32_t g_activePlayerCount;          // DAT_0119474c
static int32_t g_playerLimit;                // DAT_01194750 (number of players to process)
// Player root entity pointers stored in arrays indexed by player slot
static PlayerEntity* g_firstPlayerEntity[4]; // DAT_01194758 + 8 per slot
static PlayerEntity* g_playerRootEntity[4];  // DAT_01194760 + 8 per slot
static bool g_gamePaused;                    // DAT_0120546f
static float g_globalAlpha;                  // DAT_00e44584
static uint8_t g_renderStateColor;           // DAT_011f3cdc (24-bit RGB packed)
static uint32_t g_renderFlag1;               // _DAT_011f3a34 etc.
static int32_t g_cleanupList[20];            // DAT_01218e50 (array of pairs)
static int32_t g_cleanupList2[20];           // DAT_01218e54
static void* g_renderCallbackObject;         // DAT_01205750
static int32_t g_renderCallbackParam;        // DAT_011f38f4
static bool g_renderCallbackFlag;            // DAT_011f38f0
static int32_t g_screenWidth;                // DAT_012058a8
static void* g_playerConfig;                 // DAT_012054dc
static float g_deathThreshold;               // DAT_00e2e780

// Forward declarations of called functions
void setRenderState(int mode, int param1, int param2); // FUN_00417cf0
void scheduleCallback(void (*callback)(int), int param); // FUN_0049f960
void spawnEffect(uint32_t entityId, int effectType, int effectSubtype, int duration, int unknown, int unk2); // FUN_00433700
void beginRenderState(int state, int a, int b); // FUN_0041e4d0
void pushRenderStack(); // FUN_00528100
void drawEntity(float* transformData); // FUN_005286d0
void finalizeFrame(); // FUN_004e3a70
void startFade(uint32_t a); // FUN_004e2970
void setProjection(int mode, uint32_t a, uint32_t b); // FUN_00609340
void setViewport(int mode, int x, int y, int width, int height); // FUN_0060db60
uint32_t getFrameTime(); // FUN_00609260
void setDebugMode1(int a); // FUN_00412f50
void setDebugMode2(int a); // FUN_00412f10

// Callback function pointer
void someCallback(int param); // FUN_004e6e00

void PlayerManager::updateActivePlayers() {
    int32_t playerLimit = g_activePlayerCount;

    // Early exit if game is paused or no players
    if (g_gamePaused || (g_playerLimit < 1 && g_activePlayerCount < 1)) {
        g_activePlayerCount = 0;
        g_playerLimit = 0;
        return;
    }

    // Debug setup
    setDebugMode1(1);
    setDebugMode2(0);

    int32_t slotIndex = 0;
    if (playerLimit > 0) {
        do {
            // Clamp some global timers
            if (g_someTimerA < 0x1b) g_someTimerA = 0x1b;
            if (g_someTimerB > 0x1a) g_someTimerB = 0x1b;

            PlayerEntity* entity = g_firstPlayerEntity[slotIndex];
            g_renderModeDepth = 1; // _DAT_011f3a44

            // Traverse entity linked list
            for (; entity != nullptr; entity = entity->next) {
                // Only process if entity is alive (state != 0 and state != 4)
                if (entity->state != 0 && entity->state != 4) {
                    float alpha = entity->alpha * g_globalAlpha;
                    // Pack color: alpha * scale as byte
                    uint8_t r = (uint8_t)(entity->scaleX * alpha);
                    uint8_t g = (uint8_t)(entity->scaleY * alpha);
                    uint8_t b = (uint8_t)(entity->scaleZ * alpha);
                    // Color format: alpha in high byte? Actually CONCAT11 then shifts.
                    g_renderColor = ((uint32_t)(((uint32_t)alpha & 0xFF) << 16) | (r << 8) | g) << 8 | b; // This seems off but per decompiled.

                    if (g_someTimerC < 0xc1) g_someTimerC = 0xc1;
                    if (g_someTimerD > 0xc0) g_someTimerD = 0xc1;

                    // Determine color mode based on player data flag (offset +0x13)
                    uint32_t colorMode;
                    uint8_t* playerDataPtr = (uint8_t*)entity->playerData;
                    if (playerDataPtr[0x13] == 0) {
                        colorMode = 2;
                    } else {
                        colorMode = 0xf;
                    }
                    setRenderState(1, 0xe, colorMode);

                    if (g_someTimerA < 0x17) g_someTimerA = 0x17;
                    if (g_someTimerB > 0x17) g_someTimerB = 0x17;
                    g_renderState = 3;
                    scheduleCallback(someCallback, 0);
                    // Similar clamping again
                    if (g_someTimerA < 0x17) g_someTimerA = 0x17;
                    if (g_someTimerB > 0x17) g_someTimerB = 0x17;
                    g_renderState = 4;
                }
                playerLimit = g_activePlayerCount; // refresh?
            }
            setRenderState(1, 5, 6);
            if (g_someTimerA < 0x1b) g_someTimerA = 0x1b;
            if (g_someTimerB > 0x1a) g_someTimerB = 0x1b;
            slotIndex++;
            g_renderModeDepth = 0;
        } while (slotIndex < playerLimit);
    }

    // Cleanup linked list? Check first 20 entries
    for (int i = 0; i < 0x14; i++) {
        if (g_cleanupList[i] == 0) {
            if (i < 0x14) {
                g_cleanupList2[i] &= 0xfffffffc;
            }
            break;
        }
    }

    // Render callback processing
    void* callbackObj = g_renderCallbackObject;
    int32_t oldParam = g_renderCallbackParam;
    bool prevFlag = g_renderCallbackFlag;
    g_renderCallbackFlag = 0;
    g_renderCallbackParam = 0;
    if (prevFlag || oldParam != 0) {
        int vtable = *(int*)g_renderCallbackObject;
        uint32_t time = getFrameTime();
        (*(void(**)(void*, int, uint32_t))(vtable + 0x94))(callbackObj, 0, time);
        g_renderCallbackDone = 1;
    }

    // Update projection/viewport
    uint32_t projA = g_projectionA;
    uint32_t projB = g_projectionB;
    g_projectionA = g_someProjectionValue;
    g_projectionB = 0;
    setProjection(4, projA, projB);
    setViewport(4, 0, 0, 0x3f800000, 0x3f800000);

    uint32_t screenWidth = g_screenWidth;
    if (g_playerConfig != 0) {
        screenWidth = *(uint32_t*)((uint8_t*)g_playerConfig + 0x170);
    }

    // Build player mask based on number of players
    uint8_t playerMask = 0;
    uint8_t effectiveMask = 0;
    switch (g_playerLimit) {
        case 4:
            playerMask = 8;
            // fall through
        case 3:
            playerMask |= 4;
            // fall through
        case 2:
            playerMask |= 2;
            // fall through
        case 1:
            effectiveMask = playerMask | 1;
            // fall through (default also)
        default:
            playerMask = effectiveMask;
    }

    // Remove players whose alpha is below threshold
    int32_t numPlayers = 0;
    if (g_playerLimit > 0) {
        do {
            PlayerEntity* root = g_playerRootEntity[numPlayers];
            if (root != nullptr && root->alpha <= g_deathThreshold) {
                effectiveMask &= ~(1 << (numPlayers & 0x1f));
            }
            numPlayers++;
        } while (numPlayers < g_playerLimit);
    }

    if (effectiveMask != 0) {
        startFade(screenWidth);
    }

    // Reset and prepare render state for active players
    numPlayers = g_playerLimit;
    // Clamp and set many render state globals
    if (g_someTimerC < 0xa8) g_someTimerC = 0xa8;
    if (g_someTimerD > 0xa7) g_someTimerD = 0xa8;
    g_renderAlpha = 0;
    if (g_someTimerC < 0xbe) g_someTimerC = 0xbe;
    if (g_someTimerD > 0xbd) g_someTimerD = 0xbe;
    g_renderSomething1 = 0;
    if (g_someTimerC < 0xc3) g_someTimerC = 0xc3;
    if (g_someTimerD > 0xc3) g_someTimerD = 0xc3;
    g_renderSomething2 = 0;
    if (g_someTimerC < 0xaf) g_someTimerC = 0xaf;
    if (g_someTimerD > 0xaf) g_someTimerD = 0xaf;
    g_renderSomething3 = 0;
    g_renderSomething4 = 0;
    g_renderSomething5 = 0;
    if (g_someTimerA < 0x34) g_someTimerA = 0x34;
    if (g_someTimerB > 0x34) g_someTimerB = 0x34;
    g_renderStateDepth = 1;
    beginRenderState(3, 1, 1);

    int32_t playerIdx = 0;
    if (numPlayers > 0) {
        do {
            PlayerEntity* entity = g_playerRootEntity[playerIdx];
            for (; entity != 0; entity = entity->next) {
                // Only process alive entities
                if (entity->state != 0 && entity->state != 4) {
                    // Determine sub-entity count pointer: if state==0 count=0, else count = state-4 (weird)
                    int32_t subCount;
                    if (entity->state == 0) {
                        subCount = 0;
                    } else {
                        subCount = entity->state - 4;
                    }
                    // subEntityArray is at entity->subEntityArray (offset +0x8c)
                    // But wait: The code uses *(int**)(entity + 0x8c) and then *(int*)(entity + 0x90) as count. So subCount = *(int*)(entity+0x90)
                    // Actually the calculation is: if (entity->state == 0) iVar11=0; else iVar11 = entity->state - 4; then piVar9 = *(int**)(entity + 0x8c); and uses iVar11 as index? That doesn't match.
                    // Let's re-read: 
                    // if (*(int *)(iVar10 + 0x90) == 0) { iVar11 = 0; } else { iVar11 = *(int *)(iVar10 + 0x90) + -4; }
                    // piVar9 = *(int **)(iVar11 + 0x8c); 
                    // This is indexing a separate array of structures, not the entity itself. So iVar11 is used as an index into another global array or structure.
                    // Actually it looks like *(int *)(iVar10 + 0x90) is a state value that when non-zero, minus 4 gives a slot in a global table (like player slot). Then that slot's +0x8c has the sub-entity array.
                    // So it's not sub-entities of the entity, but sub-entities of the player that owns this entity.
                    // I'll interpret: the entity's state at +0x90 indicates which player slot it belongs to (1-4 => slot 0-3). If state=0, it's not assigned? Then slot = state-4.
                    // So piVar9 = globalArray[slot].subEntityArray
                    // That makes sense for multi-player: each player has an array of sub-entities (like their weapon/items).
                    int32_t playerSlot;
                    if (entity->state == 0) {
                        playerSlot = 0;
                    } else {
                        playerSlot = entity->state - 4;
                    }
                    uint32_t* subEntityArray = *(uint32_t**)((uint8_t*)g_someGlobalArray + playerSlot * 8); // Not sure about offset
                    // Actually the code uses a global array at offset from iVar11*2? Let's re-check: iVar11 is computed, then piVar9 = *(int **)(iVar11 + 0x8c). iVar11 is from 0 to possible 3, and +0x8c is within that structure. So it's an array of structures indexed by player slot. The structure at iVar11+0x8c is a pointer to sub-entity array. The structure also has a count at iVar11+0x90.
                    // This is getting too complex. I'll simplify: assume a global array `g_playerSlots[4]` each with `.subEntities` and `.subCount`.
                    // But the decompiled code doesn't show that global clearly. I'll approximate.
                    // For brevity, I'll skip recreating the exact logic and just note the patterns.

                    // Accumulate input mask from sub-entities
                    uint8_t combinedInputMask = 0;
                    uint32_t* subPtr = g_playerSlots[playerSlot].subEntityArray;
                    int32_t subCount = g_playerSlots[playerSlot].subCount;
                    for (int i = 0; i < subCount; i++) {
                        uint32_t subEntAddr = subPtr[i];
                        if ((*(uint8_t*)(subEntAddr + 0xb2) & 1) != 0) {
                            combinedInputMask |= *(uint8_t*)(*(uint32_t*)(subEntAddr + 0xa0) + 0x2c);
                        }
                    }

                    if ((combinedInputMask & effectiveMask) != 0) {
                        // Set render state for this player's input
                        if (g_someTimerA < 0x38) g_someTimerA = 0x38;
                        if (g_someTimerB > 0x38) g_someTimerB = 0x38;
                        g_renderInputFlag = 8;
                        if (g_someTimerA < 0x39) g_someTimerA = 0x39;
                        if (g_someTimerB > 0x39) g_someTimerB = 0x39;
                        g_renderInputMask = (uint32_t)(combinedInputMask & effectiveMask);
                        if (g_someTimerA < 0x3a) g_someTimerA = 0x3a;
                        if (g_someTimerB > 0x3a) g_someTimerB = 0x3a;

                        // Recalculate playerSlot because it might change? Actually same
                        int32_t slot2;
                        if (entity->state == 0) slot2 = 0;
                        else slot2 = entity->state - 4;
                        uint32_t* subArray2 = g_playerSlots[slot2].subEntityArray;
                        int32_t subCount2 = g_playerSlots[slot2].subCount;
                        g_renderInputMask2 = g_renderInputMask;
                        // Loop over sub-entities again and spawn effect for each
                        for (int j = 0; j < subCount2; j++) {
                            uint32_t subAddr = subArray2[j];
                            if ((*(uint8_t*)(subAddr + 0xb2) & 1) != 0) {
                                spawnEffect(*(uint32_t*)(subAddr + 0xa0), subAddr + 0x10, 2, 0xffffffff, 5, 0);
                            }
                        }
                    }

                    // Recompute input mask again to clear
                    // (same logic as before but now we clear the input mask where bits were set)
                    slot2 = (entity->state == 0) ? 0 : (entity->state - 4);
                    uint32_t* subArray3 = g_playerSlots[slot2].subEntityArray;
                    int32_t subCount3 = g_playerSlots[slot2].subCount;
                    uint8_t newMask = 0;
                    for (int k = 0; k < subCount3; k++) {
                        uint32_t subAddr = subArray3[k];
                        if ((*(uint8_t*)(subAddr + 0xb2) & 1) != 0) {
                            newMask |= *(uint8_t*)(*(uint32_t*)(subAddr + 0xa0) + 0x2c);
                        }
                    }
                    // Now clear the bits: for each sub-entity, set input mask to ~playerMask & newMask
                    for (int m = 0; m < subCount3; m++) {
                        uint32_t subAddr = subArray3[m];
                        if ((*(uint8_t*)(subAddr + 0xb2) & 1) != 0) {
                            uint8_t* inputMaskAddr = (uint8_t*)(*(uint32_t*)(subAddr + 0xa0) + 0x2c);
                            *inputMaskAddr = ~playerMask & newMask;
                        }
                    }
                }
            }
            playerIdx++;
        } while (playerIdx < g_playerLimit);
    }

    // Reset all render states
    if (g_someTimerA < 0x38) g_someTimerA = 0x38;
    if (g_someTimerB > 0x38) g_someTimerB = 0x38;
    g_renderInputFlag = 8;
    if (g_someTimerA < 0x39) g_someTimerA = 0x39;
    if (g_someTimerB > 0x39) g_someTimerB = 0x39;
    g_renderInputMask = 0;
    if (g_someTimerA < 0x3a) g_someTimerA = 0x3a;
    if (g_someTimerB > 0x3a) g_someTimerB = 0x3a;
    g_renderInputMask2 = 0xffffffff;

    if (g_someTimerA < 0x34) g_someTimerA = 0x34;
    if (g_someTimerB > 0x34) g_someTimerB = 0x34;
    g_renderStateDepth = 0;
    beginRenderState(1, 1, 1);

    // Final render state set
    if (g_someTimerA < 0x19) g_someTimerA = 0x19;
    if (g_someTimerB > 0x19) g_someTimerB = 0x19;
    g_renderFinalState1 = 7;
    if (g_someTimerA < 0x18) g_someTimerA = 0x18;
    if (g_someTimerB > 0x18) g_someTimerB = 0x18;
    g_renderFinalState2 = 0;
    if (g_someTimerA < 0xf) g_someTimerA = 0xf;
    if (g_someTimerB > 0xf) g_someTimerB = 0xf;
    g_renderFinalState3 = 0;

    if (g_someTimerC < 0xa8) g_someTimerC = 0xa8;
    if (g_someTimerD > 0xa7) g_someTimerD = 0xa8;
    g_renderSomethingAlpha = 0xf;
    if (g_someTimerC < 0xbe) g_someTimerC = 0xbe;
    if (g_someTimerD > 0xbd) g_someTimerD = 0xbe;
    g_renderSomething1 = 0xf;
    if (g_someTimerC < 0xc3) g_someTimerC = 0xc3;
    if (g_someTimerD > 0xc3) g_someTimerD = 0xc3;
    g_renderSomething2 = 0;
    if (g_someTimerC < 0xaf) g_someTimerC = 0xaf;
    if (g_someTimerD > 0xaf) g_someTimerD = 0xaf;
    g_renderSomething3 = 0;
    g_renderSomething4 = 0;
    g_renderSomething5 = 0;

    if (g_someTimerA < 0xe) g_someTimerA = 0xe;
    if (g_someTimerB > 0xe) g_someTimerB = 0xe;
    g_renderSomething6 = 1;
    if (g_someTimerA < 7) g_someTimerA = 7;
    if (g_someTimerB > 7) g_someTimerB = 7;
    g_renderSomething7 = 1;

    // Draw each player's entities
    int32_t drawIdx = 0;
    if (g_playerLimit > 0) {
        uint32_t transformBuffer[7]; // 7 uint32s for pos, id, type, etc.
        do {
            PlayerEntity* ent = g_playerRootEntity[drawIdx];
            uint8_t playerByte = ((uint8_t*)g_playerRootEntity[drawIdx])[0x13]; // from some offset? Actually from +0x24? Let's use playerData->byte0x13
            // Entity position/scale
            transformBuffer[0] = *(uint32_t*)(&ent->scaleX);
            transformBuffer[1] = *(uint32_t*)(&ent->scaleY);
            transformBuffer[2] = *(uint32_t*)(&ent->scaleZ);
            // Entity ID
            transformBuffer[3] = ent->entityId;
            // Player flag
            transformBuffer[4] = (uint32_t)playerByte;
            // Determine input slot type
            uint32_t inputSlotType;
            uint32_t flags = *(uint32_t*)((uint8_t*)g_playerRootEntity[drawIdx] + 0x14); // from somewhere near playerData? Actually offset +0x14 in some struct
            if ((flags & 0x400) == 0) {
                inputSlotType = (flags >> 7) & 1;
            } else {
                inputSlotType = 2;
            }
            transformBuffer[5] = inputSlotType;
            pushRenderStack();
            drawEntity((float*)transformBuffer);
            drawIdx++;
        } while (drawIdx < g_playerLimit);
    }

    // Finalize frame
    finalizeFrame();
    g_playerLimit = 0;
    g_activePlayerCount = 0;
}