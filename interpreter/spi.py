"""SPI - Simple Pluscal Interpreter.
   based off https://ruslanspivak.com/lsbasi-part1/
"""
from Interpreter import Interpreter
from Parser import Parser
from Lexer import Lexer
from Extractor import Extractor
from enum import Enum
import argparse
import sys
from SpiErrors import LexerError, ParserError, ExtractorError

_SHOULD_LOG_SCOPE = False  # see '--scope' command line option
_SHOULD_LOG_STACK = False  # see '--stack' command line option

def main():
    parser = argparse.ArgumentParser(
        description='SPI - Simple Pascal Interpreter'
    )
    parser.add_argument('inputfile', help='Pascal source file')
    parser.add_argument(
        '--scope',
        help='Print scope information',
        action='store_true',
    )
    parser.add_argument(
        '--stack',
        help='Print call stack',
        action='store_true',
    )
    args = parser.parse_args()

    global _SHOULD_LOG_SCOPE, _SHOULD_LOG_STACK
    _SHOULD_LOG_SCOPE, _SHOULD_LOG_STACK = args.scope, args.stack

    text = open(args.inputfile, 'r').read()

    #We are just looking for the pluscal so strip everything else
    extractor = Extractor(text)

    try:
        lexer = Lexer(extractor.extract())
    except (ExtractorError) as e:
        print(e.message)
        sys.exit(1)
    
    try:
        parser = Parser(lexer)
        tree = parser.parse()
    except (LexerError, ParserError) as e:
        print(e.message)
        sys.exit(1)

    semantic_analyzer = SemanticAnalyzer()
    try:
        semantic_analyzer.visit(tree)
    except SemanticError as e:
        print(e.message)
        sys.exit(1)

    interpreter = Interpreter(tree)
    interpreter.interpret()


if __name__ == '__main__':
    main()