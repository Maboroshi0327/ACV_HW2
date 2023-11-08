#include "bmp.hpp"

void BitmapFileHeader::bufTOparam()
{
	int b0, b1, b2, b3;

	b0 = (BitmapFileHeader::buf[0] & 0xff);
	b1 = (BitmapFileHeader::buf[1] & 0xff);
	BitmapFileHeader::B = (uint8_t)b0;
	BitmapFileHeader::M = (uint8_t)b1;

	b0 = (BitmapFileHeader::buf[2] & 0xff);
	b1 = (BitmapFileHeader::buf[3] & 0xff);
	b2 = (BitmapFileHeader::buf[4] & 0xff);
	b3 = (BitmapFileHeader::buf[5] & 0xff);
	BitmapFileHeader::bfSize = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

	b0 = (BitmapFileHeader::buf[6] & 0xff);
	b1 = (BitmapFileHeader::buf[7] & 0xff);
	BitmapFileHeader::bfReserved1 = (uint16_t)((b1 << 8) + b0);

	b0 = (BitmapFileHeader::buf[8] & 0xff);
	b1 = (BitmapFileHeader::buf[9] & 0xff);
	BitmapFileHeader::bfReserved2 = (uint16_t)((b1 << 8) + b0);

	b0 = (BitmapFileHeader::buf[10] & 0xff);
	b1 = (BitmapFileHeader::buf[11] & 0xff);
	b2 = (BitmapFileHeader::buf[12] & 0xff);
	b3 = (BitmapFileHeader::buf[13] & 0xff);
	BitmapFileHeader::bfOffBits = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);
}

void BitmapFileHeader::paramTObuf()
{
	BitmapFileHeader::buf[0] = BitmapFileHeader::B;
	BitmapFileHeader::buf[1] = BitmapFileHeader::M;

	BitmapFileHeader::buf[2] = BitmapFileHeader::bfSize & 0xff;
	BitmapFileHeader::buf[3] = (BitmapFileHeader::bfSize >> 8) & 0xff;
	BitmapFileHeader::buf[4] = (BitmapFileHeader::bfSize >> 16) & 0xff;
	BitmapFileHeader::buf[5] = (BitmapFileHeader::bfSize >> 24) & 0xff;

	BitmapFileHeader::buf[6] = BitmapFileHeader::bfReserved1 & 0xff;
	BitmapFileHeader::buf[7] = (BitmapFileHeader::bfReserved1 >> 8) & 0xff;

	BitmapFileHeader::buf[8] = BitmapFileHeader::bfReserved2 & 0xff;
	BitmapFileHeader::buf[9] = (BitmapFileHeader::bfReserved2 >> 8) & 0xff;

	BitmapFileHeader::buf[10] = BitmapFileHeader::bfOffBits & 0xff;
	BitmapFileHeader::buf[11] = (BitmapFileHeader::bfOffBits >> 8) & 0xff;
	BitmapFileHeader::buf[12] = (BitmapFileHeader::bfOffBits >> 16) & 0xff;
	BitmapFileHeader::buf[13] = (BitmapFileHeader::bfOffBits >> 24) & 0xff;
}

void BitmapInfoHeader::bufTOparam()
{
	int b0, b1, b2, b3;

	b0 = (BitmapInfoHeader::buf[0] & 0xff);
	b1 = (BitmapInfoHeader::buf[1] & 0xff);
	b2 = (BitmapInfoHeader::buf[2] & 0xff);
	b3 = (BitmapInfoHeader::buf[3] & 0xff);
	BitmapInfoHeader::biSize = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

	b0 = (BitmapInfoHeader::buf[4] & 0xff);
	b1 = (BitmapInfoHeader::buf[5] & 0xff);
	b2 = (BitmapInfoHeader::buf[6] & 0xff);
	b3 = (BitmapInfoHeader::buf[7] & 0xff);
	BitmapInfoHeader::biWidth = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

	b0 = (BitmapInfoHeader::buf[8] & 0xff);
	b1 = (BitmapInfoHeader::buf[9] & 0xff);
	b2 = (BitmapInfoHeader::buf[10] & 0xff);
	b3 = (BitmapInfoHeader::buf[11] & 0xff);
	BitmapInfoHeader::biHeight = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

	b0 = (BitmapInfoHeader::buf[12] & 0xff);
	b1 = (BitmapInfoHeader::buf[13] & 0xff);
	BitmapInfoHeader::biPlanes = (uint16_t)((b1 << 8) + b0);

	b0 = (BitmapInfoHeader::buf[14] & 0xff);
	b1 = (BitmapInfoHeader::buf[15] & 0xff);
	BitmapInfoHeader::biBitCount = (uint16_t)((b1 << 8) + b0);

	b0 = (BitmapInfoHeader::buf[16] & 0xff);
	b1 = (BitmapInfoHeader::buf[17] & 0xff);
	b2 = (BitmapInfoHeader::buf[18] & 0xff);
	b3 = (BitmapInfoHeader::buf[19] & 0xff);
	BitmapInfoHeader::biCompression = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

	b0 = (BitmapInfoHeader::buf[20] & 0xff);
	b1 = (BitmapInfoHeader::buf[21] & 0xff);
	b2 = (BitmapInfoHeader::buf[22] & 0xff);
	b3 = (BitmapInfoHeader::buf[23] & 0xff);
	BitmapInfoHeader::biSizeImage = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

	b0 = (BitmapInfoHeader::buf[24] & 0xff);
	b1 = (BitmapInfoHeader::buf[25] & 0xff);
	b2 = (BitmapInfoHeader::buf[26] & 0xff);
	b3 = (BitmapInfoHeader::buf[27] & 0xff);
	BitmapInfoHeader::biXPelsPerMeter = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

	b0 = (BitmapInfoHeader::buf[28] & 0xff);
	b1 = (BitmapInfoHeader::buf[29] & 0xff);
	b2 = (BitmapInfoHeader::buf[30] & 0xff);
	b3 = (BitmapInfoHeader::buf[31] & 0xff);
	BitmapInfoHeader::biYPelsPerMeter = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

	b0 = (BitmapInfoHeader::buf[32] & 0xff);
	b1 = (BitmapInfoHeader::buf[33] & 0xff);
	b2 = (BitmapInfoHeader::buf[34] & 0xff);
	b3 = (BitmapInfoHeader::buf[35] & 0xff);
	BitmapInfoHeader::biClrUsed = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);

	b0 = (BitmapInfoHeader::buf[36] & 0xff);
	b1 = (BitmapInfoHeader::buf[37] & 0xff);
	b2 = (BitmapInfoHeader::buf[38] & 0xff);
	b3 = (BitmapInfoHeader::buf[39] & 0xff);
	BitmapInfoHeader::biClrImportant = (uint32_t)((b3 << 24) + (b2 << 16) + (b1 << 8) + b0);
}

void BitmapInfoHeader::paramTObuf()
{
	BitmapInfoHeader::buf[0] = BitmapInfoHeader::biSize & 0xff;
	BitmapInfoHeader::buf[1] = (BitmapInfoHeader::biSize >> 8) & 0xff;
	BitmapInfoHeader::buf[2] = (BitmapInfoHeader::biSize >> 16) & 0xff;
	BitmapInfoHeader::buf[3] = (BitmapInfoHeader::biSize >> 24) & 0xff;

	BitmapInfoHeader::buf[4] = BitmapInfoHeader::biWidth & 0xff;
	BitmapInfoHeader::buf[5] = (BitmapInfoHeader::biWidth >> 8) & 0xff;
	BitmapInfoHeader::buf[6] = (BitmapInfoHeader::biWidth >> 16) & 0xff;
	BitmapInfoHeader::buf[7] = (BitmapInfoHeader::biWidth >> 24) & 0xff;

	BitmapInfoHeader::buf[8] = BitmapInfoHeader::biHeight & 0xff;
	BitmapInfoHeader::buf[9] = (BitmapInfoHeader::biHeight >> 8) & 0xff;
	BitmapInfoHeader::buf[10] = (BitmapInfoHeader::biHeight >> 16) & 0xff;
	BitmapInfoHeader::buf[11] = (BitmapInfoHeader::biHeight >> 24) & 0xff;

	BitmapInfoHeader::buf[12] = BitmapInfoHeader::biPlanes & 0xff;
	BitmapInfoHeader::buf[13] = (BitmapInfoHeader::biPlanes >> 8) & 0xff;

	BitmapInfoHeader::buf[14] = BitmapInfoHeader::biBitCount & 0xff;
	BitmapInfoHeader::buf[15] = (BitmapInfoHeader::biBitCount >> 8) & 0xff;

	BitmapInfoHeader::buf[16] = BitmapInfoHeader::biCompression & 0xff;
	BitmapInfoHeader::buf[17] = (BitmapInfoHeader::biCompression >> 8) & 0xff;
	BitmapInfoHeader::buf[18] = (BitmapInfoHeader::biCompression >> 16) & 0xff;
	BitmapInfoHeader::buf[19] = (BitmapInfoHeader::biCompression >> 24) & 0xff;

	BitmapInfoHeader::buf[20] = BitmapInfoHeader::biSizeImage & 0xff;
	BitmapInfoHeader::buf[21] = (BitmapInfoHeader::biSizeImage >> 8) & 0xff;
	BitmapInfoHeader::buf[22] = (BitmapInfoHeader::biSizeImage >> 16) & 0xff;
	BitmapInfoHeader::buf[23] = (BitmapInfoHeader::biSizeImage >> 24) & 0xff;

	BitmapInfoHeader::buf[24] = BitmapInfoHeader::biXPelsPerMeter & 0xff;
	BitmapInfoHeader::buf[25] = (BitmapInfoHeader::biXPelsPerMeter >> 8) & 0xff;
	BitmapInfoHeader::buf[26] = (BitmapInfoHeader::biXPelsPerMeter >> 16) & 0xff;
	BitmapInfoHeader::buf[27] = (BitmapInfoHeader::biXPelsPerMeter >> 24) & 0xff;

	BitmapInfoHeader::buf[28] = BitmapInfoHeader::biYPelsPerMeter & 0xff;
	BitmapInfoHeader::buf[29] = (BitmapInfoHeader::biYPelsPerMeter >> 8) & 0xff;
	BitmapInfoHeader::buf[30] = (BitmapInfoHeader::biYPelsPerMeter >> 16) & 0xff;
	BitmapInfoHeader::buf[31] = (BitmapInfoHeader::biYPelsPerMeter >> 24) & 0xff;

	BitmapInfoHeader::buf[32] = BitmapInfoHeader::biClrUsed & 0xff;
	BitmapInfoHeader::buf[33] = (BitmapInfoHeader::biClrUsed >> 8) & 0xff;
	BitmapInfoHeader::buf[34] = (BitmapInfoHeader::biClrUsed >> 16) & 0xff;
	BitmapInfoHeader::buf[35] = (BitmapInfoHeader::biClrUsed >> 24) & 0xff;

	BitmapInfoHeader::buf[36] = BitmapInfoHeader::biClrImportant & 0xff;
	BitmapInfoHeader::buf[37] = (BitmapInfoHeader::biClrImportant >> 8) & 0xff;
	BitmapInfoHeader::buf[38] = (BitmapInfoHeader::biClrImportant >> 16) & 0xff;
	BitmapInfoHeader::buf[39] = (BitmapInfoHeader::biClrImportant >> 24) & 0xff;
}

BMP::~BMP()
{
	delete[] BMP::image_data;
}

void BMP::open_img(const char* filename, vector<vector<uint8_t>>& img_R, vector<vector<uint8_t>>& img_G, vector<vector<uint8_t>>& img_B)
{
	FILE* fp;
	if (fopen_s(&fp, filename, "rb") != 0)
	{
		printf("Couldn't find file %s.\n", filename);
		exit(1);
	}

	fread_s(BMP::file_header.buf, 14, sizeof(uint8_t), 14, fp);
	BMP::file_header.bufTOparam();

	fread_s(BMP::info_header.buf, 40, sizeof(uint8_t), 40, fp);
	BMP::info_header.bufTOparam();

	if (BMP::info_header.biBitCount == 8)
	{
		fread_s(BMP::rgbquad.buf, sizeof(BMP::rgbquad.buf), sizeof(uint8_t), 256 * 4, fp);
		int size = ((BMP::info_header.biWidth + 3) & (~3)) * BMP::info_header.biHeight;
		delete[] BMP::image_data;
		BMP::image_data = new uint8_t[size];
		fread_s(BMP::image_data, size, sizeof(uint8_t), size, fp);
	}
	else if (BMP::info_header.biBitCount == 24)
	{
		int size = ((BMP::info_header.biWidth * 3 + 3) & (~3)) * BMP::info_header.biHeight;
		delete[] BMP::image_data;
		BMP::image_data = new uint8_t[size];
		fread_s(BMP::image_data, size, sizeof(uint8_t), size, fp);
	}
	else
	{
		printf("Not supported format!\n");
		exit(1);
	}

	fclose(fp);

	img_data_to_vector(img_R, img_G, img_B);
}

void BMP::save_img(const char* filename, vector<vector<uint8_t>>& img_R, vector<vector<uint8_t>>& img_G, vector<vector<uint8_t>>& img_B)
{
	FILE* fp;
	if (fopen_s(&fp, filename, "wb") != 0)
	{
		printf("Couldn't find file %s.\n", filename);
		exit(1);
	}

	BMP::file_header.B = 'B';
	BMP::file_header.M = 'M';
	int height = (int)img_R.size();
	int width = (int)img_R[0].size();
	int size = ((width * 3 + 3) & (~3)) * height;
	BMP::file_header.bfSize = 54 + size;
	BMP::file_header.bfReserved1 = 0;
	BMP::file_header.bfReserved2 = 0;
	BMP::file_header.bfOffBits = 54;
	BMP::file_header.paramTObuf();
	fwrite(BMP::file_header.buf, sizeof(uint8_t), 14, fp);

	BMP::info_header.biSize = 40;
	BMP::info_header.biWidth = width;
	BMP::info_header.biHeight = height;
	BMP::info_header.biPlanes = 1;
	BMP::info_header.biBitCount = 24;
	BMP::info_header.biCompression = 0;
	BMP::info_header.biSizeImage = 0;
	BMP::info_header.biXPelsPerMeter = 3779;
	BMP::info_header.biYPelsPerMeter = 3779;
	BMP::info_header.biClrUsed = 0;
	BMP::info_header.biClrImportant = 0;
	BMP::info_header.paramTObuf();
	fwrite(BMP::info_header.buf, sizeof(uint8_t), 40, fp);

	delete[] BMP::image_data;
	BMP::image_data = new uint8_t[size];
	vector_to_img_data(img_R, img_G, img_B);
	fwrite(BMP::image_data, sizeof(uint8_t), size, fp);

	fclose(fp);
}

void BMP::img_data_to_vector(vector<vector<uint8_t>>& img_R, vector<vector<uint8_t>>& img_G, vector<vector<uint8_t>>& img_B)
{
	int width = BMP::info_header.biWidth;
	int height = BMP::info_header.biHeight;
	img_R.resize(height);
	img_G.resize(height);
	img_B.resize(height);
	for (int y = 0; y < height; y++)
	{
		img_R[y].resize(width);
		img_G[y].resize(width);
		img_B[y].resize(width);
	}
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			uint8_t r, g, b;
			BMP::get_bmp_pixel(x, y, r, g, b);
			img_R[height - 1 - y][x] = r;
			img_G[height - 1 - y][x] = g;
			img_B[height - 1 - y][x] = b;
		}
	}
}

void BMP::vector_to_img_data(vector<vector<uint8_t>>& img_R, vector<vector<uint8_t>>& img_G, vector<vector<uint8_t>>& img_B)
{
	int width = BMP::info_header.biWidth;
	int height = BMP::info_header.biHeight;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int r = img_R[height - 1 - y][x];
			int g = img_G[height - 1 - y][x];
			int b = img_B[height - 1 - y][x];
			set_bmp_pixel(x, y, r, g, b);
		}
	}
}

void BMP::get_bmp_pixel(int x, int y, uint8_t& pixel_r, uint8_t& pixel_g, uint8_t& pixel_b)
{
	int width, height;
	int offset;

	if (BMP::info_header.biBitCount == 8)
	{
		width = BMP::info_header.biWidth;
		height = BMP::info_header.biHeight;
		offset = y * ((width + 3) & (~3)) + x;
		pixel_b = *(BMP::image_data + offset);
		pixel_g = pixel_b;
		pixel_r = pixel_b;
	}
	else if (BMP::info_header.biBitCount == 24)
	{
		width = BMP::info_header.biWidth;
		height = BMP::info_header.biHeight;
		offset = y * ((width * 3 + 3) & (~3)) + x * 3;
		pixel_b = *(BMP::image_data + offset);
		pixel_g = *(BMP::image_data + offset + 1);
		pixel_r = *(BMP::image_data + offset + 2);
	}
	else
	{
		printf("Not supported format!\n");
		exit(1);
	}
}

void BMP::set_bmp_pixel(int x, int y, uint8_t pixel_r, uint8_t pixel_g, uint8_t pixel_b)
{
	int width, height;
	int offset;

	if (BMP::info_header.biBitCount == 8)
	{
		width = BMP::info_header.biWidth;
		height = BMP::info_header.biHeight;
		offset = y * ((width + 3) & (~3)) + x;
		*(BMP::image_data + offset) = pixel_b;
	}
	else if (BMP::info_header.biBitCount == 24)
	{
		width = BMP::info_header.biWidth;
		height = BMP::info_header.biHeight;
		offset = y * ((width * 3 + 3) & (~3)) + x * 3;
		*(BMP::image_data + offset) = pixel_b;
		*(BMP::image_data + offset + 1) = pixel_g;
		*(BMP::image_data + offset + 2) = pixel_r;
	}
	else
	{
		printf("Not supported format!\n");
		exit(1);
	}
}
