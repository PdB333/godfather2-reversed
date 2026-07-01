// FUNC_NAME: FamilyManager::constructor
// Address: 0x00897de0
// Constructs the FamilyManager singleton, initializes 6 Family objects (0x18 bytes each),
// sets vtable pointers for base and derived classes, and clears the singleton creation flag.

void __fastcall FamilyManager::constructor(FamilyManager *this)
{
    Family *familyArrayStart;          // Points to the last family object's position, then decremented
    int familyIndex;                   // Loop counter: 6 families

    // Set base class vtables (first two pointers of the object)
    this->vtable = reinterpret_cast<VTableEntry*>(&PTR_FUN_00d77acc);    // +0x00: Base class interface vtable
    this->vtable2 = reinterpret_cast<VTableEntry*>(&PTR_LAB_00d77abc);   // +0x04: Base class second vtable (if multiple inheritance)

    // Register the manager class type with a hash identifier
    // 0x73a2895d is likely a ClassID or RTTI hash
    registerClassType(0x73a2895d);

    // Initialize the 6 family objects. They are placed at offsets descending from +0xAA.
    // The last family is at offset +0x1A after all decrements.
    familyArrayStart = reinterpret_cast<Family*>((char*)this + 0xAA);
    familyIndex = 6;
    do
    {
        familyArrayStart = reinterpret_cast<Family*>((char*)familyArrayStart - 0x18);
        // Construct a Family object at the given address, with a specific constructor vtable (LAB_00897d00)
        Family::constructAt(familyArrayStart, 0x18, 4, &LAB_00897d00);
        familyIndex--;
    } while (familyIndex >= 0);

    // Override vtables to derived class (FamilyManager) vtables
    this->vtable2 = reinterpret_cast<VTableEntry*>(&PTR_LAB_00e30fe0);   // +0x04: Derived class second vtable
    this->vtable = reinterpret_cast<VTableEntry*>(&PTR_LAB_00d77ab8);    // +0x00: Derived class main vtable

    // Clear global singleton flag (DAT_01129988) indicating the FamilyManager is now created
    g_FamilyManagerCreated = 0;
}