#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>
#include <iostream>

#include <SDL.h>

#include <HLLib.h>
#include <Wrapper.h>

#include "Utils.h"
#include "Object.h"
using namespace std;


#include "prologue.h"
class G_DECLSPEC Resource 
{
public:

	static bool cache(string package);
	static void dump(string package);
	static bool fetch(string file,void **data,int *size);

private:

	static bool hlInitialized;
	static void init();

	static int findPackage(string package);
	
	struct sFile
	{
		string	name;
		int		size;
		char	*data;
	};
	struct sPackage
	{
		string			name;
		vector<sFile*>	files;
	};

	static bool extractPackageFile(string file,sPackage *s_package);
	static bool extractPackageMem(HLDirectoryItem *item,sPackage *s_package);
	static bool scanPackageDir(HLDirectoryItem *dir,sPackage *s_package);
	static bool cacheItem(HLDirectoryItem *item,sPackage *s_package);

	static vector<sPackage*> packages;
};
#include "epilogue.h"

#endif