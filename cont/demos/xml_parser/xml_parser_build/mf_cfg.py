
import os;

C_XML_PARSER_DIR = os.sep.join(os.getcwd().split(os.sep)[:-1] + ["xml_parser"])

index = 0
C_XML_PARSER_PROG = index; index += 1

index = 0
CFG_NAME   = index; index += 1
CFG_TARGET = index; index += 1
CFG_DIR    = index; index += 1
CFG_MODULE = index; index += 1

c_cfg = [
    ["XML_PARSER",True,C_XML_PARSER_DIR,None],
]

