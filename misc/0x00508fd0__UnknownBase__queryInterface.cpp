// FUNC_NAME: UnknownBase::queryInterface
// Function address: 0x00508fd0
// Role: Implements a query interface pattern returning this pointer for two recognized interface IDs (0x8EFAA286 and 0xFFD2E5B1). Returns 1 on success, 0 on failure.

class UnknownBase {
public:
    virtual int __thiscall queryInterface(unsigned int id, void** out);
};

int UnknownBase::queryInterface(unsigned int id, void** out) {
    if (id == 0x8EFAA286) {
        if (out != nullptr) {
            *out = this;
        }
        return 1;
    }
    
    if (out != nullptr) {
        *out = nullptr;
    }
    
    if (id != 0xFFD2E5B1) {
        return 0;
    }
    
    if (out != nullptr) {
        *out = this;
    }
    return 1;
}