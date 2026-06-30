// FUNC_NAME: GameObject::processFlags

void __fastcall GameObject::processFlags(GameObject *this) {
    char byteVal;

    FUN_00471280();  // base class update? or initialization
    if ((*(byte *)((int)this + 0x1c4) & 0x20) == 0) {  // check flag at +0x1c4 bit 5
        byteVal = FUN_00402080(&DAT_012069c4);  // some global singleton check
        if (byteVal != '\0') {
            FUN_004086d0(&DAT_012069c4);        // process or release global object
        }
    }
}