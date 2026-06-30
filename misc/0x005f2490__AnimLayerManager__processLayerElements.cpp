// FUNC_NAME: AnimLayerManager::processLayerElements
void __thiscall AnimLayerManager::processLayerElements(void) {
    byte groupCount = *(byte*)(this + 0x02);   // number of groups (e.g., animation layers)
    byte elementCount = *(byte*)(this + 0x03); // elements per group (e.g., blend weights per bone)
    short* tableBase = *(short**)(this + 0x2C); // base pointer to 16-bit aligned table
    unsigned short* maxIndexPtr = **(unsigned short***)(this + 0x28); // pointer to "max index" variable (e.g., current animation frame count)

    // Loop over groups
    for (byte g = 0; g < groupCount; g++) {
        // Pointer to start of the current group's elements (each element is 8 bytes = 4 shorts)
        short* groupStart = tableBase + (elementCount * g * 4);

        // Loop over elements within the group
        for (byte e = 0; e < elementCount; e++) {
            short* elem = groupStart + (e * 4); // element: [value, type, param_low, param_high]

            short value = elem[0];        // first 16-bit field (e.g., weight or ID)
            short type = elem[1];         // type code (1,2,3,4)
            int param = *(int*)(elem + 2); // 32-bit parameter (e.g., blend value)

            switch (type) {
            case 1: // Constant initialization: if value == 0, set to 1000
                if (value == 0) {
                    elem[0] = 1000;
                }
                break;

            case 2: // Clamped indexing: check against max index, then clamp param to 0x7f
            case 3: // Same index check without clamping param
                {
                    unsigned short maxVal = *maxIndexPtr;
                    // The byte at offset 3 (high byte of 'type' field) is used as an index
                    char idx = *(char*)((int)elem + 3);
                    if ((int)maxVal <= (int)idx) {
                        if (maxVal == 0) {
                            *(char*)((int)elem + 3) = 0;
                        } else {
                            *(char*)((int)elem + 3) = (char)(maxVal - 1);
                        }
                    }
                    if (type == 2) {
                        // Clamp param to 0x7f (signed short max)
                        if (param > 0x7f) {
                            elem[2] = 0x7f;
                            elem[3] = 0;
                        }
                    }
                }
                break;

            case 4: // Negative param reset
                if (param < 0) {
                    elem[2] = 0;
                    elem[3] = 0;
                }
                break;
            }
        }
    }
}