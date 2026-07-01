//FUNC_NAME: CrimeScene::initialize
void CrimeScene::initialize() {
    // Set default crime ID (hash for "invalid" or "none")
    this->m_crimeId = 0x637b907; // +0x44
    this->m_objectiveId = 0; // +0x48

    // Access global manager (e.g., CrimeManager or GameManager)
    int* pManager = *(int**)(gGlobalManager + 0x160); // +0x160: pointer to player or sim manager
    if (pManager != nullptr) {
        int crimeHash = *(int*)(pManager + 0x40); // +0x40: hash of current crime/objective
        int* pCrimeData = findObjectByHash(crimeHash); // lookup crime data object
        if (pCrimeData != nullptr && *(int*)(pCrimeData + 0x50) == 3) { // +0x50: type check (3 = kCrimeScene)
            this->m_crimeId = crimeHash; // overwrite with actual crime hash
            // Retrieve objective ID from nested manager
            int* pObjectiveManager = *(int**)(pManager + 0xfc); // +0xfc: pointer to objective manager
            if (pObjectiveManager != nullptr) {
                int* pObjective = *(int**)(pObjectiveManager + 0x14); // +0x14: pointer to current objective
                if (pObjective != nullptr) {
                    this->m_objectiveId = *(int*)(pObjective + 0x54); // +0x54: objective ID
                }
            }
        }
    }
}