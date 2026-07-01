// FUNC_NAME: Entity::reset
void __fastcall Entity::reset(Entity* this)
{
    // Set vtable pointers (offsets 0x00, 0x3C, 0x48)
    *(void**)this = &PTR_FUN_00d69718;
    *(void**)((int)this + 0x3C) = &PTR_LAB_00d69708;
    *(void**)((int)this + 0x48) = &PTR_LAB_00d69704;

    // If the object was previously initialized, clean up first
    if (*(char*)((int)this + 0x116) != '\0') {
        FUN_00784910(this);
        *(char*)((int)this + 0x116) = 0;
    }

    // Release two global managers (or singleton references)
    FUN_004086d0(&DAT_0120e924);
    FUN_004086d0(&DAT_0120e91c);
    // Final cleanup for global resources
    FUN_0046c640();
    return;
}