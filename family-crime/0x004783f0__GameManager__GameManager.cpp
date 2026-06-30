// FUNC_NAME: GameManager::GameManager
void __thiscall GameManager::GameManager(uint *this, int param_2) // param_2 passed to base constructor
{
    // Set vtable pointer (base class vtable)
    this[0] = (uint)&PTR_LAB_00e32fd4; // vtable for base class
    
    // Store this manager globally
    g_pGameManager = this; // DAT_012233ac
    
    // Call base class constructor (likely some core system)
    FUN_0046c590(param_2);
    
    // Set up various vtable pointers (multiple inheritance or interface)
    uint uVar1 = DAT_00e44628;   // Some global pointer/constant
    this[0x15] = (uint)&PTR_LAB_00e32854; // vtable for interface A
    this[0x1a] = uVar1;              // Set offset 0x1a to global value
    uVar1 = DAT_00e2fc48;            // Another global pointer
    this[1] = (uint)&PTR_LAB_00e32fa0;   // vtable for another interface
    this[0] = (uint)&PTR_FUN_00e32f9c;   // Override base vtable with derived vtable
    this[0x10] = (uint)&PTR_LAB_00e32fbc; // vtable for interface B
    this[0x13] = (uint)&PTR_LAB_00e32fcc; // vtable for interface C
    this[0x15] = (uint)&PTR_LAB_00e32fd0; // Override interface A vtable
    this[0x16] = 0x32;              // Offsets: +0x58 => some capacity (50)
    this[0x17] = 0;                 // Counter 1
    this[0x18] = 0;                 // Counter 2
    this[0x1b] = uVar1;             // Set offset 0x1b from previous global
    
    // Initialize two subsystems (sound channels, controllers, etc.)
    for (int i = 0; i < 2; i++) {
        FUN_004782b0(); // Subsystem initialization
    }
    
    // Set default values for some fields
    *(byte *)(this + 0x5b) = 0;     // +0x16c => flag1
    this[0x5c] = 0;                 // +0x170 => some value
    this[0x5d] = 0;                 // +0x174 => another value
    
    // Update global linked list (memory manager or object list)
    int *listPtr = (int *)(DAT_01206880 + 0x14); // Global offset +0x14
    **(uint **)(DAT_01206880 + 0x14) = (uint)&PTR_LAB_0110bb34; // Write new node pointer
    *listPtr = *listPtr + 4;        // Advance list pointer
    
    // Additional fields initialization
    *(byte *)(this + 0x19) = 0;     // +0x64 => byte
    *(byte *)((int)this + 0x65) = 0; // +0x65 => byte
    *(byte *)((int)this + 0x66) = 0; // +0x66 => byte
    *(byte *)((int)this + 0x67) = 0xff; // +0x67 => max value (255)
    
    // Copy global singleton pointers into this manager
    if (DAT_012069c4 != 0) {
        FUN_00407e60(this + 0x10, &DAT_012069c4); // Copy pointer to offset 0x40
    }
    if (DAT_01206980 != 0) {
        FUN_00407e60(this + 0x10, &DAT_01206980); // Copy pointer to same offset? Might be assignment
    }
    
    // Final initialization step
    FUN_00479010();
}