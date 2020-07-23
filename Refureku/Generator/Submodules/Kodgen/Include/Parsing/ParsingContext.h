#pragma once

#include <clang-c/Index.h>

#include "ParsingResults/ParsingResultBase.h"
#include "Misc/EAccessSpecifier.h"

namespace kodgen
{
	//Forward declarations
	class	PropertyParser;
	struct	ParsingSettings;

	struct ParsingContext
	{
		public:
			/** Parent context of this context. */
			ParsingContext const*	parentContext			= nullptr;

			/** Root cursor of this parsing context. */
			CXCursor				rootCursor				= clang_getNullCursor();
			
			/** Current access specifier */
			EAccessSpecifier		currentAccessSpecifier	= EAccessSpecifier::Invalid;

			/** Should check for properties (annotate) at the next parsing step? */
			bool					shouldCheckProperties	= true;

			/** Parser used to parse entity properties. */
			PropertyParser*			propertyParser			= nullptr;

			/** ParsingSettings used. */
			ParsingSettings const*	parsingSettings			= nullptr;

			/** Result of the parsing. */
			ParsingResultBase*		parsingResult			= nullptr;
	};
}