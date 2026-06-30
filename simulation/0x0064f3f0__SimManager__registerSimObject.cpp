// FUNC_NAME: SimManager::registerSimObject
class SimManager {
public:
    // +0x1FC: pointer to array of SimObject* (dense array)
    SimObject** m_simObjectArray;
    // +0x204: number of used slots (next free slot index)
    int m_simObjectCount;
};

class SimObject {
public:
    // +0x2C: index in the SimManager's array
    int m_slotIndex;
};

void __thiscall SimManager::registerSimObject(SimManager* this, SimObject* obj) {
    int currentObjIndex = obj->m_slotIndex;
    if (currentObjIndex != this->m_simObjectCount) {
        // Swap the object at the current count position with the given object's current slot
        SimObject* lastObj = this->m_simObjectArray[this->m_simObjectCount];
        lastObj->m_slotIndex = currentObjIndex;
        this->m_simObjectArray[currentObjIndex] = this->m_simObjectArray[this->m_simObjectCount];
        this->m_simObjectArray[this->m_simObjectCount] = obj;
        obj->m_slotIndex = this->m_simObjectCount;
    }
    // Increment the count to include the newly placed object
    this->m_simObjectCount++;
}