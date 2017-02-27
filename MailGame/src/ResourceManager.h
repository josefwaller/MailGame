#pragma once
class ResourceManager
{
public:
	ResourceManager();
	ResourceManager * get();

private:
	static ResourceManager r;

};