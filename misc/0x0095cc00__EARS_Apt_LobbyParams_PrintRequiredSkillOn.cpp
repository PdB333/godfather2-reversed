// Xbox PDB: EARS_Apt_LobbyParams_PrintRequiredSkillOn
// FUNC_NAME: CrewSpecialty::getLocalizedDescription
// Function at 0x0095cc00
// Retrieves the localized description string for a crew specialty based on the index stored at +0x08.
// Uses a global table of specialty hashes (g_specialtyTable) and count (g_specialtyCount).
// Hashes: 0x3d26cff9 = "safe_cracker", 0x45c2f636 = "demolition", 0x7116917a = "arsonist"

#include <cstdint>

// Forward declarations of external functions
extern const char* getLocalizedString(const char* key); // FUN_004d3d90
extern void stringCopy(char* dest, const char* src, int maxLen); // FUN_005c4660

// Global data (from binary)
extern uint32_t g_specialtyCount; // DAT_011307fc
extern uint32_t* g_specialtyTable; // DAT_011307f8 - array of 8-byte entries, first 4 bytes are hash
extern const char* g_defaultSpecialtyString; // DAT_0120546e, fallback if no specialty

// Hash constants for recognized specialties
const uint32_t HASH_SAFE_CRACKER = 0x3d26cff9;
const uint32_t HASH_DEMOLITION   = 0x45c2f636;
const uint32_t HASH_ARSONIST     = 0x7116917a;

// This class might be CrewSpecialty or similar
class CrewSpecialty {
public:
    // +0x08: uint32_t m_specialtyIndex; // Index into the global specialty table
    // Other fields not used here

    void __thiscall getLocalizedDescription(char* outBuffer) const {
        // Clear output buffer? The first instruction sets *param_2 = 0, but that's just a null terminator? Actually it's *outBuffer = 0; we'll keep as is.
        *outBuffer = '\0';

        const char* localizedStr = nullptr;
        // Default fallback string (null pointer)
        const char* fallbackStr = nullptr; // puVar3, initially 0

        // Check if the index is within valid range
        if (*(uint32_t*)((uintptr_t)this + 0x08) < g_specialtyCount) {
            uint32_t index = *(uint32_t*)((uintptr_t)this + 0x08);
            uint32_t hash = *(uint32_t*)(g_specialtyTable + index * 2); // each entry is 8 bytes, hash at offset 0

            const char* key;
            if (hash == HASH_SAFE_CRACKER) {
                key = "$crew_specialty_safe_cracker";
            } else if (hash == HASH_DEMOLITION) {
                key = "$crew_specialty_demolition";
            } else if (hash == HASH_ARSONIST) {
                key = "$crew_specialty_arsonist";
            } else {
                key = "$mp_required_skills_none";
            }

            // Get localized string for the key
            const char* localized = getLocalizedString(key);
            fallbackStr = nullptr; // puVar4 was set to puVar3 (which was 0)
            // If localized is not null, use it; otherwise will fall through to default
            if (localized != nullptr) {
                localizedStr = localized;
                // Note: in original, fallbackStr was set to puVar3 (which was 0) before the check, so it remains 0
            } else {
                // Fallback to global default string
                localizedStr = g_defaultSpecialtyString;
            }
        } else {
            // Index out of range, use default string
            localizedStr = g_defaultSpecialtyString;
        }

        // Copy the localized string to the output buffer (max 0x80 bytes)
        stringCopy(outBuffer, localizedStr, 0x80);

        // The original code had a suspicious call to a null function pointer:
        // (*(code*)0x0)(puVar4, puVar4, uVar5, uVar6);
        // Since puVar4 is always 0, this is dead code. Likely a decompilation artifact.
        // We omit it.
    }
};