#pragma once

#include "Statement.hpp"

#include "../expressions/Expression.hpp"

#include <string>
#include <vector>

namespace epsilon
{
    namespace parser
    {
        namespace statements
        {
            class IfStatement : public Statement
            {

            public:

                /*!
                 * \param trueStatements  The list of statements to be executed if the expression is true.
                 * \param falseStatements The list of statements to be executed if the expression is false, i.e. an else block.
                 */
                inline IfStatement(expressions::Expression* expression,
                                   const std::vector<Statement*>& trueStatements,
                                   const std::vector<Statement*>& falseStatements)
                {

                    expression->grab();

                    m_expression = expression;

                    for(unsigned int i=0; i<trueStatements.size(); i++)
                    {
                        trueStatements[i]->grab();
                        m_trueStatements.push_back(trueStatements[i]);
                    }

                    for(unsigned int i=0; i<falseStatements.size(); i++)
                    {
                        falseStatements[i]->grab();
                        m_falseStatements.push_back(falseStatements[i]);
                    }
                }

                ~IfStatement()
                {
                    m_expression->drop();

                    for(unsigned int i=0; i<m_trueStatements.size(); i++)
                        m_trueStatements[i]->drop();

                    for(unsigned int i=0; i<m_falseStatements.size(); i++)
                        m_falseStatements[i]->drop();
                }

                Statement::Type getStatementType() const
                {
                    return Type::If;
                }

                inline const expressions::Expression* getExpression() const { return m_expression; }

                inline const std::vector<Statement*>& getTrueStatements() const { return m_trueStatements; }

                inline const std::vector<Statement*>& getFalseStatements() const { return m_falseStatements; }

            private:

                expressions::Expression* m_expression;
                std::vector<Statement*> m_trueStatements;
                std::vector<Statement*> m_falseStatements;

            };
        }
    }
}
