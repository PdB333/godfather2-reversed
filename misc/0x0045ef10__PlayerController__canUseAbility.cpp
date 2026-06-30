// FUNC_NAME: PlayerController::canUseAbility
class PlayerController {
public:
    bool canUseAbility();
};

// Check if the player can use a specific ability/item
// offset 0x218: pointer to some ability state or item inventory slot (nullable)
bool PlayerController::canUseAbility() {
    // If the ability pointer is valid and the sub-function returns a valid index
    if (*(int*)(this + 0x218) != 0) {
        int result = someInternalCheck();  // FUN_00572780 - likely returns a slot index or handle
        if (result != -1) {
            return true;
        }
    }
    return false;
}