import sys
from ply import lex
from ply import yacc
import lexer as my_lexer
import parser as my_parser

def main():
    fn = sys.argv[1] if len(sys.argv) > 1 else ""
    if fn == "":
        print("Missing file name for source program.")
        print("USAGE: python3 entry.py <decaf_source_file_name>")
        sys.exit(1)
    lexer = lex.lex(module=my_lexer, debug=True)
    # parse = yacc.yacc(module=my_parser)
    try:
        open_file = open(fn, "r")
        all_items = open_file.read()
        open_file.close()
        lexer.input(all_items)
        while True:
            next_token = lexer.token()
            if not next_token:
                break
            print(next_token)
    except FileNotFoundError:
        print("File does not exist")
        sys.exit(1)
    sys.exit(0)


if __name__ == "__main__":
    main()
    