#pragma once

#include <libconfig.h++>

using namespace libconfig;

class config_base
{
public:
    config_base(std::string filename);
    
protected:
    Config cfg;
};