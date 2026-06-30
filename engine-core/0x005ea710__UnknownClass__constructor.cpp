// FUNC_NAME: UnknownClass::constructor
// Function address: 0x005ea710
// Role: Constructor initializing an object. Calls base initializer, sets member at +0x130 to 0, then calls another init function with (0,1).

int __fastcall UnknownClass::constructor(int this) {
    FUN_00abd570();                // Base class constructor or global init
    *(int*)(this + 0x130) = 0;     // Member at offset 0x130 (e.g., flag/pointer) set to null
    FUN_00ab5fb0(0, 1);            // Additional initialization (e.g., pool or system setup)
    return this;                   // Return constructed object
}