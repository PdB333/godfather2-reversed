// FUNC_NAME: Player::Player
// Function address: 0x007c2570
// Constructor for Player class. Initializes base class, vtables, input/sound systems,
// and player-specific state flags.

#include <cstdint>

// Forward declarations for known types (from the game engine)
class Entity;
class PlayerState; // large structure containing player status flags (offset 0x24a0, 0x24a4, 0x2154)
class InputDeviceManager;
class ControllerManager;
class AudioSystem;
class GameManager;

// External functions (pointers to actual implementations)
extern void __thiscall EntityConstructor(Entity* entity, int arg1, int arg2); // FUN_007ab5e0
extern InputDeviceManager* __fastcall GetInputDeviceManager(); // FUN_007ab150
extern ControllerManager* __fastcall GetControllerManager(); // FUN_007ab130
extern AudioSystem* __fastcall GetAudioSystem(); // FUN_007ab140
extern void __cdecl SetMasterVolume(int volume); // FUN_0045f2a0 (0 = mute)
extern void __cdecl SetSystemFlag(int flag); // FUN_007f63e0 (0x31 = "allow something")
extern int __cdecl GetGlobalConfig(); // FUN_007ab360 (returns non-zero if some option enabled)
extern GameManager* __fastcall GetGameManager(); // FUN_00471610
extern char __thiscall CheckGameModeFlag(GameManager* gm, int offset); // FUN_007abbc0 (checks byte at gm+0x30)

// Player class definition (incomplete, only relevant members reconstructed)
class Player : public Entity
{
public:
    // Offset 0x1d (29): vtable pointer for interface (e.g., IPlayerInput)
    void** interfaceVTable; // +0x1d

    // Offset 0x1e (30): some pointer (likely for another interface)
    void* interfaceData; // +0x1e

    // Base vtable (from Entity) at offset 0
    // +0x00: Entity vtable

    // Byte at offset 0x7c (0x1f * 4) and plus 0x7d, 0x7e are flags
    uint8_t flags[3]; // +0x7c, +0x7d, +0x7e

    // Offset 0x22 (34): 4 bytes (maybe a handle or ID)
    int field_34; // +0x22

    // Offset 0x23 (35): 4 bytes
    int field_35; // +0x23

    // Offset 0x24 (36): 4 bytes
    int field_36; // +0x24

    // Offset 0x25 (37): 4 bytes
    int field_37; // +0x25

    // Offset 0x20 (32): pointer to some data (from InputDeviceManager)
    void* inputDeviceData; // +0x20

    // Offset 0x21 (33): pointer to some data (from ControllerManager)
    void* controllerData; // +0x21

    // Offset 0x16 (22): pointer to PlayerState (large structure far from this)
    PlayerState* playerState; // +0x16

    // Constructor
    Player* __thiscall Constructor(int someArg1, int someArg2);
};

// Constructor implementation
Player* __thiscall Player::Constructor(int someArg1, int someArg2)
{
    // Call base class (Entity) constructor with arguments
    EntityConstructor(this, someArg1, someArg2);

    // Set vtable pointers for multiple inheritance
    // Note: The order of assignments may indicate base class vtables.
    this->interfaceVTable = &PTR_FUN_00e32808; // Temporary interface vtable
    this->interfaceData = 0; // +0x1e = 0
    *(void**)this = &PTR_LAB_00d6e464; // Base vtable (Entity)
    this->interfaceVTable = &PTR_LAB_00d6e460; // Final interface vtable (overwrites previous)

    // Initialize flags at offset 0x7c-0x7e
    *(uint8_t*)&this->flags[0] = 0; // offset 0x1f (byte)
    *(uint8_t*)((int)this + 0x7d) = 0; // offset 0x7d
    *(uint8_t*)((int)this + 0x7e) = 0; // offset 0x7e

    // Clear 4-byte fields at offsets 0x22-0x25
    this->field_34 = 0;
    this->field_35 = 0;
    this->field_36 = 0;
    this->field_37 = 0;

    // Setup input device system
    InputDeviceManager* devMgr = GetInputDeviceManager();
    this->inputDeviceData = (void*)devMgr->some_data; // devMgr[1] (second word in object)
    devMgr->VTableCall1(1); // (**(code**)*devMgr)(1) - register something
    devMgr->VTableCall1(2); // (**(code**)*devMgr)(2)

    // Setup controller system
    ControllerManager* ctrlMgr = GetControllerManager();
    this->controllerData = (void*)(*(int*)((int)ctrlMgr + 4)); // ctrlMgr[1] (second word)
    ctrlMgr->VTableCall2(0x3f); // (**(code**)*ctrlMgr)(0x3f) - configure controller slot

    // Setup audio system
    AudioSystem* audSys = GetAudioSystem();
    audSys->VTableCall3(4); // (**(code**)*audSys)(4) - maybe set audio mode

    // Master volume mute
    SetMasterVolume(0); // mute all sound

    // Set player state flag at offset 0x24a0: bit 0x800 (some capability)
    *(uint32_t*)((int)this->playerState + 0x24a0) |= 0x800;

    // Set a system flag (0x31)
    SetSystemFlag(0x31);

    // Set player state field at 0x2154 to -1 (invalid)
    *(int*)((int)this->playerState + 0x2154) = -1;

    // Check if global config allows something
    if (GetGlobalConfig() != 0)
    {
        GameManager* gm = GetGameManager();
        char checkResult = CheckGameModeFlag(gm, 0x30); // check byte at gm+0x30
        if (checkResult != 0)
        {
            // Enable additional flag at offset 0x24a4
            *(uint32_t*)((int)this->playerState + 0x24a4) |= 0x400;
        }
    }

    return this;
}