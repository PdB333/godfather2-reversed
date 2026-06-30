// FUNC_NAME: SomeClass::decideAndAct (at 0x00728210)
void __thiscall SomeClass::decideAndAct(void* object) {
    char actionFlag = reinterpret_cast<char*>(this)[0x150] == '\0';  // +0x150: bool flag (0 = allow action?)
    
    if (gTimeThreshold > *(float*)((char*)this + 0x148)) {  // +0x148: timer/distance (must be less than global)
        actionFlag = checkCondition(object);  // 0x007273a0: evaluate external condition
    }
    
    if (actionFlag != '\0') {
        executeAction(object);  // 0x00727630: perform the action
    }
}