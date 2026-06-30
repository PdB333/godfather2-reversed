// FUNC_NAME: EARSObject::EARSObject (constructor)
undefined4 __thiscall EARSObject::EARSObject(undefined4 thisParam, byte flags)
{
    int *vtablePtr;

    // Call base class constructor / common initialization
    baseConstructor();

    // If the low bit of flags is set, perform additional initialization
    if ((flags & 1) != 0) {
        // Retrieve the object's vtable (static getter)
        vtablePtr = (int *)getVtable();

        // Call the second virtual function (vtable[1]) with size/type parameter 0x80
        (**(code **)(*vtablePtr + 4))(thisParam, 0x80);
    }

    return thisParam;
}