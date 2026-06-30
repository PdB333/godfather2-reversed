// FUNC_NAME: SimpleHolder::setValue
// Function address: 0x004b8010
// This function assigns the first dword of the object (at offset 0) to the given value.
class SimpleHolder {
public:
    uint32_t value; // +0x00

    void setValue(uint32_t newValue) {
        value = newValue;
    }
};