// FUNC_NAME: createTemporaryObjectWrapper
// Function address: 0x00670030
// Role: Creates a temporary stack object and passes it to an initialization function.
// This is a thin wrapper called from many game systems (cutscene, animation, vehicle, etc.).
// The actual initialization is done by FUN_0066ffb0.

void createTemporaryObjectWrapper(void)
{
    // Allocate a temporary object on the stack (size likely 0xC bytes based on offset).
    // The actual type is unknown, but it's passed as a pointer to FUN_0066ffb0.
    int local_buf[3]; // Placeholder for a struct or array of 12 bytes

    // Initialize the temporary object via function at 0x0066ffb0.
    // This function likely sets up internal state or registers the object globally.
    FUN_0066ffb0(&local_buf);
}