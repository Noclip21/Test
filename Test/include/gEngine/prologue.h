#ifdef PROLOGUE
#error Prologue instanciado multiplas vezes
#endif
#define PROLOGUE


#pragma warning(disable: 4251) // "needs to have dll-interface" Fuck the police


#ifdef _WINDLL // Visual Studio
#	define G_DECLSPEC __declspec(dllexport)
#	define G_EXPTEMPL
#else
#	define G_DECLSPEC __declspec(dllimport)
#	define G_EXPTEMPL extern
#endif