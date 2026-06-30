// FUNC_NAME: BaseManager::~BaseManager
void __thiscall BaseManager::~BaseManager(BaseManager* this)
{
    // Free resource pointers at offsets 0x1C, 0x10, 0x04
    if (this->resource3) { // +0x1C
        engineDelete(this->resource3);
    }
    if (this->resource2) { // +0x10
        engineDelete(this->resource2);
    }
    if (this->resource1) { // +0x04
        engineDelete(this->resource1);
    }
    // Restore vtable to base class vtable
    this->vtable = &g_baseVtable;
    // Clear global singleton flag
    g_bManagerActive = false;
}