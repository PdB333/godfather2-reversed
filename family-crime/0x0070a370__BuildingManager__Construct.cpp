// FUNC_NAME: BuildingManager::Construct
void __fastcall BuildingManager::Construct(BuildingManager* this)
{
    // Set vtable and additional function pointers
    this->vtable = &PTR_FUN_00d613f4;          // +0x00
    this->field_3C = &PTR_LAB_00d613e4;        // +0x3C
    this->field_48 = &PTR_LAB_00d613e0;        // +0x48

    // Global/member init (possibly a lock or reference count)
    FUN_004086d0(&DAT_012069c4);

    // Sub-object at +0x5C (offset 0x17 * 4)
    Container* container1 = reinterpret_cast<Container*>(&this->field_5C);
    if (Container::IsConstructed(container1)) // FUN_00402080
    {
        Container::Destroy(container1);       // FUN_004086d0
    }
    Container::Construct(container1);          // FUN_00408310

    // Sub-object at +0x64 (offset 0x19 * 4)
    Container* container2 = reinterpret_cast<Container*>(&this->field_64);
    if (Container::IsConstructed(container2))
    {
        Container::Destroy(container2);
    }
    Container::Construct(container2);

    // Sub-objects at +0x6C and +0x74 (offset 0x1b * 4, 0x1d * 4)
    Container* container3 = reinterpret_cast<Container*>(&this->field_6C);
    Container::Construct(container3);

    Container* container4 = reinterpret_cast<Container*>(&this->field_74);
    Container::Construct(container4);

    // Post-construction step (register with manager, etc.)
    FUN_0046c640();
}