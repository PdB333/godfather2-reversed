// FUNC_NAME: PlayerStateMachine::handleCommand

#include <cstdint>

// Forward declarations for known helper functions
void setFlag_0x9c();                                      // FUN_00773360 - enables some state flag
void playAnimation(int animId);                           // FUN_007f63b0 - plays NPC/player animation
void updateAudioSystem();                                // FUN_007f6460 - updates audio context
void switchCameraMode();                                 // FUN_00800670 - changes camera behavior
void* getPlayerEntity();                                 // FUN_00772f10 - returns player object pointer
void playSoundEffect(int soundId);                       // FUN_007f6420 - plays a sound
void startTransitionToState();                           // FUN_00773560 - state transition entry
void resetStateMachine();                                // FUN_007729f0 - resets internal state
int  baseCommandHandler(int a2, int a3, int a4, int cmd, int a6); // FUN_0073e610 - base class handler
uint32_t getStateFlags(uint32_t stateId);                // FUN_0084d420 - returns flag bitmask for state

// Object offsets (from Ghidra analysis of EARS player structures)
// +0x9c   : bitfield for player flags
// +0xa0   : pointer to an auxiliary data block
// +0xb8   : vtable of the current state object
// +0x1d0  : player-specific flags (bit 0 = performing action)
// +0x1f5c : auxiliary flag field (bit 8 = require camera lock)

class PlayerStateMachine {
public:
    // Handles a command/message identified by 'cmd' (base 0x23)
    // Returns 1 if handled, otherwise returns the result of base class handler.
    int handleCommand(int param2, int param3, int param4, int cmd, int param6)
    {
        switch (cmd - 0x23) {
        case 0: // Command 0x23 - enable action flag
            setFlag_0x9c();
            *(uint32_t*)(this + 0x9c) |= 0x8;   // set bit 3
            return 1;

        case 1: // Command 0x24 - start primary action sequence
            playAnimation(1);
            updateAudioSystem();
            switchCameraMode();

            // Check if player is performing something and clear the flag
            if (void* player = getPlayerEntity()) {
                if (*(uint8_t*)(player + 0x1d0) & 0x1) {
                    *(uint32_t*)(player + 0x1d0) &= ~0x1; // clear bit 0
                }
            }

            // Enable a work byte in the auxiliary block
            *(uint8_t*)(*(int*)(this + 0xa0) + 0xa20) = 1;
            return 1;

        case 2: // Command 0x25 - ignore (no action)
        case 5: // Command 0x28 - ignore
            return 1;

        case 3: // Command 0x26 - disable work byte
            *(uint8_t*)(*(int*)(this + 0xa0) + 0xa20) = 0;
            return 1;

        case 4: // Command 0x27 - play sound
            playSoundEffect(0x30);
            switchCameraMode();
            return 1;

        case 6: // Command 0x29 - start transition
            startTransitionToState();
            return 1;

        case 7: // Command 0x2a - fall through to post‑switch code
            break;

        case 8: // Command 0x2b - reset
            resetStateMachine();
            return 1;

        default: // Any other command - delegate to base handler
            return baseCommandHandler(param2, param3, param4, cmd, param6);
        }

        // --- Case 7 handling (continues after switch) ---
        // Query current state via vtable at +0xb8 (offset 0x34)
        void** vtable = *(void***)(this + 0xb8);
        int (*getCurrentState)() = (int(*)())(vtable[0x34 / 4]); // pointer at vtable+0x34
        int stateId = getCurrentState();

        if (stateId != 4) {
            stateId = getCurrentState(); // (same call, possibly a different state after first?)
            uint32_t stateFlags = getStateFlags((uint32_t)stateId);
            if ((stateFlags & 0x8) == 0) {
                return 1; // do not proceed if flag 8 not set
            }
        }

        // Set bit 8 in the auxiliary flag field at +0x1f5c
        uint32_t* auxFlag = (uint32_t*)(*(int*)(this + 0xa0) + 0x1f5c);
        *auxFlag |= 0x100;
        return 1;
    }
};