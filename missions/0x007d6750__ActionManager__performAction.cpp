// FUNC_NAME: ActionManager::performAction
// Address: 0x007d6750
// Role: Handles player actions (item use, interaction) after validation
// Note: This reconstructs the decompiled function with meaningful names.

// External function declarations (assumed based on context)
// FUN_007ab140 -> getGameStateFlags() -> returns pointer to global state flags
// FUN_007ab160 -> getGameStateFlags() -> same, checks different bits
// FUN_00481660 -> isPrimaryButtonPressed()
// FUN_00481640 -> isSecondaryButtonPressed()
// FUN_00481620 -> isConfirmButtonPressed()
// FUN_007afe60 -> isPlayerInActionState(Player*)
// FUN_007d65e0 -> closeCurrentMenu()
// FUN_004a8ec0 -> updatePlayerContext(PlayerContext*)
// FUN_007a9180 -> debugOutput(const char*, const char*)
// FUN_00800c10 -> isMenuOrCutsceneActive()
// FUN_006901b0 -> playSoundEffect(int soundID)
// FUN_007ab690 -> getCurrentPlayer() -> returns Player*
// FUN_006c9440 -> findObjectByCRC(Object*, uint32 crc) -> returns Object*
// FUN_0079d7c0 -> resolveActionTarget(uint32 actionId) -> returns Object*
// FUN_007b9ac0 -> executeAction(Player* player, Object* target, uint32 actionId)
// FUN_007ab9a0 -> isActionAllowed(int, int) -> returns bool (global check)

// Known constants from context
const uint32 CRC_USE = 0x55859efa;          // Likely CRC32 for "use" action
const uint32 SOUND_ACTION_FAILED = 0x1d;     // Sound ID for failed action

// Class Player (partial, based on offsets used)
// Offsets:
// +0x58: pointer to PlayerContext (maybe another object)
// +0x8E6: byte flags (bit 0 = something)
// +0x2470: byte (e.g., isInInventory or hasItem)
// +0x2748: uint32 flags (bit 14 = 0x4000)
class Player {
public:
    PlayerContext* context; // +0x58
    char unknown_0x8E6;     // +0x8E6 (bit0 used)
    char inventoryFlag;     // +0x2470 (non-zero means something)
    uint32 actionFlags;     // +0x2748 (bit 0x4000 used)
    // ... other members ...
};

// Class ActionManager (this) - contains pointer to Player
class ActionManager {
public:
    Player* player; // +0x58
    // ... other members ...
};

// Main function
int ActionManager::performAction(uint32 actionId) {
    Player* player;
    void* globalState;
    char charCheck;
    int temp1;
    int temp2;
    uint32 stringAddr1;
    uint32 stringAddr2;

    // Check global state flags
    globalState = (void*)FUN_007ab140();  // likely returns pointer to some global state struct
    if (((*(byte*)((int)globalState + 4) & 0x20) == 0) ||
        (globalState = (void*)FUN_007ab160(), (*(byte*)((int)globalState + 4) & 2) == 0)) {
        return 0; // Game not in correct state (e.g., paused or cutscene)
    }

    // Get player object
    player = *(Player**)((int)this + 0x58);

    // Check player state flag at +0x8E6 bit 0
    if ((*(byte*)((int)player + 0x8E6) & 1) == 0) {
        // Flag NOT set - normal path
        // Check primary/secondary button states
        charCheck = FUN_00481660();
        if (charCheck != '\0') {
            // Primary button is pressed
            charCheck = FUN_00481640();
            if (charCheck != '\0') {
                // Both primary and secondary? Actually original decomp: if (cVar1 != '\0') ... intertwined.
                // Reconstruct logic carefully:
                // Original: 
                // if (*(char *)(iVar2 + 0x2470) != '\0') {
                //   cVar1 = FUN_00481660();
                //   if (cVar1 == '\0') { return 0; }
                //   uVar4 = 0x7d683b;
                //   cVar1 = FUN_007afe60(iVar2);
                //   if ((*(uint *)(iVar2 + 0x2748) & 0x4000) == 0) { return 0; }
                //   if (cVar1 == '\0') { return 0; }
                //   FUN_007d65e0(); FUN_004a8ec0(iVar2 + 0x58); FUN_007a9180(uVar4,uVar5); return 0;
                // }
                // else {
                //   cVar1 = FUN_00800c10();
                //   if (cVar1 == '\0') { FUN_006901b0(0x1d); }
                //   goto LAB_007d67a1;
                // }
            }
        }
        // Actually the decompiled code is complex, we need to follow exactly.
        // Let's rewrite based on the actual branching:

        // Original decomp:
        // if ((cVar1 != '\0') || (cVar1 = FUN_00481640(), cVar1 != '\0')) {
        //   if (*(char *)(iVar2 + 0x2470) != '\0') {
        //     ... (case with inventory flag set)
        //   } else {
        //     ... (case without inventory flag)
        //   }
        // } else {
        //   cVar1 = FUN_00481620();
        //   if (cVar1 == '\0') { return 0; }
        //   iVar3 = FUN_007ab690();
        //   if (iVar3 == 0) { return 0; }
        //   iVar3 = FUN_006c9440(iVar3,0x55859efa);
        //   if (iVar3 == 0) { return 0; }
        // }

        // So:
        charCheck = FUN_00481660();
        if ((charCheck != '\0') || (charCheck = FUN_00481640(), charCheck != '\0')) {
            // At least one of the two buttons is pressed
            if (*(char*)((int)player + 0x2470) != '\0') {
                // Player has item/ability (inventory flag non-zero)
                charCheck = FUN_00481660();
                if (charCheck == '\0') {
                    return 0;
                }
                stringAddr1 = 0x7d683b;
                charCheck = FUN_007afe60(player);
                if ((*(uint*)((int)player + 0x2748) & 0x4000) == 0) {
                    return 0; // Required flag not set
                }
                if (charCheck == '\0') {
                    return 0; // Player not in correct state
                }
                stringAddr2 = 0x7d6859;
                // Close menu, update player context, debug log
                FUN_007d65e0();
                FUN_004a8ec0((int)((int)player + 0x58));
                FUN_007a9180(stringAddr1, stringAddr2);
                return 0; // Action consumed, no further processing
            } else {
                // Inventory flag not set
                charCheck = FUN_00800c10();
                if (charCheck == '\0') {
                    FUN_006901b0(SOUND_ACTION_FAILED); // Play failure sound
                }
                goto LAB_007d67a1;
            }
        } else {
            // Neither primary nor secondary buttons pressed
            charCheck = FUN_00481620();
            if (charCheck == '\0') {
                return 0; // No confirm button either
            }
            temp1 = FUN_007ab690(); // Get current player object
            if (temp1 == 0) {
                return 0;
            }
            temp1 = FUN_006c9440(temp1, CRC_USE); // Find use target
            if (temp1 == 0) {
                return 0;
            }
            // Continue to main execution path
        }
    } else {
        // Flag at +0x8E6 bit 0 is set - alternative path
        temp1 = FUN_0079d7c0(actionId); // Convert actionId to target object
    }

    // Main execution: call executeAction
    charCheck = FUN_007b9ac0(player, temp1, actionId);
    if (charCheck == '\0') {
        return 0; // Action failed
    }

LAB_007d67a1:
    // Final global check
    charCheck = FUN_007ab9a0(0, 0);
    if (charCheck == '\0') {
        return 0;
    }

    return 1; // Action succeeded
}