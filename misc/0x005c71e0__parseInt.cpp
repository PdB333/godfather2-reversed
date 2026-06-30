// FUNC_NAME: parseInt
int parseInt(char* str) {
    char* p = str;
    bool negative = false;
    int result = 0;

    // Skip leading whitespace
    while (*p != '\0' && _isspace((int)*p)) {
        p++;
    }

    // Handle sign
    if (*p == '+') {
        p++;
    } else if (*p == '-') {
        negative = true;
        p++;
    }

    // Parse digits
    while (*p != '\0' && _isdigit((int)*p)) {
        result = result * 10 + (*p - '0');
        p++;
    }

    if (negative) {
        result = -result;
    }

    return result;
}