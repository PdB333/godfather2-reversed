// FUNC_NAME: setObjectDescription
void __fastcall setObjectDescription(int *param1) {
    // param1 is this pointer? Actually *param1 likely points to a property bag at offset 0x44.
    // Get the property bag from object (first field is pointer?)
    void *propertyBag = *(void **)(*param1 + 0x44);
    // Set the "_description" property to "B_description"
    FUN_004db3f0(propertyBag, "_description", "B_description");
}