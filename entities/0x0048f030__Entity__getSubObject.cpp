// FUNC_NAME: Entity::getSubObject

// Allocate size 0x5c for sub-object at offset +0x98 (m_pSubObject)
void* allocateMemory(int size); // FUN_009c8e50

// Initialize sub-object at given memory, returns pointer to it (likely constructor)
void* constructSubObject(void* memory); // FUN_00617e10

// Class Entity assumed with member m_pSubObject at offset +0x98
class Entity {
public:
    // Lazy initialization of sub-object
    void* getSubObject() {
        // Check if sub-object already exists (offset +0x98)
        if (m_pSubObject == nullptr) {
            // Allocate memory for sub-object (size 0x5c)
            void* allocatedMem = allocateMemory(0x5c);
            if (allocatedMem != nullptr) {
                // Construct the sub-object in the allocated memory
                m_pSubObject = constructSubObject(allocatedMem);
            } else {
                m_pSubObject = nullptr;
            }
        }
        return m_pSubObject;
    }

private:
    void* m_pSubObject; // +0x98
};