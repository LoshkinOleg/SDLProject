#pragma once
#include <string_view>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <cassert>

#define BMP_HEADER_ID 0x4D42
#define BMP_PIXEL_DATA_LOCATION_OFFSET 10

#define DIB_BITMAPV5HEADER_SIZE 124
#define DIB_HEADER_SIZE_OFFSET 14
#define DIB_WIDTH_OFFSET 18
#define DIB_HEIGHT_OFFSET 22
#define DIB_COLOR_DEPTH_OFFSET 28
#define DIB_COMPRESSION_OFFSET 30

namespace
{
	enum class ImageType : unsigned short
	{
		UNKNOWN = 0xFF,
		BMP = BMP_HEADER_ID
	};
}

enum class ImageCompression : unsigned
{
	UNKNOWN = 0xFFFFFFFF,
	BI_RGB = 0, // No compression.
	BI_RLE8 = 1,
	BI_RLE4 = 2,
	BI_BITFIELDS = 3,
	BI_JPEG = 4,
	BI_PNG = 5,
	BI_ALPHABITFIELDS = 6,
	BI_CMYK = 7,
	BI_CMYKRLE8 = 8,
	BI_CMYKRLE4 = 9
};

class Image
{
public:
	inline Image(std::string_view stemAndExtension)
	{
		Load(stemAndExtension);
	}
	~Image()
	{
		delete[] data_;
	}

	inline size_t GetWidth()
	{
		return width_;
	}

	inline size_t GetHeight()
	{
		return height_;
	}

	inline size_t GetDataLenInPixels()
	{
		return dataLenInPixels_;
	}

	inline ImageCompression GetImageCompressionType()
	{
		return compressionType_;
	}

	/*
	@brief: UNSAFE: returns array of bytes, independant of the way the data is actually encoded! Use in conjonction with GetDataLenInBytes().
	*/
	inline char* GetData()
	{
		return data_;
	}

	inline size_t GetDataLenInBytes()
	{
		return dataLenInPixels_ * (colorDepthInBits_ >> 3); // >> 3 = / 8
	}

	void Load(const std::string_view stemAndExtension)
	{
		std::filesystem::path path(stemAndExtension);
		std::ifstream file(path);
		assert(file.is_open());

		const size_t fileSize = std::filesystem::file_size(path);
		char* data = new char[fileSize];
		file.read(data, fileSize);
		file.close();

		ImageType type = (ImageType) *((unsigned short*)((void*)data));
		assert(type == ImageType::BMP);

		switch (type)
		{
			case ImageType::UNKNOWN:
				{
					assert(true);
				}break;

			case ImageType::BMP:
				{
					const unsigned dibHeaderSize = *(unsigned*)((void*)(data + DIB_HEADER_SIZE_OFFSET));
					assert(dibHeaderSize == DIB_BITMAPV5HEADER_SIZE);

					switch (dibHeaderSize)
					{
						case DIB_BITMAPV5HEADER_SIZE:
							{
								width_ = *(int*)((void*)(data + DIB_WIDTH_OFFSET));
								height_ = *(int*)((void*)(data + DIB_HEIGHT_OFFSET));
								colorDepthInBits_ = *(unsigned short*)((void*)(data + DIB_COLOR_DEPTH_OFFSET));
								compressionType_ = (ImageCompression) *(unsigned*)((void*)(data + DIB_COMPRESSION_OFFSET));
								dataLenInPixels_ = (size_t)width_ * (size_t)height_;

								assert(width_ > 0 && height_ > 0 && colorDepthInBits_ >= 8);

								data_ = new char[dataLenInPixels_ * ((size_t)colorDepthInBits_ >> 3)]; // >> 3 = / 8
								memcpy(data_, data + *(unsigned*)&data[BMP_PIXEL_DATA_LOCATION_OFFSET], dataLenInPixels_ * ((size_t)colorDepthInBits_ >> 3));
							}break;

						default:
							{
								assert(true); // Unmanaged DIB header type.
							}break;
					}
				}break;

			default:
				{
					assert(true);
				}break;
		}

		delete[] data;
	}

private:
	char* data_ = nullptr;
	size_t dataLenInPixels_ = 0;

	unsigned width_ = 0;
	unsigned height_ = 0;
	ImageCompression compressionType_ = ImageCompression::UNKNOWN;

	unsigned short colorDepthInBits_ = 0;
};
