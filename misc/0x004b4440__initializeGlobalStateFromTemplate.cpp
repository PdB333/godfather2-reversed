// FUNC_NAME: initializeGlobalStateFromTemplate
void __cdecl initializeGlobalStateFromTemplate(void)
{
    // Local struct built on stack: likely represents a temporary state snapshot
    struct LocalInitBlock {
        int   field0;  // offset +0x00
        int   field4;  // offset +0x04
        char  field8;  // offset +0x08
    };

    LocalInitBlock block;
    block.field0 = g_globalTemplate;  // DAT_01218028 – global default value
    block.field4 = 0;
    block.field8 = 0;

    // Initializes some system/object using the template (second param 0 = flag)
    applyInitialization(&block, 0);
}