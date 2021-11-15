#include "config_base.h"
#include <iostream>

config_base::config_base(std::string filename)
{
    // Read the file. If there is an error, report it and exit.
    try
    {
        this->cfg.readFile(filename.c_str());
    }
    catch( const libconfig::FileIOException &fioex)
    {
        std::cerr << "I/O error while reading file." << std::endl;
        
    }
    catch( const libconfig::ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        
    }
}