// FUNC_NAME: GameObject::initGameObject
void __thiscall GameObject::initGameObject(GameObject* this) {
    // Set initial vtable pointers (base class vtables for multiple inheritance)
    *(void**)this = &PTR_FUN_00d80834;  // +0x00: first vtable
    *(void**)&this->field_0x10 = &PTR_LAB_00d806d8;  // +0x10 (offset 0x10 from base? Actually param_1[4] is offset 0x10)
    // Wait, param_1[4] means offset 0x10 bytes. Let's correct.
    // Actually param_1 is a pointer to undefined4, so param_1[4] is offset 4*4=0x10.
    // We need to be careful with offsets.
    // Let's use this->field_0x10, etc. But better to use direct pointer arithmetic.
    // For clarity, use offsets in comments.

    // Set vtable pointers for intermediate base classes
    *(void**)((char*)this + 0x10) = &PTR_LAB_00d806d8;  // +0x10
    *(void**)((char*)this + 0x4C) = &PTR_LAB_00d806c8;  // +0x4C (param_1[0x13] = 0x13*4=0x4C)
    *(void**)((char*)this + 0x58) = &PTR_LAB_00d806c4;  // +0x58 (0x16*4=0x58)
    *(void**)((char*)this + 0x60) = &PTR_LAB_00d806c0;  // +0x60 (0x18*4=0x60)
    *(void**)((char*)this + 0x64) = &PTR_LAB_00d80660;  // +0x64 (0x19*4=0x64)
    *(void**)((char*)this + 0x68) = &PTR_LAB_00d805f8;  // +0x68 (0x1A*4=0x68)

    // Check if a subobject at offset +0x1A0 exists and clear it
    if (*(void**)((char*)this + 0x1A0) != nullptr) {  // +0x1A0 = 0x68 * 4
        clearSubObject((void*)((char*)this + 0x1A0));  // FUN_004daf90 - likely frees or resets the subobject
    }

    // Set second set of vtable pointers (probably for derived class)
    *(void**)((char*)this + 0x10) = &PTR_FUN_00d80008;  // +0x10
    *(void**)((char*)this + 0x4C) = &PTR_LAB_00d7fff8;  // +0x4C
    *(void**)((char*)this + 0x58) = &PTR_LAB_00d7fff4;  // +0x58
    *(void**)((char*)this + 0x60) = &PTR_LAB_00d7fff0;  // +0x60
    *(void**)((char*)this + 0x64) = &PTR_LAB_00d7ff90;  // +0x64
    *(void**)((char*)this + 0x68) = &PTR_LAB_00d7ff28;  // +0x68

    // Global initialization call
    someGlobalInit();  // FUN_0046ea20 - possibly engine or subsystem init

    // Set final vtable for this class
    *(void**)this = &PTR_FUN_00e32808;  // +0x00: most derived vtable

    // Clear linked list of child nodes (starting from offset +0x04)
    Node* currentNode = (Node*)((char*)this + 0x04);  // +0x04: pointer to head node (next pointer)
    while (currentNode != nullptr) {
        Node* nextNode = (Node*)currentNode->next;  // Node's next at +0x04
        currentNode->next = nullptr;
        currentNode->data = nullptr;  // Node's data at +0x00
        currentNode = nextNode;
    }
}