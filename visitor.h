//
// Created by Alex on 8/26/2020.
//

#ifndef HEILANG_VISITOR_H
#define HEILANG_VISITOR_H
#include <functional>
#include "json.hpp"
class Visitor;
using visit_func = std::function<void(Visitor *, Value &)>;
extern std::map<std::string, visit_func> vistor_functions;
#define ASTList(v)  v(program) \
                    v(class)   \
                    v(fielddef)\
                    v(fundef)  \
                    v(params)  \
                    v(param)   \
                    v(vardef)  \
                    v(stmts)   \
                    v(return)  \
                    v(continue)\
                    v(break)   \
                    v(if)      \
                    v(while)   \
                    v(do_while)\
                    v(switch)  \
                    v(cases)   \
                    v(case)    \
                    v(assign)  \
                    v(binary)  \
                    v(variable)\
                    v(dot)     \
                    v(array)   \
                    v(invoke)  \
                    v(literal) \
                    v(arg_list)

class Visitor {
public:
    Visitor() {}
    virtual void visit(Value &value) {
        if (value.is_null()) {
            return;
        }
        if (vistor_functions.count(value["kind"])) {
            vistor_functions[value["kind"]](this, value);
        } else {
            error(value);
        }
    }
    virtual void error(Value &value) {
        std::cout << "Unknow Value " << value << std::endl;
    }
#define AddVisitor(kind) virtual void visit_##kind(Value &value) {}
        ASTList(AddVisitor)
#undef  AddVisitor
};

std::map<std::string, visit_func> vistor_functions = {
#define AddVisitor(kind) {#kind, &Visitor::visit_##kind},
        ASTList(AddVisitor)
#undef  AddVisitor
};

class TestVisitor : public Visitor {
public:
    void visit(Value &value) override {
        try {
            Visitor::visit(value);
        } catch (std::exception &e) {
            std::cout << "error:" << e.what() << " json:" << value << std::endl;
        }
    }
    void visit_program(Value &value) override {
        for (auto &item : value["value"]) {
            visit(item);
        }
    }
    void visit_fundef(Value &value) override {
        //std::cout << "function:" << value["name"] << std::endl;
        visit(value["block"]);
    }
    void visit_stmts(Value &value) override {
        for (auto &item : value["value"]) {
            visit(item);
        }
    }
    void visit_return(Value &value) override {
        //std::cout << "return" << std::endl;
    }

};
#endif //HEILANG_VISITOR_H
