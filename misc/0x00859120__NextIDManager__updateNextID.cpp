// FUNC_NAME: NextIDManager::updateNextID

class NextIDManager {
public:
    int m_nextID;          // +0x00: output ID
    int* m_pCounterA;      // +0x08: pointer to counter A
    int* m_pCounterB;      // +0x0C: pointer to counter B

    void updateNextID(void) {
        int leftVal = (m_pCounterB != nullptr) ? *m_pCounterB : -1;
        int rightVal = (m_pCounterA != nullptr) ? *m_pCounterA : -1;
        if (leftVal <= rightVal) {
            m_nextID = rightVal + 1;
        } else {
            m_nextID = leftVal + 1;
        }
    }
};