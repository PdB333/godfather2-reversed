// FUNC_NAME: StreamManager::release
void StreamManager::release(void)
{
    // vtable initially points to StreamManager vtable (PTR_LAB_00e3f0ac)
    *(int *)this = (int)&PTR_LAB_00e3f0ac;

    // Destroy sub-object at offset 0x4
    FUN_005d9a00((int)this + 4);
    // Destroy another sub-object or cleanup
    FUN_005d9e60();

    // If pointer at offset 0x8 is non-zero, release it via virtual call at vtable+4
    if (*(int *)((int)this + 8) != 0) {
        (**(code **)(*(int *)*(int *)this + 4))(*(int *)((int)this + 8), 0);
        *(int *)((int)this + 8) = 0;
    }

    // Call virtual function at vtable+0xc (likely base class destructor)
    (**(code **)(*(int *)*(int *)this + 0xc))();

    // Switch vtable to base class vtable (PTR_LAB_00e3f0b0)
    *(int *)this = (int)&PTR_LAB_00e3f0b0;

    // Reset global singleton pointer to null
    gStreamManager = 0;
}

// Note: PTR_LAB_00e3f0ac and PTR_LAB_00e3f0b0 are vtable addresses for the derived and base classes.
// FUN_005d9a00 and FUN_005d9e60 are likely destructors for embedded sub-objects or manual cleanup routines.