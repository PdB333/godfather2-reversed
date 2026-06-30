// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject(void* thisptr) {
    // Set vtable pointer to 0x00d63090 (likely EARSObject's vtable)
    *(void**)thisptr = (void*)0x00d63090;

    // Free sub-object at offset +0x68 (param_1[0x1a]) if it exists
    if (*(void**)((char*)thisptr + 0x68) != 0) {
        FUN_004daf90((char*)thisptr + 0x68);  // Release subobject (probably pointer to another object)
    }

    // Call base initialization or engine setup
    FUN_0080ea60();  // Possibly base constructor or registration
}