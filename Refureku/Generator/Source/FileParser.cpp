#include "FileParser.h"

using namespace rfk;

FileParser::FileParser() noexcept:
	kodgen::FileParser()
{
	//We abort parsing if we encounter a single error during parsing
	parsingSettings.shouldAbortParsingOnFirstError = true;

	//Ignore and remove space character before collecting properties
	parsingSettings.propertyParsingSettings.ignoredCharacters = {' '};

	//Each property will be separated with a , (and potentially some spaces as they are ignored)
	parsingSettings.propertyParsingSettings.propertySeparator = ',';

	//Subproperties are surrounded by []
	parsingSettings.propertyParsingSettings.subPropertyEnclosers[0] = '[';
	parsingSettings.propertyParsingSettings.subPropertyEnclosers[1] = ']';

	//Each subproperty will be separated with a , (and potentially some spaces as they are ignored)
	parsingSettings.propertyParsingSettings.subPropertySeparator = ',';

	//Define the Refureku property macros
	parsingSettings.propertyParsingSettings.namespaceMacroName	= "RFKNamespace";
	parsingSettings.propertyParsingSettings.classMacroName		= "RFKClass";
	parsingSettings.propertyParsingSettings.structMacroName		= "RFKStruct";
	parsingSettings.propertyParsingSettings.fieldMacroName		= "RFKField";
	parsingSettings.propertyParsingSettings.methodMacroName		= "RFKMethod";
	parsingSettings.propertyParsingSettings.enumMacroName		= "RFKEnum";
	parsingSettings.propertyParsingSettings.enumValueMacroName	= "RFKEnumVal";

	//Setup property rules
	parsingSettings.propertyParsingSettings.simplePropertyRules.emplace_back(&_dynamicGetArchetypePropertyRule);
	parsingSettings.propertyParsingSettings.simplePropertyRules.emplace_back(&_customInstantiatorPropertyRule);
	parsingSettings.propertyParsingSettings.complexPropertyRules.emplace_back(&_rangePropertyRule);
}

void FileParser::preParse(fs::path const& parseFile) noexcept
{
	if (logger != nullptr)
	{
		logger->log("Start parsing: " + parseFile.string(), kodgen::ILogger::ELogSeverity::Info);
	}
}

void FileParser::postParse(fs::path const&, kodgen::FileParsingResult const& result) noexcept
{
	if (logger != nullptr)
	{
		for (kodgen::ParsingError const& parsingError : result.errors)
		{
			logger->log(parsingError.toString(), kodgen::ILogger::ELogSeverity::Error);
		}

		logger->log("Found " + std::to_string(result.namespaces.size()) + " namespaces, " +
					std::to_string(result.structs.size()) + " structs, " +
					std::to_string(result.classes.size()) + " classes and " +
					std::to_string(result.enums.size()) + " enums.", kodgen::ILogger::ELogSeverity::Info);
	}
}