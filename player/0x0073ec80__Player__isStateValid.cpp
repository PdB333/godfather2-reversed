// FUNC_NAME: Player::isStateValid  
bool __thiscall Player::isStateValid(void) {  
    int stateValue = *(int *)(*(int *)((char *)this + 0x180) + 0xc4); // this->stateObject->stateField  
    if (stateValue != 0 && stateValue != 1) {  
        return false;  
    }  
    return true;  
}