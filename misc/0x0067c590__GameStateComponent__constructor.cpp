// FUNC_NAME: GameStateComponent::constructor
// Address: 0x0067c590

class GameStateComponent {
public:
    void* vtable; // +0x00 (set to PTR_FUN_00d57758)
    int someId;   // +0x04 (constructor parameter)
    unsigned char flags[3]; // +0x08 (zeroed bytes)
    int field0x0C; // +0x0C
    int field0x10; // +0x10
    int field0x14; // +0x14
    int field0x18; // +0x18
    int field0x1C; // +0x1C
    int field0x20; // +0x20
    int field0x24; // +0x24
    int field0x28; // +0x28
    // total size 0x2C (44 bytes)

    void __thiscall constructor(int param);
};

void __thiscall GameStateComponent::constructor(GameStateComponent* this, int param)
{
    this->vtable = &GameStateComponent_vtable; // PTR_FUN_00d57758
    this->someId = param;
    this->flags[0] = 0;
    this->flags[1] = 0;
    this->flags[2] = 0;
    this->field0x0C = 0;
    this->field0x10 = 0;
    this->field0x14 = 0;
    this->field0x18 = 0;
    this->field0x1C = 0;
    this->field0x20 = 0;
    this->field0x24 = 0;
    this->field0x28 = 0;
}