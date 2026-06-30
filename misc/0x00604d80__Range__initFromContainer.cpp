// FUNC_NAME: Range::initFromContainer
// Function address: 0x00604d80
// Initializes a Range object from a container that has element count at offset 0x10 and array at offset 0x14 (each element 0xC bytes).
// The range stores begin and end pointers for iteration. The container pointer is duplicated in the first two fields.

class Range {
public:
    void __thiscall initFromContainer(void* container) {
        // +0x00: pointer to container (duplicated as +0x04)
        this->containerPtr = container;
        this->containerPtr2 = container;

        // +0x10: element count (int)
        int count = *reinterpret_cast<int*>(static_cast<uint8_t*>(container) + 0x10);

        // +0x14: start of element array (each element 0xC bytes)
        uint8_t* arrayStart = static_cast<uint8_t*>(container) + 0x14;

        this->beginPtr = arrayStart;
        this->endPtr = arrayStart + count * 0xC;
    }

private:
    void* containerPtr;   // +0x00
    void* containerPtr2;  // +0x04
    void* beginPtr;       // +0x08
    void* endPtr;         // +0x0C
};