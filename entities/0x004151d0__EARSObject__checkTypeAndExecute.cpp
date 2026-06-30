// FUNC_NAME: EARSObject::checkTypeAndExecute
int EARSObject::checkTypeAndExecute(void) {
    int typeId = *(int *)(this + 0x2c);                // m_typeId
    if (typeId == DAT_0110ac04) {                      // compare to global script type constant
        int *result = (int *)(**(code **)(**(int **)(*(int *)(this + 0x8) + 0x8) + 0x24))(); // get executor from manager chain
        if (result != (int *)0x0) {
            return (**(code **)(*result + 0x58))();    // call virtual Execute() on script executor
        }
    }
    return typeId;
}