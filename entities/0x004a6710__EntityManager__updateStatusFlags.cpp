// FUNC_NAME: EntityManager::updateStatusFlags
// Function at 0x004a6710: Evaluates multiple object lists and sets combined status flags.
// Member function using __thiscall, 'this' in ESI.
// Offsets:
//   +0x5c: m_pEntities (array of pointers to entity objects)
//   +0x60: m_numEntities (count)
//   +0x68: m_pObjectives (array of objective structures, each 16 bytes? see loop step)
//   +0x6c: m_numObjectives
//   +0x74: m_pAnotherList (array of structures, each 8 bytes? step 4*2=8)
//   +0x78: m_numAnotherList
//   +0x82: m_flags (ushort, bit flags: 0x200, 0x100, 0x400)

void EntityManager::updateStatusFlags() {
    uint i;

    // Clear the flags that will be set below (bits 0x200, 0x100, 0x400? Actually only 0x200 cleared? 
    // The initial AND clears bits 0x0700? 0xf8ff clears bits 0x0700 (bits 8-10). 
    // So clear bits 0x100, 0x200, 0x400 (bits 8,9,10) fully.
    m_flags = m_flags & 0xf8ff;

    // First list: iterate over entity objects
    if (m_numEntities != 0) {
        for (i = 0; i < m_numEntities; i++) {
            // Get entity pointer from array
            int* entity = *(int**)(m_pEntities + i * 4);
            // Call virtual function at offset 0x18 (0x18/4 = 6th vtable entry)
            bool result = ((bool (*)(void*))(*entity)[6])(entity); // offset 0x18
            if (result) {
                m_flags |= 0x200;   // Set bit 9
                break;
            }
        }
    }

    // Second list: iterate over objectives (each entry seems 16 bytes? step +8 ushort = 16 bytes)
    if (m_numObjectives != 0) {
        ushort* pField = (ushort*)(m_pObjectives + 4); // start at offset 4 in first element
        for (i = 0; i < m_numObjectives; i++) {
            if ((*pField & 0x400) != 0) {
                m_flags |= 0x100;   // Set bit 8
                break;
            }
            pField += 8; // each objective structure is 16 bytes (8 ushorts)
        }
    }

    // Third list: iterate over another list (each entry seems 8 bytes? step +4 ushort = 8 bytes)
    if (m_numAnotherList != 0) {
        ushort* pField = (ushort*)(m_pAnotherList + 4); // start at offset 4
        for (i = 0; i < m_numAnotherList; i++) {
            if ((*pField & 0x400) != 0) {
                m_flags |= 0x400;   // Set bit 10
                break;
            }
            pField += 4; // each structure is 8 bytes (4 ushorts)
        }
    }
}