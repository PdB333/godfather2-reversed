// FUNC_NAME: UIScreen::initialize
// Address: 0x0041c9e0
// Role: Initialization sequence for a UI screen object, performing base class init,
// global registration, and deriving from parent parameters.
// Called functions:
//   0x0041ad20 - Base class constructor/init
//   0x00491090 - Global screen manager registration
//   0x004196d0 - Derived class initialization with flags and parent

void __thiscall UIScreen::initialize(uint flags, UIScreen* parent)
{
    // Call base class initialization (likely sets up vtable and basic members)
    this->baseInit(flags);

    // Register this screen in the global screen manager (e.g., for update/draw callbacks)
    Global::registerScreen();

    // Perform derived-specific setup, using flags and parent pointer
    this->setupFromParent(flags, parent);

    return;
}