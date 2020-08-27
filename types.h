//
// Created by Alex on 8/27/2020.
//

#ifndef HEILANG_TYPE_CHECK_H
#define HEILANG_TYPE_CHECK_H

#include "visitor.h"

#include "llvm/IR/IRBuilder.h"
using namespace llvm;

class TypeChecker : Walker<Type *> {
    LLVMContext &context;
    std::map<std::string, Type *> names = {
            {"void",   IntegerType::getVoidTy(context)},
            {"size",   IntegerType::getInt64Ty(context)},
            {"char",   IntegerType::getInt8Ty(context)},
            {"byte",   IntegerType::getInt8Ty(context)},
            {"short",  IntegerType::getInt16Ty(context)},
            {"int",    IntegerType::getInt32Ty(context)},
            {"int64",  IntegerType::getInt64Ty(context)},
            {"float",  IntegerType::getFloatTy(context)},
            {"double", IntegerType::getDoubleTy(context)},
            {"bool",   IntegerType::getInt1Ty(context)},
    };
    Type *find_type(const std::string &string) {
        return names[string];
    }
public:
    TypeChecker(LLVMContext &context) : context(context) {}
    Type *check(json &node) {
        return walk(node);
    }
private:
    Type *walk_fundef(json &node) override {
        auto *Result = find_type(node["type"]);
        std::vector<Type *> params;
        for (auto &item : node["params"]) {
            params.emplace_back(walk(item));
        }
        auto *FT = FunctionType::get(Result, params, false);
        return FT;
    }
    Type *walk_param(json &node) override {
        return find_type(node["type"]);
    }
    Type *walk_array(json &node) override {

    }

    Type *walk_char(json &node) override {
    }

    Type *walk_binary(json &node) override {
    }

    Type *walk_assign(json &node) override {
    }

    Type *walk_invoke(json &node) override {
    }

    Type *walk_dot(json &node) override {
    }

    Type *walk_number(json &node) override {

    }
};

#endif //HEILANG_TYPE_CHECK_H
