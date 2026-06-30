// FUNC_NAME: Player::Player

class Player {
public:
    // vtable pointer at +0x0
    void** vtable;
    
    // Function pointers at +0x3C (+0xF*4) and +0x48 (+0x12*4)
    void (*funcAtOff3C)();
    void (*funcAtOff48)();
    
    // Sub-object at +0x20 (32 bytes) - typically a String or embedded object
    // We'll call it SubObject for now
    class SubObject {
    public:
        SubObject(); // FUN_004086d0
        SubObject(); // FUN_00408310 (constructor overload or init)
    } subObject;

    // Constructor takes a flag indicating whether this is a dynamic allocation (bit 0)
    Player(byte isDynamic);
};

// Global initialization function called from constructor
void globalInitFunction(); // FUN_006bcd70

// Memory tracking function for dynamic allocations
void registerAllocation(void* ptr, uint size); // FUN_0043b960

Player::Player(byte isDynamic) {
    // Set vtable
    vtable = &PTR_FUN_00d5eaec; // vtable
            
    // Set additional function pointers
    funcAtOff3C = &PTR_LAB_00d5eadc; // +0x3C
    funcAtOff48 = &PTR_LAB_00d5ead8; // +0x48
    
    // Initialize sub-object at offset +0x20
    subObject.SubObject(); // calls FUN_004086d0 and FUN_00408310 via two steps? 
    // The decompiler shows two separate calls:
    // FUN_004086d0(this + 0x20) and FUN_00408310(this + 0x20)
    // So we simulate by having two constructor calls or one compound init.
    // Assuming SubObject has two initialization methods:
    subObject.initFirst();   // FUN_004086d0
    subObject.initSecond();  // FUN_00408310
    
    // Global initialization
    globalInitFunction(); // FUN_006bcd70
    
    // If this is a dynamic allocation, register with memory manager
    if (isDynamic & 1) {
        registerAllocation(this, 0x98); // size = 152 bytes
    }
}