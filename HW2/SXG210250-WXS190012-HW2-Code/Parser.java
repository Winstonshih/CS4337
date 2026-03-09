/**
 * Satyam Garg (SXG220250)
 * Winston Shih (WXS190012)
 * CS 4337.004
 * Homework 2 Question 5 Source Code 
 */
public class Parser {

    //tokens ( i think )
    static int INT=0;
    static int WHILE=1;
    static int IF=2;
    static int RETURN=3;
    static int ID=4;
    static int NUM=5;
    static int EQ=6;
    static int OP=7;
    static int ADD=8;
    static int DEC=9;
    static int LPAREN=10;
    static int RPAREN=11;
    static int LBRACE=12;
    static int RBRACE=13;
    static int LBRACKET=14;
    static int RBRACKET=15;
    static int COMMA=16;
    static int SEMI=17;
    static int EOF=99;

    // lists for stuff
    static String[] lex = new String[200];
    static int[] tok = new int[200];
    static int size = 0;

    static int point=0;
    static int tokNow;
    static String lexNow;

    /**
     * Main method of parser program that loads tokens, parses from top-level function, and reports when parsing is complete.
     */
    public static void main(String args[]){
        load(); 
        next(); 
        func();  

        if(tokNow==EOF){
            System.out.println("ok done parsing");
        }else{
            System.out.println("something wrong???");
        }
    }

    /**
     * Advances to the next token and lexeme and when it reaches end of input, it sets current token to EOF.
     */
    static void next(){
        if(point<size){
            lexNow = lex[point];
            tokNow = tok[point];
            point++;
        } else {
            lexNow="EOF";
            tokNow=EOF;
        }
        System.out.println("token="+tokNow+" lexeme="+lexNow);
    }

    /**
     * Parses a function declaration: int ID (params) { stmts }.
     */
    static void func(){
        System.out.println("in func");
        if(tokNow==INT) next();
        if(tokNow==ID) next();
        if(tokNow==LPAREN) next();
        par();
        if(tokNow==RPAREN) next();
        if(tokNow==LBRACE) next();
        stmts();
        if(tokNow==RBRACE) next();
        System.out.println("out func");
    }

    /**
     * Parses function parameters and handles optional array brackets, commas, and multiple parameter declarations.
     */
    static void par(){
        System.out.println("in params");
        if(tokNow==INT) next();
        if(tokNow==ID) next();
        if(tokNow==LBRACKET) next();
        if(tokNow==RBRACKET) next();
        if(tokNow==COMMA){
            next();
            if(tokNow==INT) next();
            if(tokNow==ID) next();
        }
        System.out.println("out params");
    }

    /**
     * Parses a sequence of statements inside braces until it finds a '}'.
     */
    static void stmts(){
        System.out.println("in stmtlist");
        while(tokNow!=RBRACE){
            stmt();
        }
        System.out.println("out stmtlist");
    }

    /**
     * Parses a single statement and handles declarations, loops, conditionals, return statements, or expressions.
     */
    static void stmt(){
        System.out.println("in stmt");
        if(tokNow==INT){
            decl();
        } else if(tokNow==WHILE){
            whl();
        } else if(tokNow==IF){
            iff();
        } else if(tokNow==RETURN){
            ret();
        } else if(tokNow==ID){
            exp();
            if(tokNow==SEMI) next();
        }
        System.out.println("out stmt");
    }

    /**
     * Parses a variable declaration statement: int ID = expr.
     */
    static void decl(){
        System.out.println("in decl");
        if(tokNow==INT) next();
        if(tokNow==ID) next();
        if(tokNow==EQ) next();
        exp();
        if(tokNow==SEMI) next();
        System.out.println("out decl");
    }

    /**
     * Parses a while loop statement: while (expr) { stmts }.
     */
    static void whl(){
        System.out.println("in while");
        if(tokNow==WHILE) next();
        if(tokNow==LPAREN) next();
        exp();
        if(tokNow==RPAREN) next();
        if(tokNow==LBRACE) next();
        stmts();
        if(tokNow==RBRACE) next();
        System.out.println("out while");
    }

    /**
     * Parses an if statement: if (expr) { stmts }.
     */
    static void iff(){
        System.out.println("in if");
        if(tokNow==IF) next();
        if(tokNow==LPAREN) next();
        exp();
        if(tokNow==RPAREN) next();
        if(tokNow==LBRACE) next();
        stmts();
        if(tokNow==RBRACE) next();
        System.out.println("out if");
    }

    /**
     * Parses a return statement of the form and returns expr.
     */
    static void ret(){
        System.out.println("in return");
        if(tokNow==RETURN) next();
        exp();
        if(tokNow==SEMI) next();
        System.out.println("out return");
    }

    /**
     * Parses an expression.
     * Supports operators and terms of the form term OP term.
     */
    static void exp(){
        System.out.println("in expr");
        term();
        if(tokNow==OP){
            next();
            term();
        }
        System.out.println("out expr");
    }

    /**
     * Parses a term inside an expression and supports operators between factors (+,-,/,*).
     */
    static void term(){
        System.out.println("in term");
        fac();
        if(tokNow==ADD){
            next();
            fac();
        }
        System.out.println("out term");
    }

    /**
     * Parses a factor like an identifier (array indexing or decrement) or a numeric literal.
     */
    static void fac(){
        System.out.println("in factor");
        if(tokNow==ID){
            next();
            if(tokNow==LBRACKET){
                next();
                exp();
                if(tokNow==RBRACKET) next();
            } else if(tokNow==DEC){
                next();
            }
        } else if(tokNow==NUM){
            next();
        }
        System.out.println("out factor");
    }

    /**
     * Adds a single (lexeme, token) pair into the token buffer.
     */
    static void add(String l, int t){
        lex[size] = l;
        tok[size] = t;
        size++;
    }

    /**
     * Loads all tokens and lexemes into memory for parsing as a pre-built token stream for parser.
     */
    static void load(){
        add("int", INT);
        add("duplicate_check", ID);
        add("(", LPAREN);
        add("int", INT);
        add("a", ID);
        add("[", LBRACKET);
        add("]", RBRACKET);
        add(",", COMMA);
        add("int", INT);
        add("n", ID);
        add(")", RPAREN);
        add("{", LBRACE);
        add("int", INT);
        add("i", ID);
        add("=", EQ);
        add("n", ID);
        add(";", SEMI);
        add("while", WHILE);
        add("(", LPAREN);
        add("i", ID);
        add(">", OP);
        add("0", NUM);
        add(")", RPAREN);
        add("{", LBRACE);
        add("i", ID);
        add("--", DEC);
        add(";", SEMI);
        add("int", INT);
        add("j", ID);
        add("=", EQ);
        add("i", ID);
        add("-", ADD);
        add("1", NUM);
        add(";", SEMI);
        add("while", WHILE);
        add("(", LPAREN);
        add("j", ID);
        add(">=", OP);
        add("0", NUM);
        add(")", RPAREN);
        add("{", LBRACE);
        add("if", IF);
        add("(", LPAREN);
        add("a", ID);
        add("[", LBRACKET);
        add("i", ID);
        add("]", RBRACKET);
        add("==", OP);
        add("a", ID);
        add("[", LBRACKET);
        add("j", ID);
        add("]", RBRACKET);
        add(")", RPAREN);
        add("{", LBRACE);
        add("return", RETURN);
        add("1", NUM);
        add(";", SEMI);
        add("}", RBRACE);
        add("j", ID);
        add("--", DEC);
        add(";", SEMI);
        add("}", RBRACE);
        add("}", RBRACE);
        add("return", RETURN);
        add("0", NUM);
        add(";", SEMI);
        add("}", RBRACE);
    }
}
