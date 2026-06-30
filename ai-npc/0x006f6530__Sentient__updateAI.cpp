// FUNC_NAME: Sentient::updateAI
void __thiscall Sentient::updateAI(Sentient* this) {
    bool canUpdate;
    
    // vtable[7] – checks if update is allowed (e.g., not dead, not in cutscene)
    canUpdate = (this->vtable[7])();
    if (canUpdate) {
        // vtable[9] – perform initial action with argument 1 (e.g., set active flag)
        (this->vtable[9])(1);
    }
    
    // m_state at offset 0xE8 (4*0x3A)
    // m_targetId at offset 0xB4 (4*0x2D)
    // 0x48 (~72) is a special "no target" value (e.g., kTargetNone)
    if ((this->m_state == 2) && (this->m_targetId != 0) && (this->m_targetId != 0x48)) {
        // Called when in state 2 (e.g., kStateEngaged) and target is valid
        FUN_006ab790();  // handleTargetCondition(this);
    }
    
    // vtable[11] – main update dispatcher (often a switch on state)
    (this->vtable[11])();
}