// FUNC_NAME: Apt::setColor
// Function address: 0x0059f390
// Source: ..\source\Apt\Apt.cpp
// Sets the color (r,g,b) with alpha/amount for an Apt element or array of elements.
// Returns true if successful.

bool Apt::setColor(const char* elementName, float r, float g, float b, float amount)
{
    // Assertions for initialization and bounds
    if (!DAT_012055b0) {
        // Debug assertion: bAptIsInitialized
        assert("bAptIsInitialized", "..\\source\\Apt\\Apt.cpp", 0x281, 2);
    }
    assert("r >= 0.0f && r <= 255.f", "..\\source\\Apt\\Apt.cpp", 0x282, 2, r >= 0.0f && r <= 255.0f);
    assert("g >= 0.0f && g <= 255.f", "..\\source\\Apt\\Apt.cpp", 0x283, 2, g >= 0.0f && g <= 255.0f);
    assert("b >= 0.0f && b <= 255.f", "..\\source\\Apt\\Apt.cpp", 0x284, 2, b >= 0.0f && b <= 255.0f);
    assert("amount >= 0.f && amount <= 100.f", "..\\source\\Apt\\Apt.cpp", 0x285, 2, amount >= 0.0f && amount <= 100.0f);

    bool result = false;
    int aptContext = getAptContext(); // FUN_0059e2f0
    int element = findElement(aptContext, 0, elementName, 1, 1); // FUN_005aea60

    if (element != 0) {
        // Check if it's a single element
        if (isSingleElement(0)) { // FUN_0059c5c0
            int elementData = getSingleElementData(); // FUN_0059c3b0
            if (elementData == 0) {
                // Debug assertion: pCIH
                assert("pCIH", "..\\source\\Apt\\Apt.cpp", 0x28e, 2);
                triggerAssertion(); // FUN_0059bf00
            }
            float alpha = 100.0f - amount; // DAT_00e2b050 - param_5
            // Set alpha component
            setColorComponent(); // FUN_005b5d20
            *(uint8*)(elementData + 100) = 0; // Mark as dirty? +0x64
            *(float*)(*(int*)(elementData + 0x50) + 0x20) = alpha; // +0x50 -> color struct, +0x20 = alpha
            float scaledAlpha = alpha * DAT_00e44640; // Some scale factor
            *(float*)(elementData + 0x24) = scaledAlpha; // +0x24 = some field
            setColorComponent();
            *(uint8*)(elementData + 100) = 0;
            *(float*)(*(int*)(elementData + 0x50) + 0x24) = alpha; // +0x24 in color struct?
            *(float*)(elementData + 0x28) = scaledAlpha;
            setColorComponent();
            *(float*)(*(int*)(elementData + 0x50) + 0x28) = alpha;
            float scale = DAT_00e44640;
            *(float*)(elementData + 0x2c) = scaledAlpha;
            amount = amount * DAT_00e2e780; // Another scale
            *(float*)(elementData + 0x14) = amount * r * scale; // +0x14 = red
            *(float*)(elementData + 0x18) = amount * g * scale; // +0x18 = green
            *(float*)(elementData + 0x1c) = amount * b * scale; // +0x1c = blue
            *(uint8*)(elementData + 100) = 1; // Mark as updated
            return true;
        }
        // Check if it's an array element
        if (isArrayElement()) { // FUN_0059c500
            int arrayData = getArrayData(); // FUN_0059c450
            if (arrayData == 0) {
                // Debug assertion: pArray
                assert("pArray", "..\\source\\Apt\\Apt.cpp", 0x29e, 2);
                triggerAssertion();
            }
            int arraySize = getArraySize(arrayData, aptContext); // FUN_005ab7b0
            if (arraySize != 0) {
                result = true;
                int count = (int)getArrayCount(); // FUN_005a8fe0
                for (int i = 0; i < count; i++) {
                    int elementPtr = DAT_0119cbbc; // Default value
                    if (i >= 0 && i < *(int*)(arrayData + 0x54) && *(int*)(*(int*)(arrayData + 0x4c) + i * 4) != 0) {
                        elementPtr = *(int*)(*(int*)(arrayData + 0x4c) + i * 4);
                    }
                    if (elementPtr != 0) {
                        char childName[260];
                        childName[0] = '\0';
                        getArrayElementName(childName, 0x100); // FUN_005a90a0
                        if (childName[0] != '\0') {
                            bool childResult = setColor(childName, r, g, b, amount);
                            if (!childResult || !result) {
                                result = false;
                            } else {
                                result = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}