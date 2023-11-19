#pragma once

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_resize.h"
#include "stb_image_write.h"


/*
* pupulates width, height, and channels with data from stbi
*/
unsigned char* load_image(int* width, int* height, int* channels) {
#ifdef WIN32
	//requires absolute path if not in same directory as file
	unsigned char* pixels = stbi_load("D:\\Projects\\VSIcicle\\Tests\\editor\\textures\\texture.png", width, height, channels, STBI_rgb_alpha);
#else       
	unsigned char* pixels = stbi_load("textures/texture.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
#endif
	return pixels;
}

void free_image(unsigned char* image) {
	stbi_image_free(image);
}