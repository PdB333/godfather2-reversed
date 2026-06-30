// FUNC_NAME: StreamManager::createStream
void StreamManager::createStream(StreamManager *this) {
    // Initial vtable setup (base class)
    this->vtable = (void *)&LAB_00e42d64; // Base class vtable
    
    this->field_0x04 = 0;
    this->field_0x08 = 0;
    
    // Allocate buffer of size 1500 bytes (0x5DC)
    this->bufferSize = 1500; // +0x0C
    this->buffer = (uint8_t *)malloc(0x5DC); // +0x10
    
    // Set flag byte to 1 (likely open mode or valid flag)
    *(uint8_t *)((uintptr_t)this + 0x14) = 1; // +0x14
    
    // Switch to derived vtable after base init
    this->vtable = (void *)&LAB_00e43144; // Derived class vtable
    
    // Additional member initialization
    this->field_0x18 = 0; // +0x18
    this->field_0x1C = 0; // +0x1C
    this->field_0x20 = 0; // +0x20
    this->field_0x28 = 0; // +0x28 (note: offset 0x28 due to int array indexing)
    *((uint8_t *)this + 0x24) = 0; // byte at +0x24
    
    // Call subclass-specific initialization
    FUN_0064bc00(this);
    FUN_0065f1a0();
}