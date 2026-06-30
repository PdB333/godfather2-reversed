// FUNC_NAME: GhostConnection::findFirstActiveGhost
// Address: 0x004e1020
// Searches the ghost array from the beginning for the first non-zero entry.
// Resets the internal index and result, then stores the found entry in m_currentGhost.
struct GhostArrayHeader {
    int* pArray;      // +0x00: pointer to array of ghost IDs/pointers
    int arraySize;    // +0x04: number of elements in the array
};

class GhostConnection {
public:
    void findFirstActiveGhost(); // __thiscall

private:
    GhostArrayHeader* m_pGhostHeader; // +0x00
    int m_currentIndex;               // +0x04
    int m_currentGhost;               // +0x08
};

void GhostConnection::findFirstActiveGhost() {
    GhostArrayHeader* header = m_pGhostHeader;
    m_currentIndex = 0;
    m_currentGhost = 0;

    if (header == nullptr) {
        return;
    }

    do {
        unsigned int index = m_currentIndex;
        if (header->arraySize <= index) {
            return;
        }
        int ghost = header->pArray[index];   // read ghost at current index
        m_currentGhost = ghost;
        m_currentIndex = index + 1;          // advance past this index
    } while (m_currentGhost == 0);           // skip empty slots
}