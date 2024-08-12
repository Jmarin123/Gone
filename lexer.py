class LexerError(Exception):
    def __init__(self, message, lineNum, badVal, lexPos):
        self.message = message
        self.lineNum = lineNum
        self.badVal = badVal
        self.lexPos = lexPos


reserved = {
    'boolean': 'BOOLEAN',
    'break': 'BREAK',
    'class': 'CLASS',
    'do': 'DO',
    'else': 'ELSE',
    'extends': 'EXTENDS',
    'false': 'FALSE',
    'float': 'FLOAT',
    'for': 'FOR',
    'foreach': "FOREACH",
    'if': 'IF',
    'int': 'INT',
    'new': "NEW",
    'null': "NULL",
    'private': "PRIVATE",
    'maybe': "MAYBE",
    'public': "PUBLIC",
    'static': "STATIC",
    "super": "SUPER",
    "true": "TRUE",
    "this": "THIS",
    "void": "VOID",
    "while": "WHILE",
    "continue": "CONTINUE",
    "return": "RETURN"
}

tokens = [
    'INT_CONST',        # integer constant
    'FLOAT_CONST',      # float constant
    'STRING_CONST',     # string constant
    'INCREMENT',        # ++
    'DECREMENT',        # --
    'ARITH_OP',         # arithmetic operations
    'BOOL_OP',          # boolean comparisons
    'MAYBE_OP',
    'LINE_COMMENT',     # //
    'BLOCK_COMMENT',    # /*   */
    'ID'                # variable identifier
]

tokens += list(reserved.values())


def t_LINE_COMMENT(t):
    r'\/\/.*'
    pass


def t_BLOCK_COMMENT(t):
    r'\/\*[\s\S]*?\*\/'
    t.lexer.lineno += int(len(t.value.splitlines()))-1
    pass


def t_ID(t):
    r'[a-zA-Z_][a-zA-Z_0-9]*'
    t.type = reserved.get(t.value, 'ID')
    return t


def t_FLOAT_CONST(t):
    r'[-]?\d*\.\d+([eE][-+]?\d+)?'
    t.value = float(t.value)
    return t

def t_INT_CONST(t):
    r'-?\d+'
    t.value = int(t.value)
    return t


def t_NEW_LINE(t):
    r'\n+'
    t.lexer.lineno += len(t.value)
    return t


def t_error(t):
    raise LexerError("Character ERROR: ", t.lexer.lineno, t.value[0], t.lexpos)


t_ignore = ' \t'
t_DECREMENT = r'\-\-'
t_INCREMENT = r'\+\+'
t_STRING_CONST = r'\"[^\"]*\"'
t_BOOL_OP = r'&&|\|\||\=\=|\!=|<=|>=|<|>'
t_ARITH_OP = r'\+|\-|\*|\/|!'
literals = ['(', ')', '{', '}', ';', '.', ',', '=', '[', ']']