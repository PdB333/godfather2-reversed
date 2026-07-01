// FUNC_NAME: ConfigurableObject::registerReflectionFields
// Funct address: 0x00912430
// This function registers 8 member variables (likely int/float) of the object for reflection/serialization.
// It first calls a base class registration, then binds each variable using a descriptor global and an offset.

// Note: The thunk_FUN_005c1740 is likely a base class registration helper.
// FUN_005c01d0 is the actual field binding function (takes descriptor, pointer to field, flags, etc.)

void __fastcall ConfigurableObject::registerReflectionFields(int thisPtr)
{
    // Call base class reflection registration
    // thunk_FUN_005c1740 -> likely baseRegisterFields()
    baseRegisterFields();

    // Bind each field using global descriptor objects.
    // The second argument is a pointer to the member variable (offset from this).
    // The 3rd argument (1) might indicate read/write access or type.
    // Offsets: +0x5c, +0x60, +0x6c, +0x70, +0x64 (100 dec), +0x68, +0x74, +0x78
    registerField(&s_fieldDescriptor5c, thisPtr + 0x5c, 1, 0, 0, 0);  // field at +0x5c
    registerField(&s_fieldDescriptor60, thisPtr + 0x60, 1, 0, 0, 0);  // field at +0x60
    registerField(&s_fieldDescriptor6c, thisPtr + 0x6c, 1, 0, 0, 0);  // field at +0x6c
    registerField(&s_fieldDescriptor70, thisPtr + 0x70, 1, 0, 0, 0);  // field at +0x70
    registerField(&s_fieldDescriptor64, thisPtr + 0x64, 1, 0, 0, 0);  // field at +0x64 (100)
    registerField(&s_fieldDescriptor68, thisPtr + 0x68, 1, 0, 0, 0);  // field at +0x68
    registerField(&s_fieldDescriptor74, thisPtr + 0x74, 1, 0, 0, 0);  // field at +0x74
    registerField(&s_fieldDescriptor78, thisPtr + 0x78, 1, 0, 0, 0);  // field at +0x78
}