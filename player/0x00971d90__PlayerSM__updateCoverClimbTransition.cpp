// FUNC_NAME: PlayerSM::updateCoverClimbTransition

void __fastcall PlayerSM::updateCoverClimbTransition(void* this) {
    uint subState = *(uint*)((int)this + 0xDC);  // +0xDC: current sub-state (e.g., cover, climb)
    int lastAction = *(int*)((int)this + 0x588); // +0x588: last action type (5=vault, 6=climb, 7=cover)

    if (subState > 4) {
        if (subState < 8) {
            // Transitioning to cover/climb/vault states – process the sub-state
            FUN_009710e0(subState, 0);
        } else if (subState == 0xB) {
            // In a fall/landing sub-state; if the last action was a vault, climb, or cover, trigger a specific response
            if (lastAction == 7 || lastAction == 5 || lastAction == 6) {
                FUN_0096d810(1);
            }
        }
    }
}