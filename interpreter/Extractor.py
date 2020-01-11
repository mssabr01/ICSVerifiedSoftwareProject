
import re

class Extractor:
    def __init__(self, source):
        self.source = source

    def error(self, msg):
        raise ExtractorError(message = msg)

    def extract(self):
        #look for start and end of pluscal
        start_regex = "^\(\* +(--fair)? +algorithm .*$"
        end_regex = "^end algorithm;\*\)$"
        start = re.search(start_regex, self.source, flags=re.MULTILINE)

        if(start == None):
            raise(self.error("Unable to detect start"))

        end = re.search(end_regex, self.source, flags=re.MULTILINE)

        if(end == None):
            raise(self.error("Unable to detect end"))

        pluscal = self.source[start.span()[1]:end.span()[0]]

        return pluscal