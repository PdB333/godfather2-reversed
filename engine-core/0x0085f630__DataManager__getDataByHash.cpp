// FUNC_NAME: DataManager::getDataByHash
// Function address: 0x0085f630
// Retrieves a pointer to data associated with this object's ID and a hash.
// Returns a pointer or 0 on failure.
class DataManager {
public:
    unsigned short m_id; // +0x12: ID of this object
    // ... other fields

    void* getDataByHash() {
        const unsigned int kDataHash = 0x998cab76;
        int outParam = 0;
        void* resultPtr = nullptr;
        char success = FUN_005fd340(m_id, kDataHash, &outParam, &resultPtr);
        if (success && resultPtr != nullptr && outParam != 0 &&
            *(char*)(outParam + 6) == 0x02) { // type byte at offset 6
            return *(void**)resultPtr; // dereference to get actual pointer
        }
        return nullptr;
    }
};