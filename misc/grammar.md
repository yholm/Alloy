Stmt        = VarDecl | FnDecl | ExprStmt ;

VarDecl     = "let" Identifier ":" Type [ "=" Expr ] ";" ;

FnDecl      = "fn" Identifier "(" [ Param { "," Param } ] ")" "->" Type "{" { Stmt } "}" ;

ExprStmt    = Expr ";" ;

Param       = ["ref"] Identifier ":" Type ;

Type        = "i8" | "i16" | "i32" | "i64" | "u8" | "u16" | "u32" | "u64" | "float" | "string" | "bool" ;
