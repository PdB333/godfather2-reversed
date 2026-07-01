// FUNC_NAME: BaseObject::attachToManager
void __fastcall BaseObject::attachToManager(BaseObject* this)
{
    // Static initialization for the manager (likely hardware or system)
    initializeManager(); // FUN_005c1740
    
    // Register the object's data block (at offset +0x54) with the global manager instance
    // The parameters: destination = &managerInstance, source = this->dataBlock,
    // followed by flags (1, 0, 0, 1) indicating add, not overwrite, etc.
    registerData(&DAT_00d85730, this + 0x54, 1, 0, 0, 1);
}