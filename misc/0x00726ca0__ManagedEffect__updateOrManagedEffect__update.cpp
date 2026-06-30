// FUNC_NAME: ManagedEffect::updateOrManagedEffect::update

void __thiscall ManagedEffect::update(int this) {
    int* effectData = *(int**)(this + 0xb8);
    
    // Check if effect data exists and its magic number (first 4 ints) is valid or all zero
    if ((effectData != nullptr) &&
        ((((*effectData != 0xBABDB8BA) || (effectData[1] != 0xBEEFBBEF) ||
           (effectData[2] != 0xEAC15A55) || (effectData[3] != 0x91100911)) &&
         ((*effectData != 0) || (effectData[1] != 0) ||
          (effectData[2] != 0) || (effectData[3] != 0))))) {
        int* validatedHandle = FUN_00446100(effectData, 0);   // validate/get handle
        if (validatedHandle != 0) {
            FUN_00726830(validatedHandle);                    // process/reset the effect
        }
        FUN_009c8eb0(*(void**)(this + 0xb8));                 // free the effect data
        *(int**)(this + 0xb8) = nullptr;
    }
    
    // Update enable/disable flags and call appropriate handlers
    int flags = *(int*)(this + 0x110);
    if ((flags & 4) == 0) {                                  // bit 2 of flags? (0x110)
        *(unsigned char*)(this + 0x114) &= 0xFE;              // clear bit 0 of state byte
        if ((*(unsigned char*)(this + 0x114) & 2) == 0) {    // bit 1 is clear
            *(unsigned char*)(this + 0x114) |= 2;             // set bit 1
            FUN_00728070(this);                               // enable effect routine
        }
    } else {
        *(unsigned char*)(this + 0x114) |= 1;                 // set bit 0
        if ((*(unsigned char*)(this + 0x114) & 2) != 0) {    // bit 1 is set
            *(unsigned char*)(this + 0x114) &= 0xFD;          // clear bit 1
            FUN_00727f30(this);                               // disable effect routine
        }
    }
    
    // Handle entity reference if present and specific condition triggers
    int* entity = *(int**)(this + 0x118);
    if ((entity != nullptr) && ((*(int*)(this + 0x110) >> 0x12 & 1) != 0)) {  // bit 18 of flags
        int entityStatus = FUN_006b0ee0(entity);               // check entity alive/valid
        if ((entityStatus == 0) ||
            ((*(unsigned int*)(entityStatus + 0x34) >> 0x16 & 1) == 0)) { // bit 22 of entity field
            *(unsigned char*)(this + 0x114) &= 0xFE;
            if ((*(unsigned char*)(this + 0x114) & 2) == 0) {
                *(unsigned char*)(this + 0x114) |= 2;
                FUN_00728070(this);
            }
        } else {
            FUN_00726c70();                                    // alternative effect handling
        }
        FUN_00408680(&DAT_0112a628);                          // release global resource handles
        FUN_00408680(&DAT_0112a5c4);
    }
    
    // Final cleanup if flags indicate
    if ((*(int*)(this + 0x110) >> 0x16 & 1) != 0) {           // bit 22 of flags
        FUN_00408680(&DAT_012069f4);
    }
}