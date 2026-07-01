// FUNC_NAME: GameObject::constructor
void __fastcall GameObject::constructor(GameObject* this) {
    // Set primary vtable pointer (first base class) at offset 0x00
    this->__vtable_a = &PTR_FUN_00d737fc;  // Pointer to primary vtable

    // Call base class constructor (likely EARSObject or similar)
    baseClassConstructor(this);  // Address 0x0082aea0

    // Set secondary vtable pointer (second base class or interface) at offset 0x30 (0x0C * 4)
    this->__vtable_b = &PTR_LAB_00e32854; // Pointer to secondary vtable

    // Call secondary initialization routine
    secondaryInit(this);  // Address 0x00821f60
}