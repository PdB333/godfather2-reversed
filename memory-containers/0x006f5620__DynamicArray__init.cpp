// FUNC_NAME: DynamicArray::init
class DynamicArray {
public:
    void* data;       // +0x00: pointer to allocated memory
    uint32_t capacity; // +0x04: number of elements allocated
    uint32_t size;     // +0x08: current number of elements (initially 0)
    uint32_t field_0C; // +0x0C: unknown (initially 0)
    uint32_t field_10; // +0x10: unknown (initially 0)
    uint8_t flags;     // +0x14: flags (e.g., owns memory, sorted, etc.)
};

DynamicArray* __thiscall DynamicArray::init(DynamicArray* this, uint32_t capacity, uint8_t flags) {
    this->flags = flags;
    this->capacity = capacity;
    this->data = nullptr;
    this->size = 0;
    this->field_0C = 0;
    this->field_10 = 0;
    // Allocate memory for capacity 32-bit elements and zero them
    this->data = operator new[](capacity * 4); // or custom allocator (FUN_009c8e80)
    memset(this->data, 0, capacity * 4);
    return this;
}