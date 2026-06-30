// FUNC_NAME: EngineContext::EngineContext
EngineContext* __fastcall EngineContext::EngineContext(EngineContext* this)
{
    this->vtable = &g_EngineContextVtable; // vtable at 0x00e33520
    this->field_0x04 = 0;
    this->field_0x08 = 0;
    this->pPrevious = g_pCurrentEngineContext; // offset 0x0C, save previous global pointer
    g_pCurrentEngineContext = 0;               // clear the global singleton pointer

    // If there was a previous instance and it has bit 1 set at offset 0x30, call its cleanup
    if (this->pPrevious != 0 && ((*(uint32_t*)((uint8_t*)this->pPrevious + 0x30) >> 1) & 1) != 0)
    {
        EngineContext::cleanup(this->pPrevious); // FUN_00481430
    }
    return this;
}