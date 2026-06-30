// FUNC_NAME: EARSModifier::initializeFromList
void __thiscall EARSModifier::initializeFromList(EARSModifier* this, EARSObjectManager* manager, DefinitionList* list) {
    // Call virtual function at vtable+4 of manager (likely getParentObject)
    EARSObject* parentObj = manager->getParentObject(); // vtable+4
    
    // Setup vtable for this modifier
    this->vtable = (void**)0x00e313c8; // Global vtable pointer
    this->next = 0; // Clear linked list next pointer
    
    FUN_0060ffd0(); // Global initialization call (unknown)
    
    if (parentObj != 0) {
        this->parentObject = parentObj; // +0x24 (offset 0x90)
        this->linkPrev = 0; // +0x27 (offset 0x9c)
        
        // Insert into parent's modifier linked list (at parent+0x84)
        if (parentObj->modifierListHead != 0) {
            parentObj->modifierListHead->prev = &this->linkNode; // +0x8c
        }
        parentObj->modifierListHead = &this->linkNode; // +0x84
    }
    
    FUN_006101b0(); // Another global init
    
    // Search for a specific class hash in the definition list
    unsigned int count = *(unsigned short*)(list + 0x20);
    if (count != 0) {
        for (unsigned int i = 0; i < count; i++) {
            DefinitionEntry* entry = *(DefinitionEntry**)(*(int*)(list + 0x1c) + i * 4);
            if (entry->classHash == 0x2e1ead2b) { // Specific class identifier
                // Call virtual function at vtable+8 of manager (resolve object by ID)
                int resolvedId = manager->resolveObjectById(entry->objectId); // vtable+8
                this->objectId = resolvedId; // Store at +4
                break;
            }
        }
    }
}