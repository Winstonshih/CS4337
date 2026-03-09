

/* EBNF Rules:

   <program> -> [<header>] dataType main '(' ')' '{' {<statement>} '}' EOF
   <header> -> # include '<' (iostream | id) '>' using namespace (id | std) ;

   <statement> -> <declaration> ; | <assign> ; | <stream> ; | <forLoop> | return int_constant | <ifStatement> ;
   <declaration> -> dataType id [= <expr>] {, id [= <expr>]} | dataType id'['int_constant']' [= <array>] | dataType id'['int_constant']' [= <expr>] 
   <assign> -> id ((=|+=|-=|*=|/=|%=) <expr> | ++ | --)

   <stream> -> <input> | <output>
   <input> -> cin {>> id}
   <output> -> cout {<< (<expr> | stringLit)}

   <boolexpr> -> <expr> [(>|>=|<|<=|!=|==) <expr>]
   <expr> -> <term> {(+ | -) <term>}
   <term> -> <factor> {(* | / | %) <factor>)
   <factor> -> id | int_constant | '(' <expr> ')'
   <array> -> '{' int_constant ',' int_constant ',' ... '}'
   <forLoop> -> for '(' <declaration> ; <boolexpr> ; <assign> ')' '{' {<statement>} '}'
   <ifStatement> -> if '(' <boolexpr> ')' '{' {<statement>} '}' [else '{' {<statement>} '}' ]
   
 */

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <limits>
using namespace std;

/* Global declarations */
/* Variables */
int charClass;
string lexeme;
char nextChar;
int nextCharInt = EOF;
int lexLen;
int nextToken;
ifstream in_fs;

const int MAX_LEXEME_LENGTH = 256; // small cap to avoid runaway lexemes

/* Function declarations */
void addChar ();
void getChar ();
void getNonBlank ();
int lex ();
void program ();
void header ();
void statement ();
void declaration ();
void assign ();
void stream ();
void input ();
void output ();
void forLoop ();
void boolexpr ();
void expr ();
void term ();
void factor ();
void error ();
void array ();
void ifStatement ();
void validateIntLiteral (const string &literal);

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define STRING_LIT 12
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define GR_THAN 27
#define GR_EQ_THAN 28
#define LS_THAN 29
#define LS_EQ_THAN 30
#define EQ_TO 31
#define NT_EQ_TO 32
#define INCR_OP 33
#define DECR_OP 34
#define NEGATION 35
#define IF 36
#define SEMICOLON 37
#define LEFT_CURLY 38
#define RIGHT_CURLY 39
#define MOD_OP 40
#define EXT_OP 41
#define INS_OP 42
#define ADD_EQ 43
#define SUB_EQ 44
#define MULT_EQ 45
#define DIV_EQ 46
#define MOD_EQ 47
#define CIN 50
#define COUT 51
#define COMMA 52
#define DATATYPE 53
#define RETURN 54
#define QUOTE 55
#define HASHTAG 56
#define MAIN 57
#define INCLUDE 58
#define IOSTREAM 59
#define USING 60
#define NAMESPACE 61
#define STD 62
#define FOR 63
#define LEFT_BRACKET 64
#define RIGHT_BRACKET 65

/******************************************************/
/* main driver */
int
main ()
{
  /* Open the input data file and process its contents */
  in_fs.open ("codeSample.in");
  if (!in_fs.is_open ())
    {
      cerr << "ERROR - cannot open codeSample.in\n";
      return 1;
    }

  /* Begin the recursion descent */
  getChar ();
  lex ();
  program ();

  in_fs.close ();

  return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses
			and return the token */
int
lookup (char ch)
{
  switch (ch)
    {
    case '(':
      addChar ();
      nextToken = LEFT_PAREN;
      break;
    case ')':
      addChar ();
      nextToken = RIGHT_PAREN;
      break;
    case '{':
      addChar ();
      nextToken = LEFT_CURLY;
      break;
    case '}':
      addChar ();
      nextToken = RIGHT_CURLY;
      break;
    case '[':
      addChar ();
      nextToken = LEFT_BRACKET;
      break;
    case ']':
      addChar ();
      nextToken = RIGHT_BRACKET;
      break;
    case ';':
      addChar ();
      nextToken = SEMICOLON;
      break;
    case '+':
      addChar ();
      if (in_fs.peek () == '+')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = INCR_OP;
	}
      else if (in_fs.peek () == '=')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = ADD_EQ;
	}
      else
	nextToken = ADD_OP;
      break;
    case '-':
      addChar ();
      if (in_fs.peek () == '-')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = DECR_OP;
	}
      else if (in_fs.peek () == '=')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = SUB_EQ;
	}
      else
	nextToken = SUB_OP;
      break;
    case '*':
      addChar ();
      if (in_fs.peek () == '=')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = MULT_EQ;
	}
      else
	nextToken = MULT_OP;
      break;
    case '/':
      addChar ();
      if (in_fs.peek () == '=')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = DIV_EQ;
	}
      else
	nextToken = DIV_OP;
      break;
    case '%':
      addChar ();
      if (in_fs.peek () == '=')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = MOD_EQ;
	}
      else
	nextToken = MOD_OP;
      break;
    case '>':
      addChar ();
      if (in_fs.peek () == '=')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = GR_EQ_THAN;
	}
      else if (in_fs.peek () == '>')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = EXT_OP;
	}
      else
	nextToken = GR_THAN;
      break;
    case '<':
      addChar ();
      if (in_fs.peek () == '=')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = LS_EQ_THAN;
	}
      else if (in_fs.peek () == '<')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = INS_OP;
	}
      else
	nextToken = LS_THAN;
      break;
    case '!':
      addChar ();
      if (in_fs.peek () == '=')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = NT_EQ_TO;
	}
      else
	nextToken = NEGATION;
      break;
    case '=':
      addChar ();
      if (in_fs.peek () == '=')
	{
	  in_fs.get (nextChar);
	  addChar ();
	  nextToken = EQ_TO;
	}
      else
	nextToken = ASSIGN_OP;
      break;
    case ',':
      addChar ();
      nextToken = COMMA;
      break;
    case '"':
      addChar ();
      nextToken = QUOTE;
      break;
    case '#':
      addChar ();
      nextToken = HASHTAG;
      break;
    default:
      addChar ();
      nextToken = EOF;
      break;
    }
  return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void
addChar ()
{
  if (nextCharInt == EOF)
    {
      cerr << "Unexpected EOF while building lexeme\n";
      error ();
    }
  if ((int) lexeme.size () >= MAX_LEXEME_LENGTH)
    {
      cerr << "Lexeme is too long\n";
      error ();
    }
  lexeme.push_back (nextChar);
}

/*****************************************************/
/* getChar - a function to get the next character of
			 input and determine its character class */
void
getChar ()
{
  nextCharInt = in_fs.get ();
  if (nextCharInt != EOF)
    {
      nextChar = static_cast < char >(nextCharInt);
      unsigned char safeChar = static_cast < unsigned char >(nextChar);
      if (isalpha (safeChar) || nextChar == '_')
	charClass = LETTER;
      else if (isdigit (safeChar))
	charClass = DIGIT;
      else
	charClass = UNKNOWN;
    }
  else
    {
      nextChar = '\0';
      charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it
				 returns a non-whitespace character */
void
getNonBlank ()
{
  while (isspace (static_cast < unsigned char >(nextChar)))
    getChar ();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
		 expressions */
int
lex ()
{
  lexeme.clear ();
  getNonBlank ();
  switch (charClass)
    {
      /* Parse identifiers */
    case LETTER:
      addChar ();
      getChar ();
      while (charClass == LETTER || charClass == DIGIT)
	{
	  addChar ();
	  getChar ();
	}
      if (lexeme == "main")
	nextToken = MAIN;
      else if (lexeme == "include")
	nextToken = INCLUDE;
      else if (lexeme == "iostream")
	nextToken = IOSTREAM;
      else if (lexeme == "using")
	nextToken = USING;
      else if (lexeme == "namespace")
	nextToken = NAMESPACE;
      else if (lexeme == "std")
	nextToken = STD;
      else if (lexeme == "for")
	nextToken = FOR;
      else if (lexeme == "cin")
	nextToken = CIN;
      else if (lexeme == "cout")
	nextToken = COUT;
      else if (lexeme == "int")
	nextToken = DATATYPE;
      else if (lexeme == "return")
	nextToken = RETURN;
      else if (lexeme == "if")
	nextToken = IF;
      else
	nextToken = IDENT;
      break;
      /* Parse integer literals */
    case DIGIT:
      addChar ();
      getChar ();
      while (charClass == DIGIT)
	{
	  addChar ();
	  getChar ();
	}
      validateIntLiteral (lexeme);
      nextToken = INT_LIT;
      break;
      /* Parentheses and operators */
    case UNKNOWN:
      lookup (nextChar);
      getChar ();
      /* Parse string literals */
      if (nextToken == QUOTE)
	{
	  addChar ();
	  getChar ();
	  while (nextChar != '"' && nextChar != EOF)
	    {
	      addChar ();
	      getChar ();
	    }
	  if (nextChar == '"')
	    {
	      addChar ();
	      getChar ();
	      nextToken = STRING_LIT;
	    }
	  else
	    nextToken = EOF;
	}
      break;
      /* EOF */
    case EOF:
      nextToken = EOF;
      lexeme = "EOF";
      break;
    }				/* End of switch */
  cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme <<
    endl;
  return nextToken;
}				/* End of function lex */

/* program
   Parses strings in the language generated by the rule:
   <program> -> [<header>] dataType main '(' ')' '{' {<statement>} '}' EOF
*/
void
program ()
{
  cout << "Enter <program>" << endl;
  if (nextToken == HASHTAG)
    header ();
  if (nextToken == DATATYPE)
    {
      lex ();
      if (nextToken == MAIN)
	{
	  lex ();
	  if (nextToken == LEFT_PAREN)
	    {
	      lex ();
	      if (nextToken == RIGHT_PAREN)
		{
		  lex ();
		  if (nextToken == LEFT_CURLY)
		    {
		      lex ();
		      while (nextToken != RIGHT_CURLY)
			{
			  statement ();
			}
		      if (nextToken == RIGHT_CURLY)
			{
			  lex ();
			  if (nextToken == EOF)
			    lex ();
			  else
			    error ();
			}
		      else
			error ();
		    }
		  else
		    error ();
		}
	      else
		error ();
	    }
	  else
	    error ();
	}
      else
	error ();
    }
  else
    error ();
  cout << "Exit <program>" << endl;
}

/* header
   Parses strings in the language generated by the rule:
   <header> -> # include '<' (iostream | id) '>' using namespace (id | std) ;
*/
void
header ()
{
  cout << "Enter <header>" << endl;
  if (nextToken == HASHTAG)
    {
      lex ();
      if (nextToken == INCLUDE)
	{
	  lex ();
	  if (nextToken == LS_THAN)
	    {
	      lex ();
	      if (nextToken == IOSTREAM || nextToken == IDENT)
		{
		  lex ();
		  if (nextToken == GR_THAN)
		    {
		      lex ();
		      if (nextToken == USING)
			{
			  lex ();
			  if (nextToken == NAMESPACE)
			    {
			      lex ();
			      if (nextToken == IDENT || nextToken == STD)
				{
				  lex ();
				  if (nextToken == SEMICOLON)
				    lex ();
				  else
				    error ();
				}
			      else
				error ();
			    }
			  else
			    error ();
			}
		      else
			error ();
		    }
		  else
		    error ();
		}
	      else
		error ();
	    }
	  else
	    error ();
	}
      else
	error ();
    }
  else
    error ();
  cout << "Exit <header>" << endl;
}

/* statement
   Parses strings in the language generated by the rule:
      <statement> -> <declaration> ; | <assign> ; | <stream> ; | <forLoop> | return int_constant | <ifStatement> ;
   */
void
statement ()
{
  cout << "Enter <statement>" << endl;
  if (nextToken == DATATYPE)
    {
      declaration ();
      if (nextToken == SEMICOLON)
	lex ();
      else
	error ();
    }
  else if (nextToken == IDENT)
    {
      assign ();
      if (nextToken == SEMICOLON)
	lex ();
      else
	error ();
    }
  else if (nextToken == CIN || nextToken == COUT)
    {
      stream ();
      if (nextToken == SEMICOLON)
	lex ();
      else
	error ();
    }
  else if (nextToken == RETURN)
    {
      lex ();
      if (nextToken == INT_LIT)
	lex ();
      else
	error ();

      if (nextToken == SEMICOLON)
	lex ();
      else
	error ();
    }
  else if (nextToken == IF)
    ifStatement ();
  else if (nextToken == FOR)
    forLoop ();
  else
    error ();
  cout << "Exit <statement>" << endl;
}

/* declaration
   Parses strings in the language generated by the rule:
     <declaration> -> dataType id [= <expr>] {, id [= <expr>]} | dataType id'['int_constant']' [= <expr>] | dataType id'['int_constant']' [= <array>]
   */
void
declaration ()
{
  cout << "Enter <declaration>" << endl;
  if (nextToken == DATATYPE)
    {
      lex ();
      if (nextToken == IDENT)
	{
	  lex ();
	  if (nextToken == ASSIGN_OP)
	    {
	      lex ();
	      expr ();
	    }
	  if (nextToken == LEFT_BRACKET)
	    {
	      lex ();
	      if (nextToken == INT_LIT)
		{
		  lex ();
		}
	      if (nextToken == RIGHT_BRACKET)
		{
		  lex ();
		  if (nextToken == ASSIGN_OP)
		    {
		      lex ();
          ::array ();
		    }
		}
	    }
	}
      else
	error ();
      while (nextToken == COMMA)
	{
	  lex ();
	  if (nextToken == IDENT)
	    {
	      lex ();
	      if (nextToken == ASSIGN_OP)
		{
		  lex ();
		  expr ();
		}
	    }
	  else
	    error ();
	}
    }
  else
    error ();
  cout << "Exit <declaration>" << endl;
}

/* assign
   Parses strings in the language generated by the rule:
   <assign> -> id ((=|+=|-=|*=|/=|%=) <expr> | ++ | --)
   */
void
assign ()
{
  cout << "Enter <assign>" << endl;
  if (nextToken == IDENT)
    {
      lex ();
      /* If the identifier is an array */
      if (nextToken == LEFT_BRACKET)
	{
	  lex ();
	  if (nextToken == INT_LIT || nextToken == IDENT)
	    {
	      lex ();
	    }
	  if (nextToken == RIGHT_BRACKET)
	    {
	      lex ();
	    }
	}
      /* If it's an assignment then it will use an expression */
      if (nextToken == ASSIGN_OP || nextToken == ADD_EQ || nextToken == SUB_EQ
	  || nextToken == MULT_EQ || nextToken == DIV_EQ
	  || nextToken == MOD_EQ)
	{
	  lex ();
	  expr ();
	}
      else if (nextToken == INCR_OP || nextToken == DECR_OP)
	lex ();
      /* Must be one of the 8 operations */
      else
	error ();
    }
  /* Always has to start with an IDENT (id) */
  else
    error ();
  cout << "Exit <assign>" << endl;
}

/* stream
   Parses strings in the language generated by the rule:
   <stream> -> <input> | <output>
 */
void
stream ()
{
  cout << "Enter <stream>" << endl;
  if (nextToken == CIN)
    input ();
  else if (nextToken == COUT)
    output ();
  else
    error ();
  cout << "Exit <stream>" << endl;
}

/* output
   Parses strings in the language generated by the rule:
   <input> -> cin {>> <id>}
 */
void
input ()
{
  cout << "Enter <input>" << endl;
  if (nextToken == CIN)
    {
      lex ();
      while (nextToken == EXT_OP)
	{
	  lex ();
	  if (nextToken == IDENT)
	    lex ();
	  else
	    error ();
	}
    }
  else
    error ();
  cout << "Exit <input>" << endl;
}

/* output
   Parses strings in the language generated by the rule:
   <output> -> cout {<< (<expr> | stringLit)}
 */
void
output ()
{
  cout << "Enter <output>" << endl;
  if (nextToken == COUT)
    {
      lex ();
      while (nextToken == INS_OP)
	{
	  lex ();
	  if (nextToken == IDENT || nextToken == INT_LIT)
	    expr ();
	  else if (nextToken == STRING_LIT)
	    lex ();
	}
    }
  else
    error ();
  cout << "Exit <output>" << endl;
}

/* boolexpr
   Parses strings in the language generated by the rule:
   <boolexpr> -> <expr> [(>|>=|<|<=|!=|==) <expr>]
   */
void
boolexpr ()
{
  cout << "Enter <boolexpr>" << endl;
  expr ();			// boolexpr can just be an expression or a comparison between expressions
  if (nextToken == GR_THAN || nextToken == GR_EQ_THAN || nextToken == LS_THAN
      || nextToken == LS_EQ_THAN || nextToken == NT_EQ_TO
      || nextToken == NT_EQ_TO)
    {
      lex ();
      expr ();
    }
  cout << "Exit <boolexpr>" << endl;
}

/* expr
   Parses strings in the language generated by the rule:
   <expr> -> <term> {(+ | -) <term>}
   */
void
expr ()
{
  cout << "Enter <expr>" << endl;
  /* Parse the first term */
  term ();
  /* As long as the next token is + or -, get
     the next token and parse the next term */
  while (nextToken == ADD_OP || nextToken == SUB_OP)
    {
      lex ();
      term ();
    }
  cout << "Exit <expr>" << endl;
}				/* End of function expr */

/* term
   Parses strings in the language generated by the rule:
   <term> -> <factor> {(* | /) <factor>)
   */
void
term ()
{
  cout << "Enter <term>" << endl;
  /* Parse the first factor */
  factor ();
  /* As long as the next token is * or /, get the
     next token and parse the next factor */
  while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == MOD_OP)
    {
      lex ();
      factor ();
    }
  cout << "Exit <term>" << endl;
}				/* End of function term */

/* factor
   Parses strings in the language generated by the rule:
   <factor> -> id | id'['int_constant']' | int_constant | '(' <expr> ')'
   */
void
factor ()
{
  cout << "Enter <factor>" << endl;
  /* Determine which RHS */
  if (nextToken == IDENT || nextToken == INT_LIT)
    {
      /* Get the next token */
      lex ();
      /* If the RHS is ( <expr>), call lex to pass over the
         left parenthesis, call expr, and check for the right
         parenthesis */

      /* If the identifier includes brackets
       * it is an array
       */
      if (nextToken == LEFT_BRACKET)
	{
	  lex ();
	  if (nextToken == INT_LIT || nextToken == IDENT)
	    {
	      lex ();
	      if (nextToken == RIGHT_BRACKET)
		{
		  lex ();
		}
	    }
	}
    }
  else
    {
      if (nextToken == LEFT_PAREN)
	{
	  lex ();
	  expr ();
	  if (nextToken == RIGHT_PAREN)
	    lex ();
	  else
	    error ();
	}			/* End of if (nextToken == ... */
      /* It was not an id, an integer literal, or a left
         parenthesis */
      else
	error ();
    }				/* End of else */
  cout << "Exit <factor>" << endl;
}				/* End of function factor */


/* array
   Parses strings in the language generated by the rule:
   <array> -> '{' int_constant ',' int_constant ',' ... '}'
   */
void
array ()
{
  cout << "Enter <array>" << endl;
  if (nextToken == LEFT_CURLY)
    {
      lex ();
      while (nextToken == INT_LIT || nextToken == COMMA)
	{
	  lex ();
	}
    }

  if (nextToken == RIGHT_CURLY)
    {
      lex ();
      cout << "Exit <array>" << endl;
    }
  else
    {
      error ();
    }

}

/* forLoop
   Parses strings in the language generated by the rule:
      <forLoop> -> for '(' <declaration> ; <boolexpr> ; <assign> ')' '{' {<statement>} '}'
*/
void
forLoop ()
{
  cout << "Enter <forLoop>" << endl;
  if (nextToken == FOR)
    {
      lex ();
      if (nextToken == LEFT_PAREN)
	{
	  lex ();
	  assign ();
	  if (nextToken == SEMICOLON)
	    {
	      lex ();
	      boolexpr ();
	      if (nextToken == SEMICOLON)
		{
		  lex ();
		  assign ();
		  if (nextToken == RIGHT_PAREN)
		    {
		      lex ();
		      if (nextToken == LEFT_CURLY)
			{
			  lex ();
			  /* Ends when '}' is found */
			  while (nextToken != RIGHT_CURLY)
			    {
			      /* {<statement>}'}' keep with the statements until there is an error in the statement. */
			      statement ();
			    }
			  if (nextToken == RIGHT_CURLY)
			    lex ();
			  else
			    error ();
			}
		      /* Must have { */
		      else
			error ();
		    }
		}
	    }
	  /* Must have ) after condition */
	  else
	    error ();
	}
      /* Must have ( */
      else
	error ();
    }
  else
    // if there is no 'for' then there can be no for loop!
    error ();
  cout << "Exit <forLoop>" << endl;
}


/* ifStatement
   Parses strings in the language generated by the rule:
   <ifStatement> -> if '(' <boolexpr> ')' '{' {<statement>} '}' [else '{' {<statement>} '}' ]
   */
void
ifStatement ()
{
  cout << "Enter <ifStatement>" << endl;
  if (nextToken == IF)
    {
      lex ();
      if (nextToken == LEFT_PAREN)
	{
	  lex ();
	  boolexpr ();
	  if (nextToken == RIGHT_PAREN)
	    {
	      lex ();
	      if (nextToken == LEFT_CURLY)
		{
		  lex ();
		  /* Ends when '}' is found */
		  while (nextToken != RIGHT_CURLY)
		    {
		      /* {<statement>}'}' keep with the statements until there is an error in the statement. */
		      statement ();
		    }
		  if (nextToken == RIGHT_CURLY)
		    lex ();
		  else
		    error ();
		}
	    }
	}
    }
  cout << "Exit <ifStatement>" << endl;
}

void
validateIntLiteral (const string &literal)
{
  long long value = 0;
  for (size_t i = 0; i < literal.size (); ++i)
    {
      char c = literal[i];
      if (!isdigit (static_cast < unsigned char >(c)))
	{
	  cerr << "Invalid integer literal: " << literal << "\n";
	  error ();
	}
      value = value * 10 + (c - '0');
      if (value > numeric_limits < int >::max ())
	{
	  cerr << "Integer literal out of 32-bit range: " << literal << "\n";
	  error ();
	}
    }
}

void
error ()
{
  cerr << "Error\n";
  exit (1);
}
