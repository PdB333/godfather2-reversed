// FUNC_NAME: NPCFamilyComponent::getCurrentFamily
__thiscall int NPCFamilyComponent::getCurrentFamily(NPCFamilyComponent* this) {
    int familyIndex;
    
    // Check if any family affiliation is set (4 possible family slots at +0x10, +0x14, +0x18, +0x1c)
    if ((((*(int*)(this + 0x10) != 0) || 
          (*(int*)(this + 0x14) != 0)) || 
         (*(int*)(this + 0x18) != 0)) || 
        (*(int*)(this + 0x1c) != 0)) {
        
        familyIndex = FUN_006ea7b0(this + 0x10); // Find active family slot
        if (familyIndex >= 0) {
            // Return family ID from table at +0x30, indexed by slot
            return *(int*)(*(int*)(this + 0x30) + familyIndex * 4);
        }
    }
    return 0; // No family
}