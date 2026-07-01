// FUNC_NAME: GameObject::constructor
// Address: 0x00867670 - Reconstructed constructor for a game object with optional secondary initialization.
int __thiscall GameObject::constructor(GameObject *this, byte flag)
{
    // Base initialization (likely base class constructor or common setup)
    this->baseInit();  // FUN_00867480
    // If low bit of flag is set, perform additional initialization
    if ((flag & 1) != 0) {
        this->specialInit();  // FUN_009c8eb0
    }
    return (int)this;
}