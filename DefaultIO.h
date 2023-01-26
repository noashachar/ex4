#ifndef EX4_DEFAULTIO_H
#define EX4_DEFAULTIO_H

#include <string>

class DefaultIO {
public:
    virtual std::string read() = 0;
    virtual void write(std::string msg) = 0;

    virtual ~DefaultIO() = default;
};


// there's no .cpp file for this class, because its functions are virtual;
// the implementors will add their .cpp code


#endif //EX4_DEFAULTIO_H
