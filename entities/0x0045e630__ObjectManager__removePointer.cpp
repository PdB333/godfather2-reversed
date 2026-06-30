// FUNC_NAME: ObjectManager::removePointer
// Address: 0x0045e630
// Role: Removes a pointer from an 8-slot array if the second parameter is zero and the pointer is found.

// +0x240: void* pointerArray[8]; // Array of 8 pointers

class ObjectManager {
public:
    void removePointer(void* pObj, int flag);
private:
    // +0x240
    void* pointerArray[8];
};

void ObjectManager::removePointer(void* pObj, int flag) {
    // Only proceed if pointer is non-null and flag is zero (likely a safety check)
    if (pObj != nullptr && flag == 0) {
        for (int i = 0; i < 8; i++) {
            if (pointerArray[i] == pObj) {
                pointerArray[i] = nullptr;
                return;
            }
        }
    }
}