#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_resize.h"
#include "stb_image_write.h"

/*
 * populates width, height, and channels with data from stbi
* return value is pointer to pixel data
* or NULL on allocation/corruption failure
*
* - see stb_image.h for more info
*/
unsigned char* load_image_from_file(char* path, int* width, int* height, int* channels) {
#ifdef WIN32
	//requires absolute path if not in same directory as file
	unsigned char* pixels = stbi_load(path, width, height, channels, STBI_rgb_alpha);
#else       
	unsigned char* pixels = stbi_load(path, width, height, channels, STBI_rgb_alpha);
#endif
	return pixels;
}



/*
converts given path to the correct operating system format
*/
char* convertPath(char* path) {
    #ifdef WIN32 // we're on Windows
        // Windows paths use backslashes
        const char separator = '\\';
    #else // we're on Linux
        // Linux paths use forward slashes
        const char separator = '/';
    #endif

    size_t pathLength = strlen(path);

    // Replace any incorrect separators in the original path
    for (size_t i = 0; i <= pathLength; ++i) {
        path[i] = (path[i] == '\\' || path[i] == '/') ? separator : path[i];
    }

    return path;
}

void free_image(unsigned char* image) {
	stbi_image_free(image);
}
