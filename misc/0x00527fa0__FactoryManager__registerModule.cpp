// FUNC_NAME: FactoryManager::registerModule
void FactoryManager::registerModule()
{
    // Call the module's initialization function (offset 4 in its vtable/struct)
    int handle = (*(int (*)())(PTR_PTR_01125b90 + 4))();
    // Convert handle to internal ID and store
    _DAT_01125b98 = FUN_0060d740(handle);

    // Call second initialization function (offset 0x10)
    (*(void (*)())(PTR_PTR_01125b90 + 0x10))();

    // Link this module into the global registry (linked list)
    _DAT_01125b94 = DAT_012058ec;          // +0x94: save previous head
    DAT_012058f8++;                        // increment module count
    DAT_012058ec = &PTR_PTR_01125b90;      // new head points to this module's data
    _DAT_01125b9c = DAT_012058f8;          // +0x9c: store assigned index
}