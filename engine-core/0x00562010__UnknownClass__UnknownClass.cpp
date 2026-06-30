// FUNC_NAME: UnknownClass::UnknownClass
// Function: 0x00562010 - Constructor with initialization flag (possibly memory ownership or registration)

// Base initialization - likely calls a static initializer or base class constructor
void init();

// Registration or cleanup function, called if flag bit 0 is set
void registerObject(void* self);

undefined4 __thiscall UnknownClass::UnknownClass(undefined4 this, byte param_2)
{
    // Call base initializer (could be a global static init or base constructor)
    init();

    // If the flag indicates special handling (e.g., memory allocation or registration)
    if ((param_2 & 1) != 0)
    {
        // Perform additional setup, possibly registering with a manager or allocating memory
        registerObject(this);
    }

    return this;
}