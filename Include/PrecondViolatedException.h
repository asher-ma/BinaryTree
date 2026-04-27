#ifndef _PRECOND_VIOLATED_EXCEP_H_
#define _PRECOND_VIOLATED_EXCEP_H

#include <stdexcept>
#include <string>

using namespace std;

class PrecondViolatedExcep: public logic_error {
    public :
        PrecondViolatedExcep(const string& message = "");
    }; // end PrecondViolatedExcep

#include "../src/PrecondViolatedException.cpp"

#endif