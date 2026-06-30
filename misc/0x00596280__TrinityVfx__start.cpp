// FUNC_NAME: TrinityVfx::start
// Address: 0x00596280
// Role: Start or stop a VFX effect based on state, compute transform matrices, and log errors on failure.

void __fastcall TrinityVfx::start(TrinityVfx* this)
{
    // +0x78: m_vfxName (pointer to string)
    if (this->m_vfxName == 0) {
        // Call some global diagnostic method (e.g., report missing VFX)
        (**(code **)(*gVfxManager + 4))();
        return;
    }

    // +0x18: m_state (0 = create, non-zero = stop)
    if (this->m_state == 0) {
        // +0x7C: m_transformData (pointer to transform structure)
        TrinityTransform* transform = this->m_transformData;
        // Fill local matrix from transform components
        (**(code **)(*gMathUtils + 4))(transform->pos, transform->rot, transform->scale, 1.0f, &localTransform);
        // +0x08: m_effectData (pointer to effect descriptor)
        if ((*(byte*)this->m_effectData & 4) != 0) {
            // Multiply local matrix with effect's orientation offset
            (**(code **)(*gMathUtils + 0x18))(&localTransform, (byte*)this->m_effectData + 0x10, &tempMatrix);
            (**(code **)(*gMathUtils + 0x10))(&tempMatrix, &localTransform);
        }
    } else {
        // Stop VFX: clear flag bit 1 at +0x04 (m_flags)
        this->m_flags &= 0xfffffffd;
        FUN_0059b690(0);  // stopTransform(...)
        FUN_0059bb50(&localTransform);  // resetTransform(...)
    }

    // Apply post-processing to local matrix array
    (**(code **)(*gMathUtils + 0x44))(localMatrixArray);
    // Set final matrix from stack values (remnants of earlier transform)
    (**(code **)(*gMathUtils + 4))(uStack_74, localTransform.pos, uStack_6c, 1.0f, &finalMatrix);

    // Virtual call at vtable offset 0x20 (index 8): applyVfx()
    bool success = (this->vtable[0x20/4])();
    if (!success) {
        // Log error: VFX name and sequence name extracted from effect descriptor
        (**(code **)(*gVfxManager + 0xc))(
            gVfxManager,
            "ERROR : TrinityVfx::start : Unable to create VFX [%s] in sequence [%s]",
            this->m_vfxName,
            *(int*)(this->m_effectData + 4) + 0x30  // sequence name offset
        );
    }
}