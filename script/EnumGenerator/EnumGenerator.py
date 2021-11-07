# %ENUM_NAME% : Name of the enum
# %ENUM_SIZE% : Number of values in the enum
# %ENUM_VALUES% : List of values a, b, c, d, etc...
# %ENUM_VALUES_STRINGS% : List of values between quotes "a", "b", "c", etc...
# %ENUM_VALUES_MAP% : Mapping between VALUES_LIST and VALUES_LIST_STRINGS
#                     {"a", a}, {"b", b}, {"c", c}, etc...

import argparse
import json
import os

def patchFile(fileIn, fileOut, valuesToReplace):
    with open(fileIn, 'r') as fIn, open(fileOut, 'w') as fOut:
        strFile = fIn.read()
        for key, value in valuesToReplace.items():
            strFile = strFile.replace(key, value)
        fOut.write(strFile)

def main():
    parser = argparse.ArgumentParser(description='Extended enum generator')
    parser.add_argument('json', help='Enum file in json format')
    parser.add_argument('destination', help='Files output')
    args = parser.parse_args()

    jsonFile = args.json
    destination = args.destination
    scriptFolder = os.path.dirname(__file__)

    with open(jsonFile, 'r') as f:
        enumJson = json.load(f)

    enumName = os.path.basename(jsonFile).rsplit('.', 1)[0]
    enumValuesArray = enumJson['values']
    enumSize = str(len(enumValuesArray))
    enumValues = ''
    enumValuesStrings = ''
    enumValuesMap = ''
    for value in enumValuesArray:
        valueStr = f'"{value}"'
        enumValues += f'{value}, '
        enumValuesStrings += f'{valueStr}, '
        enumValuesMap += f'{{{valueStr}, {value}}}, '

    valuesToReplace = {
        '%ENUM_NAME%': enumName,
        '%ENUM_SIZE%': enumSize,
        '%ENUM_VALUES%': enumValues,
        '%ENUM_VALUES_STRINGS%': enumValuesStrings,
        '%ENUM_VALUES_MAP%': enumValuesMap}

    headerPatternFile = os.path.join(scriptFolder, 'EnumPattern.h.in')
    cppPatternFile = os.path.join(scriptFolder, 'EnumPattern.cpp.in')

    headerFileOut = os.path.join(destination, enumName + '.h')
    cppFileOut = os.path.join(destination, enumName + '.cpp')

    patchFile(headerPatternFile, headerFileOut, valuesToReplace)
    patchFile(cppPatternFile, cppFileOut, valuesToReplace)

if __name__ == '__main__':
    main()
