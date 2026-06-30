// FUNC_NAME: Sound3DComponent::updatePosition
// Function address: 0x00753650
// Role: Updates the 3D position of a sound effect attached to an entity, with checks for sound component validity and entity state.

void __thiscall Sound3DComponent::updatePosition(Sound3DComponent* this)
{
    int soundCompPtr;          // value at this+0x70
    int entityPtr;             // value at this+0x50
    int baseObjPtr;            // pointer to base object (sound comp - 0x48)
    int transformA, transformB;
    float posX, posY, posZ;
    float factor = DAT_00d5ccf8;   // global scaling factor
    
    // Access fields
    soundCompPtr = *(int*)((char*)this + 0x70);
    entityPtr = *(int*)((char*)this + 0x50);
    
    // Conditions: sound component must exist and not be a special value (0x48), entity must exist
    if (soundCompPtr != 0 && soundCompPtr != 0x48 && entityPtr != 0) {
        
        // Get two transform matrices (likely world and local)
        transformA = FUN_00471610();   // returns pointer to a matrix/transform
        transformB = FUN_00471610();
        
        // Compute interpolated position: scale first vector + second vector offset
        posX = ((float*)transformA)[0x20/4] * factor + ((float*)transformB)[0x30/4];
        posY = ((float*)transformA)[0x24/4] * factor + ((float*)transformB)[0x34/4];
        posZ = ((float*)transformA)[0x28/4] * factor + ((float*)transformB)[0x38/4];
        
        // Get base object pointer (sound component subobject subtracted by 0x48)
        if (soundCompPtr == 0) {
            baseObjPtr = 0;
        } else {
            baseObjPtr = soundCompPtr - 0x48;   // parent of the subobject at offset 0x48
        }
        
        // Call virtual function at table slot 0x1e8/4 = 0x7A (122) on base object
        // Parameters: entityPtr, 2, (entityPtr->field_0x6e4 >> 2), &position, 1, 0, 1
        (**(code**)(*(int*)baseObjPtr + 0x1e8))
            (entityPtr, 2, *(int*)(entityPtr + 0x6e4) >> 2, &posX, 1, 0, 1);
        
        // Check entity state flags: if entity is "stopped" (timing <= 0) and certain bit flags are set
        float timing = (**(code**)(*(int*)entityPtr + 0xc0))();   // virtual function returning float
        if (timing <= 0.0f &&
            ((*(unsigned char*)((char*)this + 0xa4) & 1) != 0) &&
            (*(int*)((char*)this + 0x98) != 0 &&
             (*(unsigned char*)(*(int*)((char*)this + 0x98) + 4) & 0xc0) != 0))
        {
            // Trigger sound events
            FUN_00892af0(0);               // stop sound?
            FUN_00892ce0(entityPtr, 0);     // update sound with entity
            if (entityPtr != 0) {
                FUN_0072c050(0x11);        // play sound event 0x11
            }
            if (posY != 0.0f) {
                FUN_004daf90(&posY);       // set doppler or position parameter
            }
        }
        
        // Update timer or debug
        FUN_007f6420(0x36);                // sound manager update tick (0x36 = 54)
    }
}