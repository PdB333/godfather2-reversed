// Function at 0x00704a00: Getter for pointer to crew component (NPCCrewComponent or PlayerCrewLeaderComponent) stored at offset +0x98.
int * __thiscall Sentient::getCrewComponent(Sentient *this) {
    return *(int **)((char *)this + 0x98);
}