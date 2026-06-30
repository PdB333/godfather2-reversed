// FUNC_NAME: createGameManagerInstance
int createGameManagerInstance()
{
    int result;

    // Check if a global counter has reached a threshold (0x2a0 = 672 frames/ticks)
    if (0 < g_someCounter / 672)
    {
        SomeContext context;
        getContext(&context);  // Retrieve some context data via stack

        // Allocate a new manager object (sizeof = 0x24 = 36 bytes)
        result = (int)operatorNew(0x24);
        if (result != 0)
        {
            // Construct the object with the context
            result = constructManager(result, context);
        }

        // Store pointer to the singleton manager
        g_pManager = result;
        if (result != 0)
        {
            // Set vtable pointer at offset 0x20 (base class offset)
            *(void***)(result + 0x20) = &s_ManagerVTable;
        }
    }
    else
    {
        result = 0;
    }

    return result;
}