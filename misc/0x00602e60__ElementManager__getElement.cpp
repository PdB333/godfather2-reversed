// FUNC_NAME: ElementManager::getElement
class ElementManager {
public:
    struct DataTable {
        uint32_t count;  // +0xa4 from table pointer
        uint8_t* base;   // +0xac from table pointer
    };
    void* getElement(uint32_t index) const;
private:
    uint32_t defaultIndex; // +0x3c
    DataTable* table;      // +0x20 (pointer to DataTable)
    // ... other members
};

void* ElementManager::getElement(uint32_t index) const {
    if (index == 0xFFFFFFFF) {
        index = this->defaultIndex; // use default index from object
    }

    DataTable* dt = this->table;
    if (index < dt->count) {
        // Each element is 0x61 (97) bytes in size
        return dt->base + (index * 0x61);
    }
    // Return a static default element (DAT_01222260)
    return &DAT_01222260;
}