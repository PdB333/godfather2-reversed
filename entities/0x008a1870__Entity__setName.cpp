// FUNC_NAME: Entity::setName
void __thiscall Entity::setName(char *name) {
    // Copy the string to the name buffer at offset 0x1C8, max 64 bytes
    _strncpy(reinterpret_cast<char *>(this + 0x1C8), name, 0x40);
}