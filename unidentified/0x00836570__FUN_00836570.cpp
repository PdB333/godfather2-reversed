// FUNC_NAME: SomeClass::Constructor
// Function: 0x00836570 - Constructor that initializes a float field (offset +0x4c) 
//            as the sum of two other objects' float fields at same offset.
//            Sets vtable pointer, calls base init, then sums.

extern void baseObjectInit(); // FUN_008334a0 - likely base class initialization
extern float g_defaultFloat;  // _DAT_00d5780c - default value for the field
extern void* g_vtable_SomeClass; // PTR_LAB_00d73738

class SomeClass {
public:
    void* vtable;          // +0x00
    // ... other members ...
    float m_combinedValue; // +0x4c

    void* __thiscall Constructor(void* objA, void* objB);
};

void* __thiscall SomeClass::Constructor(void* objA, void* objB) {
    // Call base class/component initializer
    baseObjectInit();

    // Set vtable pointer
    this->vtable = g_vtable_SomeClass;

    // Initialize field with global default (overwritten below)
    this->m_combinedValue = g_defaultFloat;

    // Sum the float fields from two source objects at the same offset (+0x4c)
    // This effectively combines two values (e.g., scores, distances, timers)
    this->m_combinedValue = *(float*)((char*)objA + 0x4c) + *(float*)((char*)objB + 0x4c);

    return this;
}