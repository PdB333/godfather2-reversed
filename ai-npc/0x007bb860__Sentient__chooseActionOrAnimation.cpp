// FUNC_NAME: Sentient::chooseActionOrAnimation
void __thiscall Sentient::chooseActionOrAnimation(Sentient* this, char bForce, uint actionType, uint targetType) {
    char cVar1;
    int selectedAnim;
    int fallbackFlag;

    // Check if a global condition prevents action (e.g., cutscene active)
    if (isCutsceneActive()) {
        // Cutscene is active; fallback logic
        // If force flag is zero, or getting default animation fails, use table lookup
        if ((bForce == '\0') || (selectedAnim = getDefaultAnimation(this->m_actionSlot), selectedAnim == 0)) {
            selectedAnim = 0;
            fallbackFlag = 1;
            // Only use table if slot index is valid and action/target types are in range
            if ((this->m_actionSlot < 0x3c) && (actionType < 5) && (targetType < 5)) {
                selectedAnim = gAnimationTable[this->m_actionSlot][actionType][targetType];  // +0x1d
            }
        }
        // If selected animation is valid, apply it
        if (!isAnimationValid(this->m_actionSlot)) {
            setCurrentAnimation(this->m_someOtherField, fallbackFlag);  // +0x1e
        }
    } else {
        // Normal processing: no cutscene
        cVar1 = isSomethingEnabled();
        if (cVar1 != '\0') {
            if (this->m_hasSpecialBehavior == 1) {  // +0x1f
                selectedAnim = getSpecialAnimation(this->m_actionSlot, actionType, targetType);  // +0x1d
            } else {
                selectedAnim = getDefaultAnimation(this->m_actionSlot);  // +0x1d
            }
        }
    }

    // Play the selected animation via virtual function
    // vtable+0x2c: void playAnimation(int animID, int loop, int unk, int bone, float speed)
    (*(void (__thiscall **)(Sentient*, int, int, int, int, float))(*this + 0x2c))(selectedAnim, 1, 1, 0, this->m_boneIndex, 1.0f);  // +0x67
    this->m_lastSelectedAnimation = selectedAnim;  // +0x6a
}