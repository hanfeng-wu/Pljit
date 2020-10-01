set(PLJIT_SOURCES
        # add your *.cpp files here
        test/TestRegisterFunction.cpp
        Pljit.cpp
        Pljit.hpp
        lex/Identifer.cpp lex/Identifer.hpp lex/Separator.cpp lex/Separator.hpp semantic/TreeNode/Function.cpp semantic/TreeNode/Function.hpp syntax/expression/Function_Def.cpp syntax/expression/Function_Def.hpp syntax/expression/Parameter_Dec.cpp syntax/expression/Parameter_Dec.hpp syntax/expression/Variable_Dec.cpp syntax/expression/Variable_Dec.hpp syntax/expression/Const_Dec.cpp syntax/expression/Const_Dec.hpp syntax/expression/Dec_List.cpp syntax/expression/Dec_List.hpp syntax/expression/Init_List.cpp syntax/expression/Init_List.hpp syntax/expression/Assign_Exp.cpp syntax/expression/Assign_Exp.hpp syntax/expression/Add_Exp.cpp syntax/expression/Add_Exp.hpp syntax/expression/Multi_Exp.cpp syntax/expression/Multi_Exp.hpp syntax/expression/Unary_Exp.cpp syntax/expression/Unary_Exp.hpp syntax/expression/Prim_Exp.cpp syntax/expression/Prim_Exp.hpp lex/Lexer.cpp lex/Lexer.hpp lex/LexToken.cpp lex/LexToken.hpp lex/Position.cpp lex/Position.hpp lex/Keyword.cpp lex/Keyword.hpp lex/Number.cpp lex/Number.hpp lex/test/TestLexer.cpp syntax/Node/NonTerminal.cpp syntax/Node/NonTerminal.hpp syntax/expression/Comp_Statement.cpp syntax/expression/Comp_Statement.hpp syntax/expression/Statement_List.cpp syntax/expression/Statement_List.hpp syntax/expression/Statement.cpp syntax/expression/Statement.hpp syntax/expression/Init_Dec.cpp syntax/expression/Init_Dec.hpp syntax/test/TestSyntax.cpp syntax/expression/Error.cpp syntax/expression/Error.hpp syntax/Node/SyntaxNode.hpp syntax/TreeVisitor.cpp syntax/TreeVisitor.hpp syntax/PrintDotVisitor.cpp syntax/PrintDotVisitor.hpp syntax/SyntaxParser.cpp syntax/SyntaxParser.hpp semantic/TreeNode/SemanticTreeNode.hpp semantic/AST.cpp semantic/AST.hpp semantic/TreeNode/SemanticStatement.cpp semantic/TreeNode/SemanticStatement.hpp semantic/TreeNode/Expression.cpp semantic/TreeNode/Expression.hpp semantic/Symbol.cpp semantic/Symbol.hpp semantic/ASTVisitor.hpp semantic/ASTPrintDotVisitor.cpp semantic/ASTPrintDotVisitor.hpp semantic/test/TestSemantic.cpp semantic/Evaluator.cpp semantic/Evaluator.hpp semantic/Optimizer.cpp semantic/Optimizer.hpp)

add_library(pljit_core ${PLJIT_SOURCES})
target_include_directories(pljit_core PUBLIC ${CMAKE_SOURCE_DIR})

add_clang_tidy_target(lint_pljit_core ${PLJIT_SOURCES})
add_dependencies(lint lint_pljit_core)

