// FUNC_NAME: GodfatherGameManager::constructor

// Constructor for a class with multiple inheritance (4 vtable pointers).
// Calls base constructor (likely for a common base class) with the passed argument,
// then sets the primary vtable and three secondary vtable pointers at fixed offsets.
// Initializes several member fields to zero.
// Offset layout (relative to this):
// +0x00: primary vtable (most derived class)
// +0x3C: secondary vtable #1 (base class at offset 0x3C)
// +0x48: secondary vtable #2 (base class at offset 0x48)
// +0x50: secondary vtable #3 (base class at offset 0x50)
// +0x68: int zero (some flag)
// +0x6C: short zero (some member)
// +0x6E: short zero (some member)
// Total minimum object size: 0x70 bytes

void __thiscall GodfatherGameManager::constructor(void *this, int initParam)
{
    // Call base class constructor (likely a base with its own vtable)
    baseClassConstructor(initParam);   // calls FUN_00906680

    // Set primary vtable pointer
    *(void **)this = (void *)0x00d82768;

    // Set secondary vtable pointers (base class interfaces)
    *(void **)((char *)this + 0x3C) = (void *)0x00d82758; // offset 0x3C
    *(void **)((char *)this + 0x48) = (void *)0x00d82754; // offset 0x48
    *(void **)((char *)this + 0x50) = (void *)0x00d82750; // offset 0x50

    // Initialize integer member at offset 0x68 to 0
    *(int *)((char *)this + 0x68) = 0;

    // Initialize two short members at offset 0x6C and 0x6E to 0
    *(short *)((char *)this + 0x6C) = 0;
    *(short *)((char *)this + 0x6E) = 0;
}