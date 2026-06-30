// FUNC_NAME: callSystemForwarder
extern void* DAT_0121a390; // Global object pointer (e.g., manager instance)
extern char* DAT_0121b638; // Global structure with field at +0x8
extern void FUN_0060ab00(void* arg1, int32_t arg2); // Target function (likely a callback/event handler)

void callSystemForwarder(void)
{
    // Delegates to FUN_0060ab00 with two arguments:
    // - Global pointer DAT_0121a390 (unknown type)
    // - 32-bit value read from offset +0x8 of global structure DAT_0121b638
    FUN_0060ab00(DAT_0121a390, *(int32_t*)(DAT_0121b638 + 8));
}