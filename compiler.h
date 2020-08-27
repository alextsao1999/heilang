//
// Created by Alex on 8/27/2020.
//

#ifndef HEILANG_COMPILER_H
#define HEILANG_COMPILER_H

#include "codegen.h"
#include "types.h"

class Compiler : Visitor {
public:
    LLVMContext context;
    IRBuilder<> builder;
    Module *module = nullptr;
    CodeGen codegen;
    TypeChecker checker;
    Compiler() : builder(context), codegen(builder), checker(context) {}
    void compile(json &node, StringRef ModuleID = "") {
        module = new Module(ModuleID, context);
        walk(node);
        llvm::outs() << *module;

    }

private:
    void walk_fundef(json &node) override {
        auto *FT = (FunctionType *) checker.check(node);
        auto *F = Function::Create(FT, Function::ExternalLinkage, node["name"].get<std::string>(), module);
        auto *BB = BasicBlock::Create(context, "entrypoint", F);
        builder.SetInsertPoint(BB);
        int index = 0;
        for (auto &arg : F->args()) {
            auto &param = node["params"][index++];
            auto *alloc = builder.CreateAlloca(checker.check(param), nullptr);
            alloc->setName(param["name"].get<std::string>());
        }

    }

    void walk_assign(json &node) override {

    }
};


#endif //HEILANG_COMPILER_H
