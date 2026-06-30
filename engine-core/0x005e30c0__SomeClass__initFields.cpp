// FUNC_NAME: SomeClass::initFields
// Function address: 0x005e30c0
// Role: Initializes a set of object fields with default and global values. Called from multiple constructors.

extern int g_someGlobalValue1;  // DAT_00e2b1a4
extern int g_someGlobalValue2;  // DAT_00e2b04c
extern int g_someGlobalValue3;  // DAT_00e2b050

class SomeClass {
public:
    // Assuming this is a member function (__thiscall by ECX)
    void __fastcall initFields();
};

void __fastcall SomeClass::initFields(void) {
    // Offset 0x08: int flag, default 1
    *(int *)(this + 0x08) = 1;
    
    // Offset 0x0C: int x or first pair component
    *(int *)(this + 0x0C) = 0;
    
    // Offset 0x10: int y or second pair component
    *(int *)(this + 0x10) = 0;
    
    // Offset 0x14: byte flag or padding
    *(char *)(this + 0x14) = 0;
    
    // Offset 0x18: int second flag or similar
    *(int *)(this + 0x18) = 1;
    
    // Offset 0x1C: int zero
    *(int *)(this + 0x1C) = 0;
    
    // Offset 0x20: int zero
    *(int *)(this + 0x20) = 0;
    
    // Offset 0x24: byte zero
    *(char *)(this + 0x24) = 0;
    
    // Offset 0x28: byte zero
    *(char *)(this + 0x28) = 0;
    
    // Offset 0x29: byte zero
    *(char *)(this + 0x29) = 0;
    
    // Offset 0x2C: int from global variable (g_someGlobalValue1)
    *(int *)(this + 0x2C) = g_someGlobalValue1;
    
    // Offset 0x30: int from global variable (g_someGlobalValue2)
    *(int *)(this + 0x30) = g_someGlobalValue2;
    
    // Offset 0x34: int from global variable (g_someGlobalValue3)
    *(int *)(this + 0x34) = g_someGlobalValue3;
    
    // Offset 0x38: int zero
    *(int *)(this + 0x38) = 0;
    
    // Offset 0x3C: int zero
    *(int *)(this + 0x3C) = 0;
    
    // Offset 0x40: int zero
    *(int *)(this + 0x40) = 0;
    
    // Offset 0x44: int zero
    *(int *)(this + 0x44) = 0;
    
    // Call additional initialization routine
    FUN_005e3130();
    
    return;
}