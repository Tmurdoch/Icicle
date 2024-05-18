#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_resize.h"
#include "stb_image_write.h"

#include <iostream>;

void free_image(unsigned char* image) {
	stbi_image_free(image);
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

unsigned char* load_texture(char* image_path, int* width, int* height, int* channels) {      
	unsigned char* pixels = stbi_load(convertPath(image_path), width, height, channels, STBI_rgb_alpha);

    if (!pixels) {
        std::cerr << "Failed to load image: " << image_path << std::endl;
        return NULL;
    }
	return pixels;
}