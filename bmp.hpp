#ifndef _BMP_
#define _BMP_

#include <vector>
#include <cstdio>
#include <cstdint>

using namespace std;

class BitmapFileHeader
{
public:
	uint8_t B;
	uint8_t M;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
	uint8_t buf[14];

	void bufTOparam();
	void paramTObuf();
};

class BitmapInfoHeader
{
public:
	uint32_t biSize;
	uint32_t biWidth;
	uint32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;
	uint32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
	uint8_t buf[40];

	void bufTOparam();
	void paramTObuf();
};

typedef union RGBQUAD_type
{
	uint8_t buf[256 * 4];
	uint8_t palette[256][4];
} RGBQUAD;

class BMP
{
public:
	~BMP();
	void open_img(const char* filename, vector<vector<uint8_t>>& img_R, vector<vector<uint8_t>>& img_G, vector<vector<uint8_t>>& img_B);
	void save_img(const char* filename, vector<vector<uint8_t>>& img_R, vector<vector<uint8_t>>& img_G, vector<vector<uint8_t>>& img_B);
	
private:
	BitmapFileHeader file_header;
	BitmapInfoHeader info_header;
	RGBQUAD rgbquad;
	uint8_t* image_data = nullptr;
	int width_gap;
	void get_bmp_pixel(int x, int y, uint8_t& pixel_r, uint8_t& pixel_g, uint8_t& pixel_b);
	void set_bmp_pixel(int x, int y, uint8_t pixel_r, uint8_t pixel_g, uint8_t pixel_b);
	void img_data_to_vector(vector<vector<uint8_t>>& img_R, vector<vector<uint8_t>>& img_G, vector<vector<uint8_t>>& img_B);
	void vector_to_img_data(vector<vector<uint8_t>>& img_R, vector<vector<uint8_t>>& img_G, vector<vector<uint8_t>>& img_B);
};

#endif /* _BMP_ */
