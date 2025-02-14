Program     = {Declaration} EOF ;

Declaration = FnDecl 
            | VarDecl 
            | ClassDecl
            | StructDecl
            | EnumDecl ;

FnDecl      = "fn" IDENTIFIER "(" [Param {"," Param}] ")" "->" Type Block ;
VarDecl     = "let" IDENTIFIER [Assignment] ";" ;
ClassDecl   = "class" IDENTIFIER "{" {FieldDecl | FnDecl} "}" ;
StructDecl  = "struct" IDENTIFIER "{" {FieldDecl} "}" ;
EnumDecl    = "enum" IDENTIFIER "{" {IDENTIFIER} "}" ;

Stmt        = ExprStmt
            | IfStmt
            | SwitchStmt
            | BreakStmt
            | ForStmt
            | WhileStmt
            | ContinueStmt
            | ReturnStmt
            | Block 
            | VarDecl ;

ExprStmt    = Expr ";" ;
IfStmt      = "if" "(" Expr ")" Stmt ["else" Stmt] ;
SwitchStmt  = "switch" "(" Expr ")" "{" {Case} "}" ;
BreakStmt   = "break" ";" ;
ForStmt     = "for" "(" (VarDecl | ExprStmt | ";") [Expr] ";" [Expr] ";" ")" Stmt ;
WhileStmt   = "while" "(" Expr ")" Stmt ;
ContinueStmt= "continue" ";" ;
ReturnStmt  = "return" [Expr] ";" ;
Block       = "{" {Stmt} "}" ;

Expr        = Assignment ;
Assignment  = (IDENTIFIER "=" Assignment)
            | Or ;
Or          = And {"||" And} ;
And         = Equality {"&&" Equality} ;
Equality    = Comparison {("==" | "!=") Comparison} ;
Comparison  = Factor {(">" | ">=" | "<" | "<=") Factor} ;
Term        = Factor {("+" | "-") Factor} ;
Factor      = Unary {("*" | "/") Unary} ;
Unary       = {"-" | "!"} Unary | Call ;
Call        = Primary {("(" {Arg} ")") | ("." IDENTIFIER)} ;
Primary     = "true" | "false" | "null" | INT | FLOAT | CHAR | ["ref"] IDENTIFIER | "this" | "(" Expr ")" ;

Param       = ["ref"] IDENTIFIER ":" Type ;
Field       = IDENTIFIER ":" Type ";" ;
Arg         = Expr {"," Expr} ;
Case        = "case" Comparison ":" {Stmt} ;
Type        = "i8" | "i16" | "i32" | "i64" | "u8" | "u16" | "u32" | "u64" | "float" | "string" | "bool" | "void" ;
