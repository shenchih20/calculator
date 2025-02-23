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
        std::weak_ptr<AstNode> node;

    public:
        UnaryOpNode(char oper, std::weak_ptr<AstNode>node) : oper(oper), node(node)
        {

        }

        virtual double eval() override
        {
            auto value = node.lock()->eval();
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
        std::weak_ptr<AstNode> last;
        std::weak_ptr<AstNode> rast;

    public:
        BinaryOpNode(std::weak_ptr<AstNode> last,
                     const char oper,
                     std::weak_ptr<AstNode> rast) : last(last), oper(oper), rast(rast)
        {
        }

        virtual double eval() override
        {
            auto lv = last.lock()->eval();
            auto rv = rast.lock()->eval();

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
        std::list<std::shared_ptr<AstNode>> node_list;
    
    public:
        AstCreator() = default;        
        AstCreator(const AstCreator&) = delete;
        AstCreator& operator = (const AstCreator&) = delete;

        void Clear()
        {
            node_list.clear();
        }

        std::weak_ptr<AstNode> Number(double value)
        {
            auto node = std::make_shared<NumberNode>(value);
            node_list.push_back(node);
            return node;
        }

        std::weak_ptr<AstNode> UnaryOp(char oper, std::weak_ptr<AstNode> ast)
        {
            auto node = std::make_shared<UnaryOpNode>(oper, ast);
            node_list.push_back(node);
            return node;
        }

        std::weak_ptr<AstNode> BinaryOp(std::weak_ptr<AstNode> last, char oper, std::weak_ptr<AstNode> rast)
        {
            auto node = std::make_shared<BinaryOpNode>(last, oper, rast);
            node_list.push_back(node);
            return node;
        }
    };

}