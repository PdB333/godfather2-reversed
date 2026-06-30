// FUNC_NAME: ContentScanner::ContentScanner
// Address: 0x004556e0
// Constructor: initializes vtable pointers, registers message handler "iMsgAllContentScanned"
// Object layout:
//   +0x00: primary vtable (PTR_FUN_00e31938)
//   +0x04: refCount/flag = 1
//   +0x08: field_08 = 0
//   +0x10: third vtable (PTR_FUN_00e31960)
//   +0x??: secondary vtable in sub-object (PTR_LAB_00e31948)

ContentScanner* __fastcall ContentScanner::ContentScanner(ContentScanner* this_)
{
    // Initialize reference/flag and other field
    this_->field_04 = 1;            // +0x04
    this_->field_08 = 0;            // +0x08

    // Allocate a sub-object (likely for multiple inheritance / secondary interface)
    ContentScanner* subObj = (ContentScanner*)FUN_00564ad0(); // operator new or similar

    // Set up vtable pointers
    this_->vtable1 = &g_vtable1;          // +0x00: PTR_FUN_00e31938
    subObj->vtable1 = &g_vtable2;         // +0x00 in sub-object: PTR_LAB_00e31948
    this_->vtable3 = &g_vtable3;          // +0x10: PTR_FUN_00e31960

    // Register message handler for content scanning complete message
    uint32_t msgId = FUN_004dafd0("iMsgAllContentScanned"); // hash/lookup
    FUN_00408260(&g_MessageHandlerTable, msgId); // register handler

    // If a global manager exists, link this object to it
    if (g_GlobalManager != 0) {
        FUN_00407e60(this_, &g_GlobalManager); // attach to manager
    }

    return this_;
}