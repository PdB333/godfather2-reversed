// FUNC_NAME: SmartPtrPair::releaseAndDestroy
void __fastcall SmartPtrPair::releaseAndDestroy(uint32_t* thisPtr)
{
    // Struct layout:
    // +0x00: m_pObject1 (pointer to first object with vtable)
    // +0x04: m_pAttached1 (pointer to attached resource for object1)
    // +0x08: m_pObject2 (pointer to second object with vtable)
    // +0x0C: m_pAttached2 (pointer to attached resource for object2)

    if (thisPtr[3] != 0) {
        // Release attached resource of second object (vtable offset 4)
        (**(code **)(*(int *)thisPtr[2] + 4))(thisPtr[3], 0);
        thisPtr[3] = 0;
    }
    // Delete second object (vtable offset 0xC)
    (**(code **)(*(int *)thisPtr[2] + 0xC))();

    if (thisPtr[1] != 0) {
        // Release attached resource of first object (vtable offset 4)
        (**(code **)(*(int *)thisPtr[0] + 4))(thisPtr[1], 0);
        thisPtr[1] = 0;
    }
    // Delete first object (vtable offset 0xC)
    (**(code **)(*(int *)thisPtr[0] + 0xC))();
}