// FUNC_NAME: SimObject::SimObject

SimObject* __thiscall SimObject::SimObject(SimObject* thisObj, SimObjectCreationData* creationData)
{
    // +0x04: mObjectId (uint32)
    thisObj->mObjectId = 0;
    // +0x08: mTypeId (uint32)
    thisObj->mTypeId = 0;
    // +0x14: mFlags (uint32)
    thisObj->mFlags = 0;
    // +0x0C: mField1 (uint32)
    thisObj->mField1 = 0;
    // +0x10: mDataBlockIndex (uint32)
    thisObj->mDataBlockIndex = 0;
    // +0x18: mField2 (uint32)
    thisObj->mField2 = 0;
    // +0x1C: mField3 (uint32)
    thisObj->mField3 = 0;

    // Debug sentinels (set then cleared)
    // +0x20: mDebugMagic1 (uint32)
    thisObj->mDebugMagic1 = 0xBADBADBA;
    // +0x24: mDebugMagic2 (uint32)
    thisObj->mDebugMagic2 = 0xBEEFBEEF;
    // +0x28: mDebugMagic3 (uint32)
    thisObj->mDebugMagic3 = 0xEAC15A55;
    // +0x2C: mDebugMagic4 (uint32)
    thisObj->mDebugMagic4 = 0x91100911;

    // +0x30: mField4 (uint32)
    thisObj->mField4 = 0;
    // +0x34: mField5 (uint32)
    thisObj->mField5 = 0;
    // +0x38: mField6 (uint32)
    thisObj->mField6 = 0;

    // Clear debug magic (set to 0)
    thisObj->mDebugMagic4 = 0;
    thisObj->mDebugMagic3 = 0;
    thisObj->mDebugMagic2 = 0;
    thisObj->mDebugMagic1 = 0;

    // Set up first vtable pointer (primary vtable)
    // +0x00: vptr (pointer to vtable at 0x00e3280c)
    thisObj->vptr = &VTABLE_SIMOBJECT;

    // +0x3C: secondary vtable pointer (for a derived interface)
    // NOTE: This is later overwritten to PTR_LAB_00e32828
    thisObj->mSecondaryVTable = &VTABLE_SIMOBJECT_SECONDARY;

    // +0x40: mSomeFlags (uint32)
    thisObj->mSomeFlags = 1;
    // +0x44: mField8 (uint32)
    thisObj->mField8 = 0;

    // +0x48: tertiary vtable pointer (for another interface)
    // NOTE: Later overwritten to PTR_LAB_00e32838
    thisObj->mTertiaryVTable = &VTABLE_SIMOBJECT_TERTIARY;

    // +0x4C: mField9 (uint32)
    thisObj->mField9 = 0;

    // Set flags
    // +0x14: mFlags |= 0x28000000 (SimObjectFlag_IsGhost? or SimObjectFlag_Networked?)
    thisObj->mFlags |= 0x28000000;

    // Set main vtable pointer (overwrites initial)
    // +0x00: vptr = &PTR_FUN_00e3280c (actual vtable)
    thisObj->vptr = &VTABLE_SIMOBJECT_MAIN;

    // Overwrite secondary vtable pointer
    // +0x3C: mSecondaryVTable = &PTR_LAB_00e32828
    thisObj->mSecondaryVTable = &VTABLE_SIMOBJECT_SECONDARY_FINAL;

    // Overwrite tertiary vtable pointer
    // +0x48: mTertiaryVTable = &PTR_LAB_00e32838
    thisObj->mTertiaryVTable = &VTABLE_SIMOBJECT_TERTIARY_FINAL;

    // Merge more flags
    // +0x40: mSomeFlags |= 0x12 (possible network/ghost flags)
    thisObj->mSomeFlags |= 0x12;

    // Call internal initialization (likely sets up default properties)
    SimObject::onConstruction(thisObj);   // FUN_0043ab10

    // Register this object with the simulation manager
    // DAT_01223410 is a global pointer to the SimManager singleton
    // creationData->mDataBlockIndex is the data block index (offset +8)
    SimManager::registerObject(DAT_01223410, thisObj, creationData->mDataBlockIndex); // FUN_004467c0

    return thisObj;
}