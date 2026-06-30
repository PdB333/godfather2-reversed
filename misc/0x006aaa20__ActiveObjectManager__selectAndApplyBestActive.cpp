// FUNC_NAME: ActiveObjectManager::selectAndApplyBestActive

class ActiveObjectManager {
public:
    // +0x10: pointer to array of object pointers
    // +0x14: number of objects in array
    // Object layout:
    // +0x64: priority (uint)
    // +0x68: active flag (bool)

    uint m_objectCount;             // +0x14
    SObj** m_objects;               // +0x10

    struct SObj {
        uint m_priority;            // +0x64
        bool m_active;              // +0x68
    };

    void __thiscall selectAndApplyBestActive() {
        uint objectCount = m_objectCount;
        if (objectCount == 0) {
            return;
        }

        bool activeFound = false;
        uint bestIndex = 0xFFFFFFFF; // invalid index
        SObj* bestObj = nullptr;

        if (objectCount == 1) {
            // Single object: check if active
            SObj* obj = m_objects[0];
            if (obj->m_active) {
                activeFound = true;
                bestIndex = 0;
            }
        } else {
            // Multiple objects: find first active
            uint i = 0;
            for (; i < objectCount; i++) {
                if (m_objects[i]->m_active) {
                    bestIndex = i;
                    bestObj = m_objects[i];
                    i++; // start next iteration from i+1
                    break;
                }
            }

            // Scan remaining to find highest priority active
            for (; i < objectCount; i++) {
                SObj* current = m_objects[i];
                if (current->m_active) {
                    if (bestObj == nullptr || current->m_priority > bestObj->m_priority) {
                        bestObj = current;
                        bestIndex = i;
                    }
                }
            }

            if (bestObj != nullptr) {
                activeFound = true;
            }
        }

        if (activeFound) {
            applyBestActive(bestIndex); // FUN_006aa660
        }
    }

    void __thiscall applyBestActive(uint index); // defined elsewhere
};