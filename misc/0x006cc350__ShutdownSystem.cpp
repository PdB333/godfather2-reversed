// FUNC_NAME: ShutdownSystem
void ShutdownSystem(void)
{
    // Temporary object for release call
    struct {
        uint32_t field0;  // +0x00
        uint32_t field4;  // +0x04
        uint8_t  field8;  // +0x08
    } temp;

    if (g_shutdownFlag != 0) {
        g_shutdownFlag = 0;
        temp.field0 = g_pResourceA;  // DAT_0112a80c
        temp.field4 = 0;
        temp.field8 = 0;
        // Release resource A with a second argument of 0
        ShutdownResource(&temp, 0);
    }

    // Destroy remaining global resources
    DestroyObject(&g_pResourceB);  // DAT_0112a814
    DestroyObject(&g_pResourceC);  // DAT_0112a80c (same as field0 above?)
    DestroyObject(&g_pResourceD);  // DAT_0112a820
}