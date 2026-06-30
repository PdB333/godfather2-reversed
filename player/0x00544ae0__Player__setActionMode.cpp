//FUNC_NAME: Player::setActionMode
void __thiscall Player::setActionMode(int *this, int mode)
{
    int animationController;
    char canChange;

    // Virtual call to check if mode change is allowed (vtable+0x198)
    canChange = (**(code (__thiscall **)(int *))(*this + 0x198))(this);
    if ((canChange != '\0') && (*(int *)(this[0xd8] + 0x10c) != mode)) {
        // Get pointer to animation controller from mode manager (+0x18)
        animationController = *(int *)(this[0xd8] + 0x18);
        if (mode == 1) {
            // Set animation state to 6 (e.g., combat ready)
            if (*(short *)(animationController + 0x2a) != 6) {
                *(short *)(animationController + 0x2a) = 6;
            }
            // Call mode-specific setup (e.g., enter combat)
            FUN_0055d870();
            // Update current mode
            *(int *)(this[0xd8] + 0x10c) = 1;
            return;
        }
        // For any other mode, set animation state to 3 (e.g., idle)
        if (*(short *)(animationController + 0x2a) != 3) {
            *(short *)(animationController + 0x2a) = 3;
        }
        if (mode == 2) {
            // Call mode-specific setup (e.g., enter stealth)
            FUN_0055d810();
        }
        // Update current mode
        *(int *)(this[0xd8] + 0x10c) = mode;
    }
    return;
}