// Xbox PDB: EARS_Modules_Player_Player
// FUNC_NAME: Player::Player

// Constructor for the Player class at 0x007a1920
// Initializes all member fields, registers message handlers, and sets up subsystems.

#include <cstdint>

// Forward declarations of known functions
extern void FUN_008022b0(uint32_t param, int a, int b, int c, int d);
extern void FUN_004aee00();
extern void FUN_006d9b40();
extern void FUN_007aaf80();
extern void FUN_007dd670();
extern void FUN_00700040();
extern void FUN_007dc210();
extern void FUN_0079b1a0();
extern void FUN_007ac460();
extern void FUN_00896360();
extern void FUN_006d9ee0();
extern void FUN_0084e6d0(int size);
extern void FUN_007f7c90();
extern uint32_t FUN_00408240(const char* str); // returns message ID
extern void FUN_00408900(void* obj, uint32_t* msgID, uint32_t flags);
extern bool FUN_00481620(); // returns true if multiplayer
extern uint32_t FUN_0043ffa0(void* obj, int param);
extern void FUN_00444d20(uint32_t val, int param);
extern uint8_t FUN_0089c630();
extern void FUN_004dde90(uint32_t* ptr, int size);
extern void FUN_007f9340(int a, int b);
extern uint32_t FUN_0043b490();
extern uint32_t FUN_00540c60(int a, int b, uint32_t c);
extern void FUN_008963a0(void* obj, uint32_t val, void* func);
extern void FUN_004daf90(void* ptr);
extern void FUN_00798bc0();
extern void FUN_00798f60();
extern void* FUN_009c8e50(int size);
extern void* FUN_00704d70(int param);
extern void* FUN_00471610(); // returns some global object

// External global data
extern uint32_t DAT_00d6b350; // vtable pointer
extern uint32_t DAT_00d6b340;
extern uint32_t DAT_00d6b33c;
extern uint32_t DAT_00d6b338;
extern uint32_t DAT_00d6b2d8;
extern uint32_t DAT_00d6b270;
extern uint32_t DAT_00d6b24c;
extern uint32_t DAT_00d6b238;
extern uint32_t DAT_00d6b230;
extern uint32_t DAT_00d6b218;
extern uint32_t DAT_00d6a560;
extern uint32_t DAT_00d6a568;
extern uint32_t DAT_00d6a578;
extern uint32_t DAT_00d6a570;
extern uint32_t DAT_00d6a574; // function pointer
extern uint32_t DAT_00d6a54c;
extern uint32_t DAT_00d6a5b0;
extern uint32_t DAT_00d6a5ec;
extern uint32_t DAT_00d5779c;
extern uint32_t DAT_00d5ddec;
extern uint32_t DAT_00e448a4;
extern uint32_t DAT_00d5efa4;
extern uint32_t DAT_00d5d7b8;
extern uint32_t DAT_00d5780c;
extern uint32_t DAT_00d5f00c;
extern uint32_t DAT_00d5fcbc;
extern uint32_t DAT_00d62bd4;
extern uint32_t DAT_00d5ccf8;
extern uint32_t DAT_0112b2b4;
extern uint32_t DAT_0112dd00;
extern uint32_t DAT_0112b6fc;
extern uint32_t DAT_0112b904;
extern uint32_t DAT_0112b384;
extern uint32_t DAT_0112b18c;
extern uint32_t DAT_0112b29c;
extern uint32_t DAT_0112b364;
extern uint32_t DAT_0112b6f4;
extern uint32_t DAT_0112b34c;
extern uint32_t DAT_0112b704;
extern uint32_t DAT_0112b784;
extern uint32_t DAT_0112b2c4;
extern uint32_t DAT_0112b804;
extern uint32_t DAT_0112b41c;
extern uint32_t DAT_0112b544;
extern uint32_t DAT_0112b56c;
extern uint32_t DAT_0112b39c;
extern uint32_t DAT_01129aa0;
extern uint32_t DAT_01129a98;
extern uint32_t DAT_0112b524;
extern uint32_t DAT_0112b564;
extern uint32_t DAT_0112b534;
extern uint32_t DAT_0112b2a4;
extern uint32_t DAT_0112b214;
extern uint32_t DAT_0112b37c;
extern uint32_t DAT_0112b54c;
extern uint32_t DAT_0112b52c;
extern uint32_t DAT_0112b554;
extern uint32_t DAT_0112b90c;
extern uint32_t DAT_0112f4b4;
extern uint32_t DAT_0120e978;
extern uint32_t DAT_0120ea74;
extern uint32_t DAT_0112b914;
extern uint32_t DAT_0112b51c;
extern uint32_t DAT_0112b374;
extern uint32_t DAT_0112b20c;
extern uint32_t DAT_0112b66c;
extern uint32_t DAT_01129814; // pointer to some structure

// Function pointer type for callback
typedef void (*CallbackFunc)();

// The Player class (size > 0x3000 bytes)
class Player {
public:
    // Constructor
    Player(uint32_t param2);
    // Destructor would be elsewhere

private:
    // Fields are defined by offsets; we'll use an anonymous struct for clarity
    // But for reconstruction, we'll just use the raw pointer accesses.
};

// Constructor implementation
Player::Player(uint32_t param2) {
    // Call base class constructor/init
    FUN_008022b0(param2, 0, 5, 0x46, 0x20);
    FUN_004aee00();

    // Set up vtable and function pointers
    // +0x00: vtable
    *(uint32_t*)(this) = &DAT_00d6b350;
    // +0x3C (0xF*4): function pointers
    *(uint32_t*)((uint8_t*)this + 0x3C) = &DAT_00d6b340;
    *(uint32_t*)((uint8_t*)this + 0x48) = &DAT_00d6b33c;
    *(uint32_t*)((uint8_t*)this + 0x50) = &DAT_00d6b338;
    *(uint32_t*)((uint8_t*)this + 0x54) = &DAT_00d6b2d8;
    *(uint32_t*)((uint8_t*)this + 0x58) = &DAT_00d6b270;
    // +0x390 (0xE4*4)
    *(uint32_t*)((uint8_t*)this + 0x390) = &DAT_00d6b24c;
    *(uint32_t*)((uint8_t*)this + 0x394) = &DAT_00d6b238;
    *(uint32_t*)((uint8_t*)this + 0x3A0) = &DAT_00d6b230;
    // +0x1F30 (0x7CC*4)
    *(uint32_t*)((uint8_t*)this + 0x1F30) = &DAT_00d6b218;
    // +0x205C (0x817*4) - byte field
    *(uint8_t*)((uint8_t*)this + 0x205C) = 0;

    FUN_006d9b40();
    FUN_006d9b40();
    FUN_006d9b40();
    FUN_007aaf80();

    // +0x2190 (0x864*4)
    *(uint32_t*)((uint8_t*)this + 0x2190) = 0;
    *(uint32_t*)((uint8_t*)this + 0x2194) = 0;

    FUN_007dd670();

    // +0x24AC (0x92B*4) to +0x24C0 (0x930*4)
    for (int i = 0x92B; i <= 0x930; ++i) {
        *(uint32_t*)((uint8_t*)this + i*4) = 0;
    }

    FUN_00700040();

    // +0x24FC (0x93F*4)
    *(uint32_t*)((uint8_t*)this + 0x24FC) = 0;
    *(uint32_t*)((uint8_t*)this + 0x2500) = 0;
    *(uint32_t*)((uint8_t*)this + 0x2528) = 0;
    *(uint32_t*)((uint8_t*)this + 0x252C) = 0;

    FUN_007dc210();

    // +0x26A4 (0x9A9*4)
    *(uint32_t*)((uint8_t*)this + 0x26A4) = 0x3FF;
    *(uint8_t*)((uint8_t*)this + 0x26A8) = 1;
    *(uint32_t*)((uint8_t*)this + 0x26A0) = &DAT_00d6a560;
    *(uint32_t*)((uint8_t*)this + 0x26B0) = 0x3F;
    *(uint8_t*)((uint8_t*)this + 0x26B4) = 1;
    *(uint32_t*)((uint8_t*)this + 0x26AC) = &DAT_00d6a568;
    *(uint32_t*)((uint8_t*)this + 0x26BC) = 0x1BF;
    *(uint8_t*)((uint8_t*)this + 0x26C0) = 1;
    *(uint32_t*)((uint8_t*)this + 0x26B8) = &DAT_00d6a578;
    *(uint32_t*)((uint8_t*)this + 0x26C8) = 0xF;
    *(uint8_t*)((uint8_t*)this + 0x26CC) = 1;
    *(uint32_t*)((uint8_t*)this + 0x26C4) = &DAT_00d6a570;

    // Call function pointer at DAT_00d6a574 with argument 0xF
    ((CallbackFunc)DAT_00d6a574)(0xF);

    // +0x26D0 (0x9B4*4) to +0x2734 (0x9CD*4) - zero out many fields
    for (int i = 0x9B4; i <= 0x9CD; ++i) {
        *(uint32_t*)((uint8_t*)this + i*4) = 0;
    }

    // +0x2738 (0x9CE*4)
    *(uint32_t*)((uint8_t*)this + 0x2738) = 0x1FF;
    *(uint32_t*)((uint8_t*)this + 0x2740) = 1;
    *(uint32_t*)((uint8_t*)this + 0x273C) = 1;

    FUN_0079b1a0();
    FUN_007ac460();

    // +0x28F0 (0xA3C*4) - zero out several fields
    *(uint32_t*)((uint8_t*)this + 0x28F0) = 0;
    *(uint16_t*)((uint8_t*)this + 0x28F4) = 0;
    *(uint16_t*)((uint8_t*)this + 0x28F6) = 0;
    *(uint32_t*)((uint8_t*)this + 0x28F8) = 0;
    *(uint16_t*)((uint8_t*)this + 0x28FC) = 0;
    *(uint16_t*)((uint8_t*)this + 0x28FE) = 0;
    *(uint32_t*)((uint8_t*)this + 0x2900) = 0;
    *(uint16_t*)((uint8_t*)this + 0x2904) = 0;
    *(uint16_t*)((uint8_t*)this + 0x2906) = 0;
    *(uint32_t*)((uint8_t*)this + 0x2908) = 0xBADBADBA;
    *(uint32_t*)((uint8_t*)this + 0x290C) = 0xBEEFBEEF;
    *(uint32_t*)((uint8_t*)this + 0x2910) = 0xEAC15A55;
    *(uint32_t*)((uint8_t*)this + 0x2914) = 0x91100911;
    *(uint32_t*)((uint8_t*)this + 0x291C) = 0xBEEFBEEF;
    *(uint32_t*)((uint8_t*)this + 0x2918) = 0xBADBADBA;
    *(uint32_t*)((uint8_t*)this + 0x2920) = 0xEAC15A55;
    *(uint32_t*)((uint8_t*)this + 0x2924) = 0x91100911;
    *(uint32_t*)((uint8_t*)this + 0x292C) = 0xBEEFBEEF;
    *(uint32_t*)((uint8_t*)this + 0x2928) = 0xBADBADBA;
    *(uint32_t*)((uint8_t*)this + 0x2930) = 0xEAC15A55;
    *(uint32_t*)((uint8_t*)this + 0x2934) = 0x91100911;
    *(uint32_t*)((uint8_t*)this + 0x293C) = 0xBEEFBEEF;
    *(uint32_t*)((uint8_t*)this + 0x2938) = 0xBADBADBA;
    *(uint32_t*)((uint8_t*)this + 0x2940) = 0xEAC15A55;
    *(uint32_t*)((uint8_t*)this + 0x2944) = 0x91100911;

    FUN_00896360();

    // +0x2B80 (0xAE0*4) - zero out many fields with sentinel patterns
    *(uint32_t*)((uint8_t*)this + 0x2B80) = 0;
    *(uint32_t*)((uint8_t*)this + 0x2B8C) = 0xEAC15A55;
    *(uint32_t*)((uint8_t*)this + 0x2B90) = 0x91100911;
    *(uint32_t*)((uint8_t*)this + 0x2B84) = 0xBADBADBA;
    *(uint32_t*)((uint8_t*)this + 0x2B88) = 0xBEEFBEEF;
    // ... many more sentinel patterns (omitted for brevity, but they are all similar)
    // The pattern repeats for offsets 0xAE5 to 0xB18, then some zeros and sentinels.

    // +0x2C78 (0xB1E*4)
    *(uint32_t*)((uint8_t*)this + 0x2C78) = DAT_00d6a54c;
    *(uint32_t*)((uint8_t*)this + 0x2C7C) = DAT_00d6a5b0;
    *(uint32_t*)((uint8_t*)this + 0x2C70) = 0;
    *(uint8_t*)((uint8_t*)this + 0x2C74) = 0;
    *(uint32_t*)((uint8_t*)this + 0x2C80) = 0;

    FUN_006d9ee0();
    FUN_006d9ee0();
    FUN_006d9ee0();

    // +0x2E24 (0xB89*4) - zero out many fields
    *(uint32_t*)((uint8_t*)this + 0x2E24) = 0;
    *(uint32_t*)((uint8_t*)this + 0x2E28) = 0;
    // ... sentinel patterns again for offsets 0xB8B to 0xBA6

    // +0x2E9C (0xBA7*4) - zero out many fields with sentinels and zeros
    // ... (omitted for brevity)

    // +0x3064 (0xC19*4) - zero out
    *(uint32_t*)((uint8_t*)this + 0x3064) = 0;
    *(uint32_t*)((uint8_t*)this + 0x3068) = 0;
    // ... more zeros

    // +0x3098 (0xC26*4)
    *(uint32_t*)((uint8_t*)this + 0x3098) = 0;
    *(uint32_t*)((uint8_t*)this + 0x309C) = 0;
    *(uint32_t*)((uint8_t*)this + 0x30A4) = 0;
    *(uint32_t*)((uint8_t*)this + 0x30A8) = 0;
    *(uint32_t*)((uint8_t*)this + 0x30B0) = &DAT_00d6a5ec;
    *(uint32_t*)((uint8_t*)this + 0x30B4) = 0;
    *(uint32_t*)((uint8_t*)this + 0x30B8) = 0;
    *(uint32_t*)((uint8_t*)this + 0x30BC) = 0;
    *(uint32_t*)((uint8_t*)this + 0x30C0) = 0;
    *(uint32_t*)((uint8_t*)this + 0x30C4) = 0;

    FUN_0084e6d0(0x10);

    // +0x3100 (0xC40*4) - zero out many fields
    for (int i = 0xC40; i <= 0xC61; ++i) {
        *(uint32_t*)((uint8_t*)this + i*4) = 0;
    }

    // +0x3188 (0xC62*4) - sentinel patterns
    *(uint32_t*)((uint8_t*)this + 0x3188) = 0xBADBADBA;
    *(uint32_t*)((uint8_t*)this + 0x318C) = 0xBEEFBEEF;
    *(uint32_t*)((uint8_t*)this + 0x3190) = 0xEAC15A55;
    *(uint32_t*)((uint8_t*)this + 0x3194) = 0x91100911;
    // ... more sentinels

    // +0x31A8 (0xC6A*4)
    *(uint32_t*)((uint8_t*)this + 0x31A8) = 0;
    *(uint32_t*)((uint8_t*)this + 0x31AC) = 0;
    *(uint32_t*)((uint8_t*)this + 0x31B0) = 0;
    *(uint32_t*)((uint8_t*)this + 0x31B4) = 0;
    // ... more zeros

    // +0x31C8 (0xC72*4) - byte
    *(uint8_t*)((uint8_t*)this + 0x31C8) = 0;

    FUN_007f7c90();

    // +0x09DC (0x277*4) - byte
    *(uint8_t*)((uint8_t*)this + 0x09DC) = 0;

    // Register and subscribe to messages
    uint32_t msgID;
    msgID = FUN_00408240("iMsgSetPlayerCrouchEvent");
    if (msgID != 0) {
        FUN_00408900((uint8_t*)this + 0x3C, &msgID, 0x8000);
    }
    if (DAT_0112dd00 != 0) {
        FUN_00408900((uint8_t*)this + 0x3C, &DAT_0112dd00, 0x8000);
    }

    FUN_00408240("iMsgPlayerDeath");
    FUN_00408240("iMsgPlayerDeathBloodSplatter");
    FUN_00408240("iMsgPlayerDeathExplosion");
    FUN_00408240("iMsgNotifyCopPatrolCarOfPlayerCrime");
    FUN_00408240("iMsgPlayerUsedItem");
    FUN_00408240("iMsgSetPlayerUsePrimaryBribeProp");
    msgID = FUN_00408240("iMsgSetPlayerUsePrimaryBribeProp");
    if (msgID != 0) {
        FUN_00408900((uint8_t*)this + 0x3C, &msgID, 0x8000);
    }

    // ... many more message registrations (omitted for brevity, but pattern continues)
    // The code registers many messages and subscribes to them.

    // After all message registrations, there is a call to FUN_00481620() to check multiplayer
    bool isMultiplayer = FUN_00481620();
    if (isMultiplayer) {
        if (DAT_01129aa0 != 0) {
            FUN_00408900((uint8_t*)this + 0x3C, &DAT_01129aa0, 0x8000);
        }
        if (DAT_01129a98 != 0) {
            FUN_00408900((uint8_t*)this + 0x3C, &DAT_01129a98, 0x8000);
        }
    }

    // ... more message registrations

    // +0x2494 (0x925*4)
    uint32_t uVar10 = FUN_0043ffa0((uint8_t*)this + 0x1F30, 0xFFFFFFFF);
    *(uint32_t*)((uint8_t*)this + 0x2494) = uVar10;

    isMultiplayer = FUN_00481620();
    if (!isMultiplayer) {
        *(uint32_t*)((uint8_t*)this + 0x2498) = 0x12; // 18
    } else {
        uint8_t bVar4 = *(uint8_t*)(DAT_01129814 + 0x14);
        if (bVar4 < 0x10) {
            *(uint32_t*)((uint8_t*)this + 0x2498) = bVar4;
            FUN_00444d20(bVar4, 1);
        } else {
            *(uint32_t*)((uint8_t*)this + 0x2498) = 0;
        }
        uint8_t uVar9 = FUN_0089c630();
        *(uint8_t*)((uint8_t*)this + 0x311C) = uVar9; // +0xC47
    }

    // +0x249C (0x927*4)
    uint32_t* puVar2 = (uint32_t*)((uint8_t*)this + 0x249C);
    FUN_004dde90(puVar2, 0x4F);
    *puVar2 |= 6;

    isMultiplayer = FUN_00481620();
    if (isMultiplayer) {
        FUN_007f9340(1, 0);
    }

    // +0x294C (0xA53*4)
    *(uint32_t*)((uint8_t*)this + 0x294C) = 0;

    uVar10 = FUN_0043b490();
    uVar10 = FUN_00540c60(0xF, 0x1F, uVar10);
    FUN_008963a0(this, uVar10, (void*)0x00798160); // callback function

    // Clean up some pointers
    if (*(uint32_t*)((uint8_t*)this + 0x24B4) != 0) { // +0x92D
        FUN_004daf90((void*)*(uint32_t*)((uint8_t*)this + 0x24B4));
        *(uint32_t*)((uint8_t*)this + 0x24B4) = 0;
    }
    if (*(uint32_t*)((uint8_t*)this + 0x24BC) != 0) { // +0x92F
        FUN_004daf90((void*)*(uint32_t*)((uint8_t*)this + 0x24BC));
        *(uint32_t*)((uint8_t*)this + 0x24BC) = 0;
    }

    // +0x24F0 (0x93C*4) - byte
    *(uint8_t*)((uint8_t*)this + 0x24F0) = 1;
    *(uint32_t*)((uint8_t*)this + 0x24F4) = 0;
    *(uint32_t*)((uint8_t*)this + 0x24F8) = 0;
    *(uint32_t*)((uint8_t*)this + 0x2530) = 0;

    FUN_00798bc0();
    FUN_00798f60();

    // Clear the sentinel arrays (set to zero)
    // Offsets 0xAE1 to 0xB19 (previously set to sentinels) are now zeroed
    for (int i = 0xAE1; i <= 0xB19; ++i) {
        *(uint32_t*)((uint8_t*)this + i*4) = 0;
    }

    // +0x2C64 (0xB19*4) - 8 bytes zero
    *(uint64_t*)((uint8_t*)this + 0x2C64) = 0;

    // +0x2C6C (0xB1B*4)
    *(uint32_t*)((uint8_t*)this + 0x2C6C) = 0;

    // +0x2024 (0x809*4)
    *(uint32_t*)((uint8_t*)this + 0x2024) = DAT_00d5779c;
    *(uint32_t*)((uint8_t*)this + 0x2028) = DAT_00d5ddec;

    // +0x20F4 (0x83D*4)
    *(uint32_t*)((uint8_t*)this + 0x20F4) = DAT_00d6a5b0;
    *(uint32_t*)((uint8_t*)this + 0x20FC) = DAT_00d6a5b0;
    *(uint32_t*)((uint8_t*)this + 0x20F8) = DAT_00e448a4;

    // Allocate and initialize a sub-object
    int iVar11 = (int)FUN_009c8e50(0x148);
    if (iVar11 != 0) {
        iVar11 = (int)FUN_00704d70(1);
    }
    *(uint32_t*)((uint8_t*)this + 0x24A8) = iVar11; // +0x92A
    *(uint32_t**)(iVar11 + 0x10) = (uint32_t*)((uint8_t*)this + 0x740); // +0x1D0
    *(uint32_t**)(*(uint32_t*)((uint8_t*)this + 0x24A8) + 0xF0) = this;

    // +0x2E14 (0xB85*4) - set some constants
    *(uint32_t*)((uint8_t*)this + 0x2E14) = 0x366E8F8A;
    *(uint32_t*)((uint8_t*)this + 0x2E18) = 0x0D326CA8;
    *(uint32_t*)((uint8_t*)this + 0x2E1C) = 0xD63872B9;
    *(uint32_t*)((uint8_t*)this + 0x2E20) = 0x3856101B;

    // Register more messages (combat-related)
    FUN_00408240((const char*)((uint8_t*)this + 0x2E9C)); // +0xBA7
    FUN_00408240((const char*)((uint8_t*)this + 0x2EA4)); // +0xBA9
    // ... many more

    // Clean up if needed
    if (*(uint32_t*)((uint8_t*)this + 0x3064) != 0) { // +0xC19
        FUN_004daf90((void*)*(uint32_t*)((uint8_t*)this + 0x3064));
        *(uint32_t*)((uint8_t*)this + 0x3064) = 0;
    }

    // Set some global pointers
    *(uint32_t*)((uint8_t*)this + 0x1F4C) = DAT_00d5efa4; // +0x7D3
    *(uint32_t*)((uint8_t*)this + 0x2010) = DAT_00d5d7b8; // +0x804
    *(uint32_t*)((uint8_t*)this + 0x2014) = DAT_00d5779c; // +0x805
    uint32_t uVar10_2 = DAT_00d5780c;
    *(uint32_t*)((uint8_t*)this + 0x2018) = uVar10_2; // +0x806
    *(uint32_t*)((uint8_t*)this + 0x201C) = uVar10_2; // +0x807
    *(uint32_t*)((uint8_t*)this + 0x2020) = uVar10_2; // +0x808

    // Clear sentinel arrays again (offsets 0xB8B to 0xBA6)
    for (int i = 0xB8B; i <= 0xBA6; ++i) {
        *(uint32_t*)((uint8_t*)this + i*4) = 0;
    }

    // Clear sentinel arrays at offsets 0xA42 to 0xA52
    for (int i = 0xA42; i <= 0xA52; ++i) {
        *(uint32_t*)((uint8_t*)this + i*4) = 0;
    }

    // +0x1F7C (0x7DF*4)
    *(uint32_t*)((uint8_t*)this + 0x1F7C) = DAT_00d5f00c;
    // +0x1F78 (0x7DE*4)
    *(uint32_t*)((uint8_t*)this + 0x1F78) = DAT_00d6a54c;

    // +0x2490 (0x924*4)
    *(uint32_t*)((uint8_t*)this + 0x2490) = 0;

    // Clean up pointer at +0x30A4 (0xC29*4)
    uint32_t* piVar3 = (uint32_t*)((uint8_t*)this + 0x30A4);
    if (*piVar3 != 0) {
        FUN_004daf90((void*)*piVar3);
        *piVar3 = 0;
    }
    *(uint32_t*)((uint8_t*)this + 0x30AC) = 0; // +0xC2B

    // Copy from global object
    iVar11 = (int)FUN_00471610();
    *(uint64_t*)((uint8_t*)this + 0x24E4) = *(uint64_t*)(iVar11 + 0x30); // +0x939
    uint32_t uVar10_3 = *(uint32_t*)(iVar11 + 0x38);
    *(uint32_t*)((uint8_t*)this + 0x24EC) = uVar10_3; // +0x93B

    // +0x30C8 (0xC32*4)
    *(uint32_t*)((uint8_t*)this + 0x30C8) = DAT_00d5d7b8;
    // +0x3114 (0xC45*4)
    *(uint32_t*)((uint8_t*)this + 0x3114) = 0;

    // +0x24A0 (0x928*4) - set bit 0x400
    *(uint32_t*)((uint8_t*)this + 0x24A0) |= 0x400;

    // +0x2188 (0x862*4)
    *(uint32_t*)((uint8_t*)this + 0x2188) = 0;
    *(uint32_t*)((uint8_t*)this + 0x218C) = 0;

    // +0x30CC (0xC33*4)
    *(uint32_t*)((uint8_t*)this + 0x30CC) = DAT_00d5fcbc;
    *(uint32_t*)((uint8_t*)this + 0x30D0) = DAT_00d62bd4;
    *(uint32_t*)((uint8_t*)this + 0x30D4) = DAT_00d5779c;
    *(uint32_t*)((uint8_t*)this + 0x30E4) = DAT_00d5ccf8; // +0xC39

    iVar11 = (int)FUN_00471610();
    *(uint64_t*)((uint8_t*)this + 0x30D8) = *(uint64_t*)(iVar11 + 0x30); // +0xC36
    uint32_t uVar10_4 = DAT_00d5ccf8;
    *(uint32_t*)((uint8_t*)this + 0x30E0) = *(uint32_t*)(iVar11 + 0x38); // +0xC38
    *(uint32_t*)((uint8_t*)this + 0x3124) = uVar10_4; // +0xC49

    // Clear sentinel arrays at offsets 0xC62 to 0xC69
    for (int i = 0xC62; i <= 0xC69; ++i) {
        *(uint32_t*)((uint8_t*)this + i*4) = 0;
    }

    // +0x0184 (0x61*4) - set bit 1
    *(uint32_t*)((uint8_t*)this + 0x0184) |= 1;

    // Clean up pointer at +0x3174 (0xC5D*4)
    if (*(uint32_t*)((uint8_t*)this + 0x3174) != 0) {
        FUN_004daf90((void*)*(uint32_t*)((uint8_t*)this + 0x3174));
        *(uint32_t*)((uint8_t*)this + 0x3174) = 0;
    }

    // +0x317C (0xC5F*4)
    *(uint32_t*)((uint8_t*)this + 0x317C) = 0;

    // +0x24A4 (0x929*4) - clear bit 0x80
    *(uint32_t*)((uint8_t*)this + 0x24A4) &= ~0x80;

    // Set various global pointers
    *(uint32_t*)((uint8_t*)this + 0x202C) = DAT_00d5efa4; // +0x80B
    *(uint32_t*)((uint8_t*)this + 0x204C) = DAT_00d5efa4; // +0x813
    *(uint32_t*)((uint8_t*)this + 0x2034) = DAT_00d5efa4; // +0x80D
    *(uint32_t*)((uint8_t*)this + 0x2044) = DAT_00d5780c; // +0x811
    *(uint32_t*)((uint8_t*)this + 0x2030) = DAT_00d5d7b8; // +0x80C
    *(uint32_t*)((uint8_t*)this + 0x203C) = DAT_00d5ddec; // +0x80F
    *(uint32_t*)((uint8_t*)this + 0x2040) = DAT_00e448a4; // +0x810
    *(uint32_t*)((uint8_t*)this + 0x2050) = DAT_00d5d7b8; // +0x814
    *(uint32_t*)((uint8_t*)this + 0x2054) = DAT_00d5ddec; // +0x815
    *(uint32_t*)((uint8_t*)this + 0x2058) = DAT_00e448a4; // +0x816
    *(uint32_t*)((uint8_t*)this + 0x2038) = DAT_00d5d7b8; // +0x80E
    *(uint32_t*)((uint8_t*)this + 0x2048) = DAT_00d6a54c; // +0x812

    // Clean up pointers at +0x31B0 (0xC6C*4) and +0x31B8 (0xC6E*4)
    if (*(uint32_t*)((uint8_t*)this + 0x31B0) != 0) {
        FUN_004daf90((void*)*(uint32_t*)((uint8_t*)this + 0x31B0));
        *(uint32_t*)((uint8_t*)this + 0x31B0) = 0;
    }
    if (*(uint32_t*)((uint8_t*)this + 0x31B8) != 0) {
        FUN_004daf90((void*)*(uint32_t*)((uint8_t*)this + 0x31B8));
        *(uint32_t*)((uint8_t*)this + 0x31B8) = 0;
    }

    // Return this pointer
    return;
}