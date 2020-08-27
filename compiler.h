//
// Created by Alex on 8/27/2020.
//

#ifndef HEILANG_COMPILER_H
#define HEILANG_COMPILER_H

#include "codegen.h"
struct Scope {
    std::map<std::string, Value *> symbols;
};

class Compiler : Visitor {
public:
    CompileContext context;
    Module *module = nullptr;
    CodeGen codegen;
    Compiler() : codegen(context) {}
    void compile(json &node, StringRef ModuleID = "") {
        module = new Module(ModuleID, context.context);
        walk(node);
        llvm::outs() << *module;
    }

private:
    void walk_fundef(json &node) override {
        auto *FT = (FunctionType *) context.checker.check(node);
        auto *F = Function::Create(FT, Function::ExternalLinkage, node["name"].get<std::string>(), module);
        auto *BB = BasicBlock::Create(context.context, "entrypoint", F);
        context.builder.SetInsertPoint(BB);
        int index = 0;
        for (auto &arg : F->args()) {
            auto &param = node["params"][index++];
            auto *alloc = context.builder.CreateAlloca(context.checker.check(param), nullptr);
            alloc->setName(param["name"].get<std::string>());
        }
        walk(node["block"]);
    }
    void walk_stmts(json &node) override {
        for (auto &item: node["value"]) {
            codegen.walk(item);
        }
    }

    void walk_binary(json &node) override {

    }

    void walk_return(json &node) override {}
    void walk_assign(json &node) override {

    }
};


#endif //HEILANG_COMPILER_H
