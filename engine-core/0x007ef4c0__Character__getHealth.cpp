//FUNC_NAME: Character::getHealth
float Character::getHealth() {
    // this+4 points to a data block (e.g., CharacterData)
    // data block +0x13c is the health float
    return *(float*)(*(int*)((char*)this + 4) + 0x13c);
}