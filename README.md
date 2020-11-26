# Pljit
Easy compiler that converts String to excutable functions with multithreading ability
using function in Pljit Pljit::registerFunction(const string& s) to register function with respect to the grammar of

function-definition = [ parameter-declarations ]

[ variable-declarations ]

[ constant-declarations ]

compound-statement

".".

parameter-declarations = "PARAM" declarator-list ";".

variable-declarations = "VAR" declarator-list ";".

constant-declarations = "CONST" init-declarator-list ";".

declarator-list = identifier { "," identifier }.

init-declarator-list = init-declarator { "," init-declarator }.

init-declarator = identifier "=" literal.

compound-statement = "BEGIN" statement-list "END".

statement-list = statement { ";" statement }.

statement = assignment-expression

| "RETURN" additive-expression.

assignment-expression = identifier ":=" additive-expression.

additive-expression = multiplicative-expression

[ ( "+" | "-" ) additive-expression ].

multiplicative-expression = unary-expression

[ ( "*" | "/" ) multiplicative-expression ].

unary-expression = [ "+" | "-" ] primary-expression.

primary-expression = identifier

| literal

| "(" additive-expression ")".


for Example

PARAM width, height, depth;

VAR volume;

CONST density = 2400;

BEGIN

volume := width * height * depth;

RETURN density * volume

END.
