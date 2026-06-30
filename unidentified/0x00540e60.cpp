// FUNC_ADDR: 0x00540e60 - Likely a conditional flag setter for an object (e.g., FamilyManager, CrimeScene)
// Uses ESI as 'this' pointer (custom convention), EAX/EDI as two void* parameters.
void __thiscall SomeObject::checkAndSetConditionFlags(void* ptrA, void* ptrB) {
    // ptrA: first object pointer (in EAX)
    // ptrB: second object pointer (in EDI)

    if (ptrA != nullptr && ptrB != nullptr) {
        // Precondition action (e.g., resetting state or incrementing counter)
        this->performPreAction(); // FUN_005413f0

        // Evaluate combined condition from two internal flags/subsystems
        uint64_t combinedStatus = this->computeCombinedStatus(); // FUN_00541430

        // Set a boolean member at offset 0x00: true only if lower and upper halves share at least one set bit
        // (common pattern for checking intersection of two flag sets)
        this->m_bConditionMet = ((uint32_t)combinedStatus & (uint32_t)(combinedStatus >> 32)) != 0;
    }
    else {
        // If either pointer is null, default to true (e.g., skip condition)
        this->m_bConditionMet = true;
    }
}