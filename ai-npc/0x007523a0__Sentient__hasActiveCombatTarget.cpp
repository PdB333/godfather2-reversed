// FUNC_NAME: Sentient::hasActiveCombatTarget
bool __fastcall Sentient::hasActiveCombatTarget(void) {
    // this pointer in ECX
    // +0x58: pointer to CombatPerception component
    CombatPerception* perception = *(CombatPerception**)((char*)this + 0x58);
    if (!perception) return false;

    // +0x498: current combat target (Entity pointer or invalid sentinel 0x48)
    Entity* target = perception->currentTarget; // stored as a pointer
    if (target == nullptr || target == (Entity*)0x48) return false;

    // +0x116: activity flag (negative = active)
    if (*(char*)((char*)target + 0x116) >= 0) return false;

    return true;
}