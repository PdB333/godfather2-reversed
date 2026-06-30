// FUNC_NAME: ModalDialog::runModalLoop

void ModalDialog::runModalLoop(int param_2) {
    uiDialogInit(param_2);
    uiDialogSetIdentifier(param_2, 0x14064116);

    while (!uiDialogIsFinished()) {
        uiDialogProcessEvents();

        int state = uiDialogGetState();
        if (state == 0) {
            uiDialogProcessEvents();
            int data = uiDialogGetData();
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x50) = data; // +0x50: result storage
        } else if (state == 1) {
            int* controlPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x58); // +0x58: control pointer
            uiDialogProcessEvents(controlPtr);
            uiDialogControlUpdate(controlPtr);
        } else if (state == 2) {
            int* controlData = uiDialogProcessEvents(); // returns control data pointer
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x68) = controlData[2]; // +0x68: store value from control data offset 8
        }

        uiDialogEndFrame();
    }
}