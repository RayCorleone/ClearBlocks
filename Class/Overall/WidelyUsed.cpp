#include "Classes/Overall/WidelyUsed.h"
#include "cocos2d.h"

USING_NS_CC;

void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames.\n");
}