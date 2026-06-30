// FUNC_NAME: mapBuildingTypeToSomeValue
// Function at 0x00711380 - Small dispatch/mapping function, likely related to building or crew type enum.
int mapBuildingTypeToSomeValue(int inputIndex) {
    int outputValue = 11; // default (0xB)
    switch(inputIndex) {
    case 2:
    case 3:
        return 9;
    case 4:
        outputValue = 2;
        break;
    }
    return outputValue;
}