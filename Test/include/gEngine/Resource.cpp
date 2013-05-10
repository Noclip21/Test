#include "Resource.h"
using namespace utils;



bool Resource::hlInitialized = false;

vector<Resource::sPackage*> Resource::packages;



bool Resource::cache(string file)
{
	if(file.size() <= 0) return false;

	init();

	if(findPackage(file) >= 0) return false;
	

	sPackage *s_package = new sPackage;
			  s_package->name = file;
			  packages.push_back(s_package);

	return extractPackageFile(file,s_package);
}

void Resource::dump(string package)
{
	int id = findPackage(package);

	if(id >= 0)
	{
		while(packages[id]->files.size() > 0)
		{
			delete[] packages[id]->files[0]->data;
						packages[id]->files[0]->data = NULL;
			delete packages[id]->files[0];
					packages[id]->files[0] = NULL;

			removeObject(packages[id]->files[0],packages[id]->files);
		}

		delete	packages[id];
				packages[id] = NULL;
			
		removeObject(packages[id],packages);
	}
}

bool Resource::fetch(string file,void **data,int *size)
{
	if(file.size() > 0)
		for(size_t i=0; i<packages.size(); ++i)
			for(size_t j=0; j<packages[i]->files.size(); ++j)
				if(file.compare(packages[i]->files[j]->name) == 0)
				{
					*data = packages[i]->files[j]->data;
					*size = packages[i]->files[j]->size;
					return true;
				}

	return false;
}



void Resource::init()
{
	if(!hlInitialized)
	{
		hlInitialize();
		hlInitialized = true;
	}
}



int Resource::findPackage(string package)
{
	for(size_t i=0; i<packages.size(); ++i)
		if(package.compare(packages[i]->name) == 0)
			return i;
	return -1;
}

bool Resource::extractPackageFile(string file,sPackage *s_package)
{
	hlUInt package = 0;
	if(!hlCreatePackage(hlGetPackageTypeFromName(file.c_str()),&package)) return false;
	hlBindPackage(package);

	if(!hlPackageOpenFile(file.c_str(),HL_MODE_READ | HL_MODE_QUICK_FILEMAPPING)) return false;

	bool ok = scanPackageDir(hlPackageGetRoot(),s_package);

	hlPackageClose();

	return ok;
}

bool Resource::extractPackageMem(HLDirectoryItem *item,sPackage *s_package)
{

	HLStream *stream = 0;
	if(!hlFileCreateStream(item,&stream)) return false;

	if(!hlStreamOpen(stream,HL_MODE_READ)) return false;

	hlUInt package = 0;
	if(!hlCreatePackage(hlGetPackageTypeFromStream(stream),&package)) return false;
	hlBindPackage(package);

	if(!hlPackageOpenStream(stream,HL_MODE_READ | HL_MODE_QUICK_FILEMAPPING)) return false;

	bool ok = scanPackageDir(hlPackageGetRoot(),s_package);

	hlPackageClose();
	hlStreamClose(stream);
	hlFileReleaseStream(item,stream);

	return ok;
}
bool Resource::scanPackageDir(HLDirectoryItem *dir,sPackage *s_package)
{
	int filesCount = hlFolderGetCount(dir);

	if(filesCount <= 0) return false;
	
	for(int i=0; i<filesCount; ++i)
	{
		HLDirectoryItem *item = hlFolderGetItem(dir,i);
		switch(hlItemGetType(item))
		{
			case(HL_ITEM_FOLDER):{
				if(!scanPackageDir(item,s_package)) return false;
				break;
			}
			case(HL_ITEM_FILE):{
				if(!extractPackageMem(item,s_package))
					if(!cacheItem(item,s_package))
						return false;
				break;
			}
		}
	}
	return true;
}
bool Resource::cacheItem(HLDirectoryItem *item,sPackage *package)
{
	if(hlItemGetType(item) == HL_ITEM_FILE)
	{					
		HLStream *stream = 0;
		if(!hlFileCreateStream(item,&stream)) return false;

		if(!hlStreamOpen(stream,HL_MODE_READ)) return false;
			
		sFile *s_file = new sFile;
				s_file->name = string(hlItemGetName(item));
				s_file->size = hlStreamGetStreamSize(stream);
				s_file->data = new char[s_file->size];
				package->files.push_back(s_file);

		int i = 0;
		while(hlStreamReadChar(stream,&s_file->data[i]) && i < s_file->size) i++;
			
		hlStreamClose(stream);
		hlFileReleaseStream(item,stream);
	}
	return true;
}