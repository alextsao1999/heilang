//
// Created by Alex on 8/27/2020.
//

#ifndef HEILANG_CODEGEN_H
#define HEILANG_CODEGEN_H

#include "visitor.h"
#include "types.h"
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class ErrorReport {
public:
    void report(const char *msg) {
        std::cout << msg;
    }
};

struct CompileContext {
    LLVMContext context;
    IRBuilder<> builder;
    TypeChecker checker;
    ErrorReport error;
    Value *bool_true = ConstantInt::getTrue(context);
    Value *bool_false = ConstantInt::getFalse(context);
    Type *i8 = IntegerType::getInt8Ty(context);
    Type *i32 = IntegerType::getInt32Ty(context);
    Type *i64 = IntegerType::getInt64Ty(context);
    Type *f32 = IntegerType::getFloatTy(context);
    Type *f64 = IntegerType::getDoubleTy(context);
    Type *b = IntegerType::getInt1Ty(context);
    Type *v = IntegerType::getVoidTy(context);
    CompileContext() : builder(context), checker(context) {}
};

class CodeGen : public Walker<Value *> {
public:
    CompileContext &context;
    CodeGen(CompileContext &context) : context(context) {}
    Value *walk_string(json &node) override {
        auto str = node["value"].get<std::string>();
        auto *global = context.builder.CreateGlobalString(str.substr(1, str.length() - 2));
        Value *zero = context.builder.getInt32(0);
        Value *idxs[] = {zero, zero};
        return context.builder.CreateInBoundsGEP(global, idxs);
    }
    Value *walk_number(json &node) override {
        return context.builder.getInt32(std::stol(node["value"].get<std::string>()));
    }
    Value *walk_binary(json &node) override {
        static std::map<std::tuple<std::string, int>, Instruction::BinaryOps> ops = {
                {std::pair("+", 0),  Instruction::BinaryOps::Add},
                {std::pair("-", 0),  Instruction::BinaryOps::Sub},
                {std::pair("*", 0),  Instruction::BinaryOps::Mul},
                {std::pair("/", 0),  Instruction::BinaryOps::SDiv},
                {std::pair("|", 0),  Instruction::BinaryOps::Or},
                {std::pair("<<", 0), Instruction::BinaryOps::Shl},
                {std::pair(">>", 0), Instruction::BinaryOps::LShr},
                {std::pair("+", 1),  Instruction::BinaryOps::FAdd},
                {std::pair("-", 1),  Instruction::BinaryOps::FSub},
                {std::pair("*", 1),  Instruction::BinaryOps::FMul},
                {std::pair("/", 1),  Instruction::BinaryOps::FDiv},
                {std::pair("/", 2),  Instruction::BinaryOps::UDiv},
        };

        auto op = node["op"].get<std::string>();
        return context.builder.CreateBinOp(
                ops[std::pair(op, 0)],
                walk(node["left"]),
                walk(node["right"]), "temp"
        );

    }

};


#endif //HEILANG_CODEGEN_H
