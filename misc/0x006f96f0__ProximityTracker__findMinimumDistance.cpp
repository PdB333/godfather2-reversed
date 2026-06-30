// FUNC_NAME: ProximityTracker::findMinimumDistance
float ProximityTracker::findMinimumDistance(bool bCheckEnabled) {
    float fMinDist = DAT_00d5f6f0; // Default large distance (e.g., FLT_MAX)
    if (bCheckEnabled) {
        uint uIndex = 0;
        if (this->m_nCount != 0) {
            do {
                // Each entry in m_pEntries is an 8-byte struct; at offset 0 is a pointer to a member inside an object (at +0x48)
                int* pMemberPtr = *(int**)(this->m_pArray + uIndex * 8);
                if (pMemberPtr != nullptr) {
                    int* pObject = pMemberPtr - 0x48; // Get base object pointer
                    if (pObject != nullptr) {
                        float fDist = FUN_00470360(pObject); // Calculate distance to this object
                        if (fDist < fMinDist) {
                            fMinDist = fDist;
                        }
                    }
                }
                uIndex++;
            } while (uIndex < this->m_nCount);
        }
        return fMinDist;
    }
    return DAT_00d5f6f0;
}