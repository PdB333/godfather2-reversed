// FUNC_NAME: CharacterState::initialize
void __thiscall CharacterState::initialize(int thisObj)
{
    uint *staticFlags = (uint *)getStaticFlags(0x9b7aabf3);
    if (staticFlags != (uint *)0x0) {
        *(uint *)(thisObj + 0x30) = *(uint *)(thisObj + 0x30) | *staticFlags;
    }
    if ((*(byte *)(thisObj + 0x32) & 1) == 0) {
        if (*(int *)(thisObj + 0x20) != 0) {
            getGameManager();
            setupStateTimer(thisObj + 0x2c);          // +0x2c internal timer/state field
            *(uint *)(thisObj + 0x30) = *(uint *)(thisObj + 0x30) | 2;
        }
        if ((*(int *)(thisObj + 0x20) != 0) && (int owner = getGameManager(), owner != 0)) {
            *(int *)(thisObj + 0x38) = owner;          // +0x38 pointer to some data (animation?)
            *(uint *)(thisObj + 0x34) = (uint)*(byte *)(owner + 0xd8); // +0x34 copied value
            playAnimation(7, 1, 0);                    // animation with ID 7, speed=1, loop=0
            *(short *)(owner + 0x2a) = 7;              // set animation index on owner
        }
    }
    *(undefined4 *)(thisObj + 0x4c) = 0;               // clear timer/counter fields
    *(undefined4 *)(thisObj + 0x48) = 0;
    *(undefined4 *)(thisObj + 0x44) = 0;
    *(undefined4 *)(thisObj + 0x40) = 0;
}