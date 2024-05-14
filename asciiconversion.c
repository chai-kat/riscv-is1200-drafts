int atoi(char* str) {
    int sign = 1;

    // discard initial whitespace
    while(*(str) == ' ') {
        str++;
    }

    if (*str == '+') {
        str++;
    }
    else if (*str == '-') {
        sign = -1;
        str++;
    }

    int res = 0;
    while (*str > '0' && *str < '9') {
        res = (res * 10) + (*str - '0');
    }

    return res*sign;
}

long atol(char* str) {
    long sign = 1;

    // discard initial whitespace
    while(*(str) == ' ') {
        str++;
    }

    if (*str == '+') {
        str++;
    }
    else if (*str == '-') {
        sign = -1;
        str++;
    }

    long res = 0;
    while (*str > '0' && *str < '9') {
        res = (res * 10) + (*str - '0');
    }

    return res*sign;
}

long long atoll(char* str) {
    long long sign = 1;

    // discard initial whitespace
    while(*(str) == ' ') {
        str++;
    }

    if (*str == '+') {
        str++;
    }
    else if (*str == '-') {
        sign = -1;
        str++;
    }

    long long res = 0;
    while (*str > '0' && *str < '9') {
        res = (res * 10) + (*str - '0');
    }

    return res*sign;
}

float atof(char* str) {
    float res = 0.0;
    
    return res;
}