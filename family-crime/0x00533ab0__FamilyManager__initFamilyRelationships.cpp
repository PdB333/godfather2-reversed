// FUNC_NAME: FamilyManager::initFamilyRelationships
void __thiscall FamilyManager::initFamilyRelationships(void) {
    // Initialize family relationship matrix (6x6 = 36 floats)
    // +0x00: m_familyRelations[0][0] - (self) set to 0
    // +0x10: m_familyRelations[0][4] - default weight from global
    // +0x24: m_familyRelations[1][3]
    // +0x38: m_familyRelations[2][2]
    // +0x4C: m_familyRelations[3][1]
    // +0x50: m_familyRelations[3][2]
    // +0x64: m_familyRelations[4][1]
    // +0x78: m_familyRelations[5][0]
    // +0x8C: m_familyRelations[5][5] - (self) set to default weight
    float* relations = this->m_familyRelations;  // array of 36 floats, offset 0x00

    float defaultWeight = *DAT_00e2b1a4;  // global constant, likely 1.0f

    relations[0] = 0.0f;                  // [0][0]
    relations[4] = defaultWeight;         // [0][4]
    relations[5] = 0.0f;
    relations[6] = 0.0f;
    relations[7] = 0.0f;
    relations[8] = 0.0f;
    relations[9] = defaultWeight;         // [1][3]
    relations[10] = 0.0f;
    relations[11] = 0.0f;
    relations[12] = 0.0f;
    relations[13] = 0.0f;
    relations[14] = defaultWeight;        // [2][2]
    relations[15] = 0.0f;
    relations[16] = 0.0f;
    relations[17] = 0.0f;
    relations[18] = 0.0f;
    relations[19] = defaultWeight;        // [3][1]
    relations[20] = defaultWeight;        // [3][2]
    relations[21] = 0.0f;
    relations[22] = 0.0f;
    relations[23] = 0.0f;
    relations[24] = 0.0f;
    relations[25] = defaultWeight;        // [4][1]
    relations[26] = 0.0f;
    relations[27] = 0.0f;
    relations[28] = 0.0f;
    relations[29] = 0.0f;
    relations[30] = defaultWeight;        // [5][0]
    relations[31] = 0.0f;
    relations[32] = 0.0f;
    relations[33] = 0.0f;
    relations[34] = 0.0f;
    relations[35] = defaultWeight;        // [5][5]
}