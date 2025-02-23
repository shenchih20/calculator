#include "calc.lexer.hh"
#include "calc.parser.hh"
#include "calculator.hpp"
#include <sstream>

namespace calc
{
    Calculator::Calculator()
        : lexer_(new CalcLexer()),
          parser_(new CalcParser(*this)),
          error_(0)
    {
    }

    Calculator::~Calculator()
    {
        delete parser_;        
    }

    void Calculator::reset()
    {
        error_ = 0;
        creator_.Clear();
    }

    int Calculator::parse_string(std::string &str)
    {
        reset();
        
        str.append("\n");
        std::istringstream s(str);
        lexer_->switch_streams(&s, &std::cout);

        parser_->parse();
        
        return error_;
    }

    void Calculator::eval(std::weak_ptr<AstNode> node)
    {
        if(true == node.expired())
        {
            std::cout << "node is nullptr";
            return;
        }        

        std::cout << "\n\nResult : " << node.lock()->eval() << "\n\n";
    }

}
