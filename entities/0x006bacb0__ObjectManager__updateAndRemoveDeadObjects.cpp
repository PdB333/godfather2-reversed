// FUNC_NAME: ObjectManager::updateAndRemoveDeadObjects
// Address: 0x006bacb0
// This function iterates through an array of object pointers backwards,
// checks each object for removal (likely based on lifetime/state),
// removes dead objects by swapping with the last element, decrements count,
// and calls a virtual release method on removed objects.

// Structure offsets (relative to 'this', assuming 32-bit ints):
// +0xAC (0x2b*4): m_objectArray - pointer to array of object pointers
// +0xB0 (0x2c*4): m_objectCount - number of valid entries in array

class ObjectManager {
public:
    // Virtual function table offset +0x1c -> release/destroy method
    virtual void releaseObject(void* obj) = 0; // offset 0x1c in vtable

    void* m_objectArray;            // +0xAC
    int m_objectCount;              // +0xB0

    void updateAndRemoveDeadObjects();
};

// Forward declaration of the condition checker (FUN_006bdb50)
extern bool shouldRemoveObject(void* obj); // returns true if object should be removed

void __fastcall ObjectManager::updateAndRemoveDeadObjects() {
    int count = this->m_objectCount;
    void** array = (void**)this->m_objectArray;

    // Iterate backwards to safely remove while shifting
    for (int i = count - 1; i >= 0; i--) {
        void* obj = array[i];
        if (shouldRemoveObject(obj)) {
            // Move the last element to the current position if not already last
            if (i != count - 1) {
                array[i] = array[count - 1];
            }
            this->m_objectCount = count - 1;
            // Call virtual release (vtable + 0x1c) on the removed object
            this->releaseObject(obj);
        }
    }
}