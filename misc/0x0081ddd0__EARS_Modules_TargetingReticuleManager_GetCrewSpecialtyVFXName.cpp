// Xbox PDB: EARS_Modules_TargetingReticuleManager_GetCrewSpecialtyVFXName
// FUNC_NAME: getCSATriggerNameFromFlags
// Function address: 0x0081ddd0
// Converts a bitmask of CSA (Crew Special Ability) flags to the corresponding trigger string name.
// Returns nullptr if no flag is set.
// Bit flags:
//   0x04 - Demolition (csa_demo_trg)
//   0x08 - Arson (csa_arsn_trg)
//   0x10 - Safecracking (csa_safe_trg)
//   0x20 - Engineering (csa_eng_trg)
//   0x40 - Medical (csa_med_trg)
//   0x80 - Brute (csa_bru_trg)

char* getCSATriggerNameFromFlags(byte csaFlags)
{
    if ((csaFlags & 0x04) != 0) {
        return "csa_demo_trg";
    }
    if ((csaFlags & 0x08) != 0) {
        return "csa_arsn_trg";
    }
    if ((csaFlags & 0x10) != 0) {
        return "csa_safe_trg";
    }
    if ((csaFlags & 0x20) != 0) {
        return "csa_eng_trg";
    }
    if ((csaFlags & 0x40) != 0) {
        return "csa_med_trg";
    }
    if ((csaFlags & 0x80) != 0) { // Check bit 7 (sign bit)
        return "csa_bru_trg";
    }
    return nullptr;
}