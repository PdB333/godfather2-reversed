// FUNC_NAME: Entity::destructorPhase2
// Function at 0x00848860: performs mid-destruction cleanup, releases sub-component at +0x8C and switches vtables.

void __fastcall Entity::destructorPhase2(Entity* this)
{
    // Set vtable pointers to intermediate destruction stage
    // *this (offset +0x00) -> PTR_FUN_00d748c4 (destruction vtable)
    this->vtable = (void**)&PTR_FUN_00d748c4;
    // param_1[3] (offset +0x0C) -> PTR_LAB_00d74898 (base vtable)
    this->baseVtable = (void**)&PTR_LAB_00d74898;

    // Sub‑component at offset +0x8C (param_1[0x23])
    SubComponent* sub = this->subComponent; // offset +0x8C
    if (sub != nullptr) {
        // Release the sub‑component (FUN_004df600)
        sub->release();
        // Clear field at offset +0x08 inside the sub‑component (maybe ref count or link)
        sub->field_0x08 = 0;
        // Nullify pointer
        this->subComponent = nullptr;
    }

    // Final vtable switch to base class vtables for further destruction
    this->baseVtable = (void**)&PTR_LAB_00d747cc; // offset +0x0C
    this->vtable = (void**)&PTR_LAB_00d74620; // offset +0x00
}