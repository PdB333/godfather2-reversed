// FUNC_NAME: SomeClass::initializeSubComponents
void __fastcall SomeClass::initializeSubComponents(int thisPtr)
{
    // Allocate first sub-component and store at +0x10
    *(void**)(thisPtr + 0x10) = FUN_0060a380();  // returns a pointer to some object

    // Allocate second sub-component using a global factory, store at +0x14
    *(void**)(thisPtr + 0x14) = FUN_0060a2e0(&PTR_DAT_0110a37c);  // PTR_DAT_0110a37c is probably a static factory or config

    // Finalize initialization (possibility: initialize engine-level subsystem or finish setup)
    FUN_006127d0();
}