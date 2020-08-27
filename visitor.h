//
// Created by Alex on 8/26/2020.
//

#ifndef HEILANG_VISITOR_H
#define HEILANG_VISITOR_H
#include <iostream>
#include <functional>
#include "json.hpp"
#define ASTList(v)  v(program)   \
                    v(class)     \
                    v(fielddef)  \
                    v(fundef)    \
                    v(param)     \
                    v(vardef)    \
                    v(stmts)     \
                    v(return)    \
                    v(continue)  \
                    v(break)     \
                    v(if)        \
                    v(while)     \
                    v(do_while)  \
                    v(switch)    \
                    v(cases)     \
                    v(case)      \
                    v(assign)    \
                    v(binary)    \
                    v(variable)  \
                    v(dot)       \
                    v(array)     \
                    v(invoke)    \
                    v(number)    \
                    v(string)    \
                    v(char)      \
                    v(arg_list)
using json = nlohmann::json;
template <class Value>
class Walker {
    using walker_func = std::function<Value(Walker *, json &)>;
    static std::map<std::string, walker_func> functions;
public:
    virtual Value walk(json &node);
    virtual void error(json &node) {}
#define AddVisitor(kind) virtual Value walk_##kind(json &node) { return Value(); }
    ASTList(AddVisitor)
#undef  AddVisitor
};
template <class Value>
std::map<std::string, std::function<Value(Walker<Value> *, json &)>> Walker<Value>::functions = {
#define AddVisitor(kind) {#kind, &Walker<Value>::walk_##kind},
        ASTList(AddVisitor)
#undef  AddVisitor
};
template<class Value>
Value Walker<Value>::walk(json &node) {
    if (node.count("kind")) {
        return functions[node["kind"]](this, node);
    } else {
        if (!node.is_null()) {
            error(node);
        }
        return Value();
    }
};

class Visitor : public Walker<void> {
    inline void walk_values(json &node) {
        for (auto &item : node) {
            walk(item);
        }
    }
public:
    void walk(json &node) override {
        try {
            Walker::walk(node);
        } catch (...) {
            error(node);
        }
    }
    void error(json &node) override;
    void walk_program(json &node) override;
    void walk_array(json &node) override;
    void walk_fundef(json &node) override;
    void walk_return(json &node) override;
    void walk_if(json &node) override;
    void walk_vardef(json &node) override;
    void walk_do_while(json &node) override;
    void walk_stmts(json &node) override;
    void walk_while(json &node) override;
    void walk_class(json &node) override;
    void walk_binary(json &node) override;
    void walk_assign(json &node) override;
    void walk_invoke(json &node) override;
    void walk_dot(json &node) override;
    void walk_arg_list(json &node) override;

};

#endif //HEILANG_VISITOR_H
