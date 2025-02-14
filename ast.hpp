#pragma once
#include <list>
#include <memory>

namespace calc
{
    class AstNode
    {
    public:
        virtual double eval() = 0;
    };

    class NumberNode : public AstNode
    {
    private:
        double value = 0;

    public:
        NumberNode(double value) : value(value) {}

        virtual double eval() override { return value; }
    };

    class UnaryOpNode : public AstNode
    {
    private:
        char oper;
        AstNode* node;

    public:
        UnaryOpNode(char oper, AstNode *node) : oper(oper), node(node)
        {

        }

        virtual double eval() override
        {
            auto value = node->eval();
            switch(oper)
            {
            case '+' : return value;
            case '-' : return (0 - value);                                        
            }

            return 0;
        }

    };

    class BinaryOpNode : public AstNode
    {
    private:
        const char oper;
        AstNode* last;
        AstNode* rast;

    public:
        BinaryOpNode(AstNode* last,
                     const char oper,
                     AstNode* rast) : last(last), oper(oper), rast(rast)
        {
        }

        virtual double eval() override
        {
            auto lv = last->eval();
            auto rv = rast->eval();

            switch (oper)
            {
            case '+': return lv + rv;
            case '-': return lv - rv;
            case '*': return lv * rv;
            case '/': return lv / rv;
            }

            return 0;
        }
    };


  
    class AstCreator
    {
    private:
        std::list<AstNode*> node_list;
    
    public:
        AstCreator() = default;        
        AstCreator(const AstCreator&) = delete;
        AstCreator& operator = (const AstCreator&) = delete;

        void Clear()
        {
            for each(AstNode* node in node_list)
            {
                delete node;
            }

            node_list.clear();
        }

        AstNode* Number(double value)
        {
            auto node = new NumberNode(value);
            node_list.push_back(node);
            return node;
        }

        AstNode* UnaryOp(char oper, AstNode* ast)
        {
            auto node = new UnaryOpNode(oper, ast);
            node_list.push_back(node);
            return node;
        }

        AstNode* BinaryOp(AstNode* last, char oper, AstNode* rast)
        {
            auto node = new BinaryOpNode(last, oper, rast);
            node_list.push_back(node);
            return node;
        }
    };

}