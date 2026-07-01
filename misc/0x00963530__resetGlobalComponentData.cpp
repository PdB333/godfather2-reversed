// FUNC_NAME: resetGlobalComponentData
void resetGlobalComponentData(int index) {
    // Switch on component index to reset its global data block
    switch (index) {
        case 0:
            resetDataBlock(&gComponentData0, 0); // Equivalent to FUN_00402050(&DAT_011301c0, 0)
            break;
        case 1:
            resetDataBlock(&gComponentData1, 0); // DAT_011304d8
            break;
        case 2:
            resetDataBlock(&gComponentData2, 0); // DAT_01130448
            break;
        case 3:
            resetDataBlock(&gComponentData3, 0); // DAT_011302c8
            break;
        case 4:
            resetDataBlock(&gComponentData4, 0); // DAT_01130310
            break;
        case 5:
            resetDataBlock(&gComponentData5, 0); // DAT_01130208
            break;
        case 6:
            resetDataBlock(&gComponentData6, 0); // DAT_011302c0
            break;
        default:
            break;
    }
}