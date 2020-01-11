class Error(Exception):
    def __init__(self, error_code=None, token=None, message=None):
        self.error_code = error_code
        self.token = token
        # add exception class name before the message
        self.message = f'{self.__class__.__name__}: {message}'

class ExtractorError(Error):
    pass

class LexerError(Error):
    pass

class ParserError(Error):
    pass

class SemanticError(Error):
    pass