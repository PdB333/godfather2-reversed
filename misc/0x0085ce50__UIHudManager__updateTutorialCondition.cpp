// FUNC_NAME: UIHudManager::updateTutorialCondition
void __thiscall UIHudManager::updateTutorialCondition(UIHudManager *this, int strId, TutorialConditionData *out)
{
    bool validStr;
    bool result;
    char *text;
    float elapsed;

    validStr = isStringValid(strId);
    if (!validStr) {
        result = false;
    }
    else {
        if (!isObjectValid(g_pManager1) && !isObjectValid(g_pManager2)) {
            int singleton = getSingleton(0x36); // eSingleton_TutorialManager
            if (!isObjectValid(singleton)) {
                elapsed = (this->*(this->vtable + 0x1a8))(); // virtual: getTimeSinceLastSpeaker()
                if (elapsed >= g_fadeThreshold && 
                    out->condition1 <= 0.0f && 
                    out->condition2 <= 0.0f && 
                    *(char *)(&out->condition3) == 0) // bool flag at offset 16
                {
                    result = true;
                }
                else {
                    result = false;
                }
            }
        }
    }
    setActionResult(result);
    text = getTextPointer(&strId);
    out->flag = (*text != '\0');
}