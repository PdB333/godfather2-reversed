// FUNC_NAME: Player::update

#include <cstdint>

// Forward declarations of called functions
bool isGameActive();           // FUN_00481620
void pushCommandStack();       // FUN_007a6c60
bool isGamePaused();           // FUN_0089c630
void handlePause();            // FUN_0079e330
bool isGameMenuActive();       // FUN_008a4380
void updateGeneral();          // FUN_00806d00
void setFlag(int);             // FUN_007a4250
bool isPlayerAlive();          // FUN_00481640
bool isTargetValid(int);       // FUN_007a7010
void updateMovement();         // FUN_007a64e0
void updateOrientation();      // FUN_007a6610
void playIdleAnimation();      // FUN_007993e0
void* getCamera();             // FUN_00471610
float getInputMagnitude(int, int, int); // FUN_00465ca0
void releaseVehicleInput(int); // FUN_007eec00

// External globals (probably class statics or game globals)
extern int gCommandStackDepth;   // DAT_0112b220
extern int* gCommandStackBase;   // DAT_0112b21c
extern int gGameManager;         // DAT_0112b9b4
extern float gDeltaTime;         // DAT_012067e8
extern float gCameraThreshold;   // DAT_00d5ef84
extern float gInputThreshold;    // DAT_00d5c458
extern int gSomeGlobal;          // DAT_01205224

// Player class offset constants (from decompiled offsets)
constexpr int kFlags = 0x927;        // bitfield flags
constexpr int kFlags2 = 0x928;       // another bitfield
constexpr int kFlags3 = 0x23a;       // third bitfield
constexpr int kPlayerType = 0xad;    // e.g., 0 = player, 1 = AI
constexpr int kTargetA = 0x7be;      // first target index
constexpr int kTargetB = 0x7bd;      // second target index
constexpr int kTargetFlag = 0xc47;   // target dead flag
constexpr int kVehicleHandle = 0x783;
constexpr int kVehicleActive = 0x787;
constexpr int kTimer1 = 0x862;       // accumulated time
constexpr int kTimer2 = 0x863;       // secondary timer
constexpr int kTimerThreshold = 0x852; // time limit for attack
constexpr int kTimerRatio = 0x851;    // threshold ratio
constexpr int kPosX = 0x939;         // world position X
constexpr int kPosY = 0x93a;         // world position Y
constexpr int kPosZ = 0x93b;         // world position Z
constexpr int kVulnerability = 0x9c5; // vulnerability timer
constexpr int kInputChar = 0x926;    // input character index

void __fastcall Player::update(int* thisPtr) {
    int* piVar1;
    float fVar3, fVar9, fVar8;
    char cVar4;
    int iVar5;
    float fStack_2e0;
    // Command stack copy area
    char commandStackCopy[712]; // 0xb1 * 4 = 284*4? Actually 0xb1 = 177, times 4 = 708, plus some alignment

    // Check if game is active
    if (isGameActive()) {
        // Push command stack if depth > 0
        if (gCommandStackDepth != 0) {
            // Copy top of stack to local buffer
            int* src = gCommandStackBase;
            int* dst = reinterpret_cast<int*>(&commandStackCopy);
            for (int i = 0xb1; i != 0; i--) {
                *dst++ = *src++;
            }
            pushCommandStack(); // FUN_007a6c60
            // If depth > 1, shift data
            if (gCommandStackDepth != 1) {
                src = gCommandStackBase + gCommandStackDepth * 0xb1 - 0xb1;
                dst = gCommandStackBase;
                for (int i = 0xb1; i != 0; i--) {
                    *dst++ = *src++;
                }
            }
            gCommandStackDepth--;
        }

        // Check pause state
        cVar4 = isGamePaused(); // FUN_0089c630
        if (cVar4) {
            if (!(thisPtr[kFlags] >> 5 & 1)) return; // bit5 must be set
            handlePause(); // FUN_0079e330
            return;
        }

        // Check menu active
        cVar4 = isGameMenuActive(); // FUN_008a4380
        if (cVar4 && thisPtr[kPlayerType] == 0) return; // player in menu
    }

    // General update
    updateGeneral(); // FUN_00806d00

    // Check pause bit again
    if (thisPtr[kFlags] >> 5 & 1) {
        handlePause(); // FUN_0079e330
    }

    // If flag bit0 not set, set it
    if (!(*(uint8_t*)(thisPtr + kFlags) & 1)) { // bit0
        setFlag(1); // FUN_007a4250(1)
    }

    // Check if player is alive and has valid targets
    cVar4 = isPlayerAlive(); // FUN_00481640
    if (cVar4 && thisPtr[kTargetA] != -1 && thisPtr[kTargetB] != -1) {
        piVar1 = *(int**)(*(int*)(gGameManager + 0x40)); // some manager pointer
        if (piVar1 != nullptr && piVar1[0x36] == 2) { // check state
            if (*(char*)(thisPtr + kTargetFlag) == '\0' && !isTargetValid(thisPtr[kTargetA])) {
                // Call virtual function at vtable+0xc4 (likely something like "onTargetInvalid")
                (*(void (**)(int*))(*(int*)thisPtr + 0xc4))(thisPtr);
            }
        }
    }

    // Call virtual function at vtable+0x2fc (likely render or state update)
    (*(void (**)(int, int))(*(int*)thisPtr + 0x2fc))(gSomeGlobal, gDeltaTime);

    // Second game active check
    cVar4 = isGameActive();
    if (cVar4 && !(thisPtr[kFlags3] >> 0x1d & 1)) { // bit29 not set
        updateMovement();   // FUN_007a64e0
        updateOrientation(); // FUN_007a6610
    }

    // If bit7 set, play idle animation
    if (thisPtr[kFlags] >> 7 & 1) {
        playIdleAnimation(); // FUN_007993e0
    }

    // Camera distance check
    iVar5 = (int)getCamera(); // FUN_00471610
    float camX = *(float*)(iVar5 + 0x30);
    float camY = *(float*)(iVar5 + 0x34);
    float camZ = *(float*)(iVar5 + 0x38);
    float playerX = (float)thisPtr[kPosX];
    float playerY = (float)thisPtr[kPosY];
    float playerZ = (float)thisPtr[kPosZ];
    // The decompiled uses a strange (uint) cast and & with constant; likely a fabs approximation?
    if (gCameraThreshold < (float)((uint)(camX - playerX) & 0x7FFFFFFF) ||
        gCameraThreshold < (float)((uint)(camY - playerY) & 0x7FFFFFFF) ||
        gCameraThreshold < (float)((uint)(camZ - playerZ) & 0x7FFFFFFF)) {
        if ((float)thisPtr[kVulnerability] <= 0.0f && (thisPtr[kFlags3] >> 1 & 1)) {
            thisPtr[kFlags2] |= 8; // set bit3
        }
    }

    fStack_2e0 = 0.0f;
    // Input magnitude check
    if ((thisPtr[kFlags] >> 1 & 1) && isGameActive()) {
        fStack_2e0 = getInputMagnitude((char)thisPtr[kInputChar], 0, 1); // FUN_00465ca0
    }

    if (fStack_2e0 <= gInputThreshold) {
        thisPtr[kFlags2] &= ~(1 << 25); // clear bit25
    } else {
        thisPtr[kFlags2] |= (1 << 25); // set bit25
    }

    // Vehicle input release
    if (thisPtr[kVehicleActive] != 0) {
        releaseVehicleInput(thisPtr[kVehicleHandle]); // FUN_007eec00
    }

    fVar3 = gDeltaTime;
    // Timer update
    thisPtr[kTimer1] = (int)((float)thisPtr[kTimer1] + gDeltaTime);

    // Get two virtual function return floats (e.g., getAttackSpeed, getDefense?)
    fVar8 = (*(float (**)())(*(int*)thisPtr + 0xc0))(); // vtable+0xc0
    fVar9 = (*(float (**)())(*(int*)thisPtr + 0xc4))(); // vtable+0xc4

    // Attack timer logic
    if ((float)thisPtr[kTimerThreshold] <= (float)thisPtr[kTimer1] &&
        (float)thisPtr[kTimer1] != (float)thisPtr[kTimerThreshold] &&
        (fVar8 / fVar9) < (float)thisPtr[kTimerRatio] &&
        (*(float (**)())(*(int*)thisPtr + 0xc0))() > 0.0f) {
        thisPtr[kTimer2] = (int)((float)thisPtr[kTimer2] + fVar3);
    }
}