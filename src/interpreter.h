
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "types.h"

extern VarMap varmap;

namespace Interpreter { void parse(const std::string& path); };

#endif