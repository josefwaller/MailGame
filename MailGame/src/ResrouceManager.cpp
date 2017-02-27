#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}
ResourceManager ResourceManager::r = ResourceManager();

ResourceManager * ResourceManager::get()
{
	return &r;
}