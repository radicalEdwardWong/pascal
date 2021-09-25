#ifndef error_h
#define error_h

extern int errorCount;
extern int errorArrowFlag;
extern int errorArrowOffset;

enum TAbortCode {
	abortInvalidCommandLineArgs = -1,
	abortSourceFileOpenFailed = -2,
	abortIFormFileOpenFailed = -3,
	abortAssemblyFileOpenFailed = -4,
	abortTooManySyntaxErors = -5,
	abortStackOverflow = -6,
	abortCodeSegmentOverflow = -7,
	abortNestingTooDeep = -8,
	abortRuntimeError = -9,
	abortUnimplementedFeature = -10,
};

void AbortTranslation(TAbortCode ac);

enum TErrorCode {
	errNone,
	errUnrecognizable,
	errTooMany,
	errUnexpectedEndOfFile,
	errInvalidNumber,
	errInvalidFraction,
	errInvalidExponent,
	errTooManyDigits,
	errRealOutOfRange,
	errIntegerOutOfRange,
	errMissingRightParen,
	errInvalidExpression,
	errInvalidAssignment,
	errMissingIdentifier,
	errMissingColonEqua,
	errUndefinedIdentifier,
	errStackOverflow,
	errInvalidStatement,
	errUnexpectedToken,
	errMissingSemicolon,
	errMissingComma,
	errMissingDO,
	errMissingUNTIL,
	errMissingTHEN,
	errInvalidFORControl,
	errMissingOF,
	errInvalidConstant,
	errMissingConstant,
	errMissingColon,
	errMissingEND,
	errMissingTOorDOWNTO,
	errRedefinedIdentifier,
	errMissingEqual,
	errInvalidType,
	errNotATypeIdentifier,
	errInvalidSubrangeType,
	errNotAConstantIdentifier,
	errMissingDotDot,
	errIncompatibleTypes,
	errInvalidTarget,
	errInvalidIdentifierUsage,
	errIncompatibleAssignment,
	errMinGtMax,
	errMissingLeftBracket,
	errMissingRightBracket,
	errInvalidIndexType,
	errMissingBEGIN,
	errMissingPeriod,
	errTooManySubscripts,
	errInvalidField,
	errNestingTooDeep,
	errMissingPROGRAM,
	errAreadyForwarded,
	errWrongNumberOfParms
};

void Error(TErrorCode ec);

#endif
