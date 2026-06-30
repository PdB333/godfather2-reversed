// FUNC_NAME: Player::handleVehicleInteraction
void __thiscall Player::handleVehicleInteraction(int baseSubobj, int entity, undefined4 param3)
{
    Player* player = (Player*)(baseSubobj - 0x394); // derived object is at base subobject -0x394
    bool isActive = player->vtable->isActive(); // vtable+0x1bc
    int entity2 = entity; // save original entity pointer

    if (isActive && (*(int*)(entity + 0xc) != 0) && (*(int*)(entity + 0xc) != 0x48)) {
        // entity+0xc is a pointer to a component; 0x48 is possibly a type ID
        void* componentPtr = (void*)((*(int*)(entity + 0xc) == 0) ? 0 : (*(int*)(entity + 0xc) - 0x48));
        int outParam = 0;
        // 0x369ac561 is a hash for a specific component type
        bool found = ((int (*)(int, int*))componentPtr->vtable->findComponent)(0x369ac561, &outParam);
        if (found && outParam != 0) {
            // Clear bit 0x400 (bit 10) at offset 0x1f5c from the component
            *(uint*)(outParam + 0x1f5c) &= 0xfffffbff;
            // 0x3f800000 = 1.0f; parameter meaning unknown
            FUN_0078b4b0(1.0f, 1, 0);
        }
    }

    // Call base class function (likely BaseObject::update)
    FUN_00736bd0(entity2, param3);

    bool isActive2 = player->vtable->isActive(); // vtable+0x1bc
    if (isActive2) {
        // Modify flags at offset 0x1800 from base subobject (which is at player+0x394)
        uint flags = *(uint*)(baseSubobj + 0x1800);
        flags &= 0xffffff67; // clear bits 7,4,3 (0x98)
        flags |= 0x2000; // set bit 13
        *(uint*)(baseSubobj + 0x1800) = flags;

        // Get time and angle from virtual functions
        float time = player->vtable->getTime(); // vtable+0xc4
        float angle = player->vtable->getAngle(time); // vtable+0xc0
        FUN_009395a0(player, angle, time); // likely apply rotation/velocity
    }
}