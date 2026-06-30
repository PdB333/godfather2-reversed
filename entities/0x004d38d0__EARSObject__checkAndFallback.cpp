// FUNC_NAME: EARSObject::checkAndFallback
void EARSObject::checkAndFallback(void* obj) {
    char condition = checkCondition(obj);
    if (condition == 0) {
        fallbackHandler(obj);
    }
}