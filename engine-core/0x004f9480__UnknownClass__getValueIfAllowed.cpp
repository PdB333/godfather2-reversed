// FUNC_NAME: UnknownClass::getValueIfAllowed
// Address: 0x004f9480
// Returns a value from an internal getter only if the flag is non-zero.

class UnknownClass {
public:
    uint32_t getValueIfAllowed(int32_t flag) {
        if (flag != 0) {
            return this->getInternalValue(); // Calls FUN_004f8e60
        }
        return 0;
    }

private:
    uint32_t getInternalValue(); // Defined at 0x004f8e60
};