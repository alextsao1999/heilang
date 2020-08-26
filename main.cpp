//
// Created by Alex on 8/26/2020.
//

#include "parser.h"
#include "input.h"
#include "visitor.h"
int main() {
    const char *string =
            "int main() {"
            "  open();"
            "  return 10;"
            "}";
    Parser<StringIter<>> parser;
    parser.reset(string);
    parser.parse();
    std::cout << parser.value().dump(4) << std::endl;
    TestVisitor visitor;
    visitor.visit(parser.value());

    return 0;
}
