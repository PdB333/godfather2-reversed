// FUNC_NAME: charClassCheck
uint __fastcall charClassCheck(int specifier, int testChar)
{
    int lowerSpec = _tolower(specifier);
    uint result;

    switch (lowerSpec) {
    case 'a':
        result = _isalpha(testChar);
        break;
    case 'c':
        result = _iscntrl(testChar);
        break;
    case 'd':
        result = _isdigit(testChar);
        break;
    case 'l':
        result = _islower(testChar);
        break;
    case 'p':
        result = _ispunct(testChar);
        break;
    case 's':
        result = _isspace(testChar);
        break;
    case 'u':
        result = _isupper(testChar);
        break;
    case 'w':
        result = _isalnum(testChar);
        break;
    case 'x':
        result = _isxdigit(testChar);
        break;
    case 'z':
        result = (uint)(testChar == 0);
        break;
    default:
        return (uint)(specifier == testChar); // exact match for unknown specifiers
    }

    // If original specifier is lowercase, return result; otherwise return inverted result.
    if (_islower(specifier) != 0) {
        return result;
    }
    return (uint)(result == 0);
}