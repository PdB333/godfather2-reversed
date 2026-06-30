// FUNC_NAME: FamilyManager::GetFamilyData
// Address: 0x005e2180
// Searches an array of 5 FamilyData structures (each 0x4a4 bytes) located at this+0x490.
// If the passed family ID (in EAX) matches any entry's ID (at +0x00 of each struct),
// copies 108 bytes (27 ints) from offset +0x214 of that entry (ID +4 +0x210) into the output buffer.
// Returns 1 on success, 0 if ID is zero or not found.

struct FamilyData {
    int m_id;                                         // +0x00
    char _pad0[0x210];                                // +0x04 to +0x213
    int m_statBlock[27];                              // +0x214 size 0x6C (108 bytes)
    // rest of struct up to 0x4A4
};

class FamilyManager {
public:
    static const int kMaxFamilies = 5;
    FamilyData m_families[kMaxFamilies];              // +0x490

    __thiscall int GetFamilyData(int familyId, int* outData) {
        if (familyId == 0) {
            return 0;
        }
        for (int i = 0; i < kMaxFamilies; i++) {
            if (m_families[i].m_id == familyId) {
                // Copy 108 bytes from m_statBlock (offset +0x214 within the found element)
                const int* src = m_families[i].m_statBlock;
                for (int j = 0; j < 27; j++) {
                    outData[j] = src[j];
                }
                return 1;
            }
        }
        return 0;
    }
};