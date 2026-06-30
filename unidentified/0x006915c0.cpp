// Function at 0x006915c0: Common two-phase initialization wrapper called by various constructors/init functions.
// Calls two sub-initialization functions in sequence.
// FUNC_NAME: initializeComponents
void __thiscall initializeComponents(void* thisObject) {
    initPhase1(thisObject);
    initPhase2(thisObject);
}