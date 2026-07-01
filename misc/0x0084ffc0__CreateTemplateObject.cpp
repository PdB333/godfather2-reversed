// FUNC_NAME: CreateTemplateObject
// Function at 0x0084ffc0 creates an object from a resource hash template
// Calls resource manager functions to instantiate and initialize

int __cdecl CreateTemplateObject(unsigned int param1)
{
    int objPtr;

    // Register or log debug identifier for this template
    FUN_004da270("XTHALE1387_C90A01A_DA2FB58_v3");

    // Allocate object from hash (template ID 0xfe16702f, flags 0, extra 0)
    objPtr = FUN_00404280(0xfe16702f, 0, 0);

    if (objPtr != 0) {
        // Set type index or initializer (type 2) with given parameter
        FUN_004035c0(objPtr, 2, param1);
    }

    return objPtr;
}