#ifndef error_h
#define error_h

extern int errorCount;

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

#endif
