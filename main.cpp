//
// Created by Alex on 8/26/2020.
//

#include "parser.h"
#include "input.h"
#include "compiler.h"
int main() {
    const char *string =
            "int main(int value) {"
            "  open();"
            "  return 10;"
            "}"
            "void open() {"
            ""
            "}"
            "";
    Parser<StringIter<>> parser;
    parser.reset(string);
    parser.parse();
    std::cout << parser.value().dump(4) << std::endl;

    Compiler compiler;
    compiler.compile(parser.value(), "module");

    return 0;
}
