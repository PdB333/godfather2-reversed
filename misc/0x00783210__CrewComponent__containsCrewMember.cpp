// FUNC_NAME: CrewComponent::containsCrewMember

bool __thiscall CrewComponent::containsCrewMember(int this, int objectPtr)
{
    bool result = false;
    int currentBasePtr = 0;

    // Get the base pointer of the current crew member (if any)
    // The stored pointer is offset +0x48 into the sentient object
    if (*(int *)(this + 0x40) == 0) {
        currentBasePtr = 0;
    } else {
        currentBasePtr = *(int *)(this + 0x40) + -0x48;
    }

    // Check if the given object is the current crew member
    if (objectPtr != currentBasePtr) {
        // Only search the member list if flagged (bit 1 of flags at +0x74)
        if ((*(uint *)(this + 0x74) >> 1 & 1) != 0) {
            uint index = 0;
            if (*(uint *)(this + 0x68) != 0) {
                int **memberArray = *(int ***)(this + 100); // +0x64: array of pointers
                while (true) {
                    int memberBasePtr;
                    if (*memberArray == 0) {
                        memberBasePtr = 0;
                    } else {
                        memberBasePtr = *memberArray + -0x48; // convert field pointer to object base
                    }

                    if (memberBasePtr == objectPtr) {
                        break;
                    }

                    index++;
                    memberArray += 2; // each entry is 8 bytes (pointer + unused? or next pointer)
                    if (*(uint *)(this + 0x68) <= index) {
                        return result; // false
                    }
                }
                result = true;
            }
        }
        return result;
    }
    return true; // object matches current crew member
}