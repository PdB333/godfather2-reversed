// FUNC_NAME: SimManager::getSimNpcFlag
#include <cstdint>

uint8_t SimManager::getSimNpcFlag(void* param_1) {
    int* local_4;
    FUN_008ab770(&local_4, &param_1); // SimManager::getNpcFromHandle
    if (local_4 != nullptr) {
        FUN_008ab7d0(&local_4, &param_1); // validation or field offset adjustment
        return *(uint8_t*)(local_4 + 4); // +0x04 flag byte (e.g., active/inactive)
    }
    return 0; // default to false/0
}