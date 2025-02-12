Expr        = Equality ;
Equality    = Comparison {("==" | "!=") Comparison} ;
Comparison  = Factor {(">" | ">=" | "<" | "<=") Factor} ;
Factor      = Term {("*" | "/") Term} ;
Term        = Unary {("+" | "-") Unary} ;
Unary       = {"-" | "!"} Primary ;
Primary     = "true" | "false" | "null" | INT | FLOAT | CHAR | IDENTIFIER | "(" Expr ")" ;

Type        = "i8" | "i16" | "i32" | "i64" | "u8" | "u16" | "u32" | "u64" | "float" | "string" | "bool" ;
