// FUNC_NAME: StreamManager::StreamManager
void __fastcall StreamManager::StreamManager(StreamManager* this) {
    // Set vtable pointers for the class hierarchy
    this->vtable = (void*)0x00d80f10; // +0x00: primary vtable
    this->field_0x3C = (void*)0x00d80f00; // +0x3C: secondary vtable
    this->field_0x48 = (void*)0x00d80efc; // +0x48: tertiary vtable

    // If the reinitialization flag is set, perform extra setup
    if (this->m_bReinitFlag) {
        this->reinitializeInternal(); // 0x008f1bc0
    }

    // Initialize two embedded list structures at offsets 0xA0 and 0xA8
    // Each structure appears to be a linked list (e.g., of stream nodes)
    initList(&this->m_streamList1); // +0xA0
    initList(&this->m_streamList2); // +0xA8

    // Reset the same structures (probably clear head/tail pointers)
    resetList(&this->m_streamList1);
    resetList(&this->m_streamList2);

    // Global initialization (e.g., audio stream manager singleton reset)
    FUN_0046c640(); // global init function
}