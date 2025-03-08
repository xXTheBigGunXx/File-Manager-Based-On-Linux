#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <string>

class Authentication
{
public:
    static bool IsTextFile(const std::string& filesName);
};

#endif