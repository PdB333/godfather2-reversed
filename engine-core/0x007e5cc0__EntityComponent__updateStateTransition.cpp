// FUNC_NAME: EntityComponent::updateStateTransition
void __fastcall EntityComponent::updateStateTransition(void)
{
    char bOldFlag = this->field_27c; // +0x27c: previous "state==2" flag
    int iStateResult = getStateCondition(this->field_58); // +0x58: pointer to a state manager or activity handler
    this->field_27c = (iStateResult == 2); // +0x27c: current "state==2" flag
    if (iStateResult == 2 && !bOldFlag) {
        // Just entered state 2 (e.g., inactive), set rising edge flag
        this->field_27d = 1; // +0x27d: one-shot trigger for entering state 2
    } else {
        this->field_27d = 0;
    }
}