//
// Created by Alex on 8/27/2020.
//

#include "visitor.h"

void Visitor::walk_program(json &node) {
    walk_values(node["value"]);
}

void Visitor::walk_array(json &node) {
    walk(node["lhs"]);
    walk(node["field"]);
}

void Visitor::walk_fundef(json &node) {
    walk_values(node["params"]);
    walk(node["block"]);
}

void Visitor::walk_return(json &node) {
    walk(node["value"]);
}

void Visitor::walk_if(json &node) {
    walk(node["condition"]);
    walk(node["then"]);
    walk(node["else"]);
}

void Visitor::walk_vardef(json &node) {
    walk(node["init"]);
}

void Visitor::walk_do_while(json &node) {
    walk(node["condition"]);
    walk(node["body"]);
}

void Visitor::walk_stmts(json &node) {
    walk_values(node["value"]);
}

void Visitor::walk_while(json &node) {
    walk(node["condition"]);
    walk(node["body"]);
}

void Visitor::walk_class(json &node) {
    //walk_values(node["member"]);
    walk_values(node["body"]);
}

void Visitor::walk_binary(json &node) {
    walk(node["left"]);
    walk(node["right"]);
}

void Visitor::walk_assign(json &node) {
    walk(node["left"]);
    walk(node["right"]);
}

void Visitor::walk_invoke(json &node) {

}

void Visitor::walk_dot(json &node) {
    walk(node["lhs"]);
}

void Visitor::walk_arg_list(json &node) {
    walk_values(node["value"]);
}

void Visitor::error(json &node) {
    std::cout << "Unknow Value " << node << std::endl;
}
