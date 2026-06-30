// FUNC_NAME: Entity::getFlagIfSet
uint __thiscall Entity::getFlagIfSet(uint flag) {
    char result;
    uint dummy = 0;
    // Call virtual function at vtable offset 0x10 (entry 4) which likely checks a flag/condition.
    // The virtual function takes (flag, &dummy) and returns a char (non-zero if the flag is set/valid).
    result = (this->*(char (__thiscall*)(Entity*, uint, uint*))(*(int**)this)[4])(flag, &dummy);
    // If the condition is true, return the original flag value; otherwise return 0.
    return result != '\0' ? flag : 0;
}