//
// Created by Alex on 8/27/2020.
//

#ifndef HEILANG_CODEGEN_H
#define HEILANG_CODEGEN_H

#include "visitor.h"
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class CodeGen : public Walker<Value *> {
public:
    IRBuilder<> &builder;
    CodeGen(IRBuilder<> &builder) : builder(builder) {}
    Value *walk_number(json &node) override {
        return builder.getInt32(std::stol(node["value"].get<std::string>()));
    }
};


#endif //HEILANG_CODEGEN_H
