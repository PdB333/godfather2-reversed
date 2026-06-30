// FUNC_NAME: ObjectManager::removeDeadObjects
void __thiscall ObjectManager::removeDeadObjects() {
    // m_objectArray at +0xAC, m_objectCount at +0xB0
    int count = this->m_objectCount;
    int i = count;
    while (i > 0) {
        i--;
        void* obj = this->m_objectArray[i];
        // Check if the object should be removed (e.g., dead, expired)
        if (isObjectDead(obj)) {
            // If not the last element, swap with the last
            if (i != this->m_objectCount - 1) {
                this->m_objectArray[i] = this->m_objectArray[this->m_objectCount - 1];
            }
            this->m_objectCount--;
            // Call virtual release/destructor at vtable+0x1c
            (*(void (__thiscall**)(void*))(*(int*)obj + 0x1c))(obj);
        }
    }
}