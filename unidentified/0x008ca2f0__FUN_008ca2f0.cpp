// FUNC_NAME: SomeManager::~SomeManager
// Address: 0x008ca2f0
// Role: Destructor for a manager class (likely singleton). Sets vtable to base, calls base destructor, releases member at +0x04, then sets vtable to another base and clears global singleton flag.

class SomeManager {
public:
    void* vtable;          // +0x00
    void* memberPtr;       // +0x04 (some dynamically allocated object)
    // ... other members
};

// Forward declarations of called functions (base destructor and member release)
void __fastcall FUN_008ca0d0(void* this);   // base class destructor
void __fastcall FUN_009c8f10(void* ptr);    // release/destructor for member object

// Global singleton flag
extern int DAT_01129990;

void __fastcall SomeManager::~SomeManager() {
    // Set vtable to immediate base class (so virtual calls during base destructor are correct)
    this->vtable = &PTR_FUN_00d7bf40;
    
    // Call base class destructor
    FUN_008ca0d0(this);
    
    // Release member at offset +0x04 if non-null
    if (this->memberPtr != nullptr) {
        FUN_009c8f10(this->memberPtr);
    }
    
    // Set vtable to most base class (or a sentinel vtable) to avoid dangling pointer
    this->vtable = &PTR_LAB_00d7bf3c;
    
    // Clear singleton flag
    DAT_01129990 = 0;
}