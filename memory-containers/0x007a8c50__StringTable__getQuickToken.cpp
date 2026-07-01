// FUNC_NAME: StringTable::getQuickToken
int __thiscall StringTable::getQuickToken(int id) {
    char buffer[12]; // small buffer for short token/status
    if (id != 0) {
        if (lookupToken(id, buffer)) {
            processToken(buffer);
            return 1;
        }
    }
    return 0;
}