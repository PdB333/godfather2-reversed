// FUNC_NAME: ArrayContainer::constructWithCount
ArrayContainer* __thiscall ArrayContainer::constructWithCount(ArrayContainer* this, uint32_t count) {
    uint32_t totalLow;
    uint32_t totalHigh;
    uint32_t size;
    uint32_t* header;
    void* elements;
    
    // Calculate total size = count * sizeof(element) (0x34 = 52 bytes) with overflow detection
    uint64_t mulResult = (uint64_t)count * 0x34;
    totalLow = (uint32_t)mulResult;
    totalHigh = (uint32_t)(mulResult >> 32);
    if (totalHigh != 0) {
        size = 0xFFFFFFFF; // Overflow indicator
    } else {
        size = totalLow;
    }
    
    // Add 4 bytes for header count, check for overflow
    uint32_t allocSize = size + 4;
    if (size > 0xFFFFFFFB) {
        allocSize = 0xFFFFFFFF; // Overflow
    }
    
    header = (uint32_t*)FUN_009c8e80(allocSize); // Memory allocation (likely malloc)
    if (header == nullptr) {
        return nullptr;
    }
    
    *header = count; // Store element count in header
    elements = (void*)(header + 1); // Elements start right after header
    
    // Construct each element using the fixed-size constructor (0x34 bytes each)
    // Compiler intrinsic equivalent to: for(i=0; i<count; i++) constructElement((uint8_t*)elements + i*0x34);
    _vector_constructor_iterator_(elements, 0x34, count, &LAB_0090eff0);
    
    // Fill container structure:
    // +0x00: pointer to first element (after header)
    // +0x04: element count
    // +0x08: capacity (set to 0, maybe unused or set later)
    // +0x0C: flags (set to 0)
    this->data = elements;
    this->count = count;
    this->capacity = 0;
    this->flags = 0;
    
    return this;
}