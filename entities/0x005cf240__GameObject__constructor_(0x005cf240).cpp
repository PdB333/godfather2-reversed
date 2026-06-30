// FUNC_NAME: GameObject::constructor (0x005cf240)
// Constructor for a base GameObject, initializes three member fields to zero and calls sub-initializers.
// Fields at offsets: +0x00 (int), +0x04 (int), +0x0C (int) are zeroed.

class GameObject
{
public:
    int field_0;   // +0x00
    int field_4;   // +0x04
    int field_0C;  // +0x0C
    // ... other members ...

    void __thiscall constructor();
};

// Sub-initializers called in order:
void __thiscall baseInit(GameObject* this);       // FUN_00670350
void __cdecl staticInitA();                      // FUN_006710b0
void __cdecl staticInitB();                      // FUN_00671ab0
void __thiscall internalInit(GameObject* this);  // FUN_006726e0

extern void (*g_globalCallback)();               // DAT_0119caf8

void GameObject::constructor()
{
    baseInit(this);
    staticInitA();
    staticInitB();
    this->field_4 = 0;
    internalInit(this);
    this->field_0 = 0;
    this->field_0C = 0;
    g_globalCallback();
}