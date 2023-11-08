#include "Image.hpp"

int ImageSize::size()
{
	return ImageSize::rows * ImageSize::columns;
}

ImageSize::ImageSize()
{
	ImageSize::rows = 0;
	ImageSize::columns = 0;
}

ImageSize::ImageSize(int rows, int columns)
{
	ImageSize::rows = rows;
	ImageSize::columns = columns;
}

ImageSize::ImageSize(const ImageSize& source)
{
	ImageSize::rows = source.rows;
	ImageSize::columns = source.columns;
}

ImageSize ImageSize::operator=(const ImageSize& other)
{
	ImageSize::rows = other.rows;
	ImageSize::columns = other.columns;
	return *this;
}

ImageSize ImageSize::operator*(const double& other)
{
	return ImageSize(int(ImageSize::rows * other), int(ImageSize::columns * other));
}

ImageSize ImageSize::operator/(const double& other)
{
	return ImageSize(int(ImageSize::rows / other), int(ImageSize::columns / other));
}

bool ImageSize::operator==(const ImageSize& other)
{
	bool result = ImageSize::rows == other.rows;
	result &= ImageSize::columns == other.columns;
	return result;
}

bool ImageSize::operator!=(const ImageSize& other)
{
	bool result = ImageSize::rows != other.rows;
	result |= ImageSize::columns != other.columns;
	return result;
}

void Image::openBMP(const char* FileName)
{
	Image::bmp.open_img(FileName, Image::img_0, Image::img_1, Image::img_2);
	Image::color = ColorSpace::RGB;
	Image::size.rows = (int)Image::img_0.size();
	Image::size.columns = (int)Image::img_0[0].size();
}

void Image::saveBMP(const char* FileName, bool printName)
{
	bool flag = false;
	if (Image::color == ColorSpace::RGB)
	{
		flag = true;
		Image::bmp.save_img(FileName, Image::img_0, Image::img_1, Image::img_2);
	}
	if (Image::color == ColorSpace::GRAY || Image::color == ColorSpace::Binary)
	{
		flag = true;
		Image::bmp.save_img(FileName, Image::img_0, Image::img_0, Image::img_0);
	}

	if (printName && flag)
		cout << "Output file: " << FileName << endl;
}

void Image::saveBMP(const char* FileName, int channel, bool printName)
{
	bool flag = false;
	switch (channel)
	{
	case 0:
		flag = true;
		Image::bmp.save_img(FileName, Image::img_0, Image::img_0, Image::img_0);
		break;

	case 1:
		flag = true;
		Image::bmp.save_img(FileName, Image::img_1, Image::img_1, Image::img_1);
		break;

	case 2:
		flag = true;
		Image::bmp.save_img(FileName, Image::img_2, Image::img_2, Image::img_2);
		break;
	}

	if (printName && flag)
		cout << "Output file: " << FileName << endl;
}

void Image::rgb2gray()
{
	Image::color = ColorSpace::GRAY;
	for (int r = 0; r < Image::size.rows; r++)
	{
		for (int c = 0; c < Image::size.columns; c++)
		{
			Image::img_0[r][c] = (uint8_t)round(
				0.299 * Image::img_0[r][c]
				+ 0.587 * Image::img_1[r][c]
				+ 0.114 * Image::img_2[r][c]
				);
		}
	}
}

void Image::rgb2hsv()
{
	Image::color = ColorSpace::HSV;
	for (int r = 0; r < Image::size.rows; r++)
	{
		for (int c = 0; c < Image::size.columns; c++)
		{
			double R = Image::img_0[r][c] / 255.0, G = Image::img_1[r][c] / 255.0, B = Image::img_2[r][c] / 255.0;
			double max_v = max({ R, G, B });
			double min_v = min({ R, G, B });
			double V = max_v;

			double S = (V != 0.0) ? ((V - min_v) / V) : 0.0;

			double H;
			if (V == R)
				H = 60.0 * (G - B) / (V - min_v);
			if (V == G)
				H = 120.0 + 60.0 * (B - R) / (V - min_v);
			if (V == B)
				H = 240.0 + 60.0 * (R - G) / (V - min_v);
			if (R == G && R == B)
				H = 0;
			if (H < 0)
				H = H + 360;

			Image::img_0[r][c] = (uint8_t)(255 * V);
			Image::img_1[r][c] = (uint8_t)(255 * S);
			Image::img_2[r][c] = Image::mapping(H, 0.0, 359.0, 0, 255);
		}
	}
}

void Image::rgb2hsl()
{
	Image::color = ColorSpace::HSL;
	for (int r = 0; r < Image::size.rows; r++)
	{
		for (int c = 0; c < Image::size.columns; c++)
		{
			double R = Image::img_0[r][c] / 255.0, G = Image::img_1[r][c] / 255.0, B = Image::img_2[r][c] / 255.0;
			double max_v = max({ R, G, B });
			double min_v = min({ R, G, B });
			double L = (max_v + min_v) / 2;

			double S;
			if (max_v == 0.0)
				S = 0;
			else
				S = (L < 0.5) ? ((max_v - min_v) / (max_v + min_v)) : ((max_v - min_v) / (2 - max_v - min_v));

			double H;
			if (max_v == R)
				H = 60.0 * (G - B) / (max_v - min_v);
			if (max_v == G)
				H = 120.0 + 60.0 * (B - R) / (max_v - min_v);
			if (max_v == B)
				H = 240.0 + 60.0 * (R - G) / (max_v - min_v);
			if (R == G && R == B)
				H = 0;
			if (H < 0)
				H = H + 360;

			Image::img_0[r][c] = (uint8_t)(255 * L);
			Image::img_1[r][c] = (uint8_t)(255 * S);
			Image::img_2[r][c] = Image::mapping(H, 0.0, 359.0, 0, 255);
		}
	}
}

void Image::threshold(uint8_t th)
{
	if (Image::color == ColorSpace::RGB)
	{
		for (int r = 0; r < Image::size.rows; r++)
			for (int c = 0; c < Image::size.columns; c++)
			{
				Image::img_0[r][c] = (Image::img_0[r][c] < th) ? 0 : 255;
				Image::img_1[r][c] = (Image::img_1[r][c] < th) ? 0 : 255;
				Image::img_2[r][c] = (Image::img_2[r][c] < th) ? 0 : 255;
			}
	}
	else if (Image::color == ColorSpace::GRAY)
	{
		Image::color = ColorSpace::Binary;
		for (int r = 0; r < Image::size.rows; r++)
			for (int c = 0; c < Image::size.columns; c++)
				Image::img_0[r][c] = (Image::img_0[r][c] < th) ? 0 : 255;
	}
}

void Image::threshold(uint8_t th, int channel)
{
	vector<vector<uint8_t>>* img = nullptr;
	switch (channel)
	{
	case 0:
		img = &(Image::img_0);
		break;

	case 1:
		img = &(Image::img_1);
		break;

	case 2:
		img = &(Image::img_2);
		break;
	}
	if (img != nullptr)
	{
		for (int r = 0; r < Image::size.rows; r++)
			for (int c = 0; c < Image::size.columns; c++)
				(*img)[r][c] = ((*img)[r][c] < th) ? 0 : 255;
	}
}

Image::Image()
{
	Image::size = ImageSize(0, 0);
}

Image::Image(const Image& source)
{
	Image::color = source.color;
	Image::size = source.size;
	Image::img_0 = source.img_0;
	Image::img_1 = source.img_1;
	Image::img_2 = source.img_2;
}

Image::Image(const vector<vector<uint8_t>>& img_0)
{
	Image::color = ColorSpace::GRAY;
	Image::size.rows = (int)img_0.size();
	Image::size.columns = (int)img_0[0].size();
	Image::img_0 = img_0;
}

Image::Image(const vector<vector<uint8_t>>& img_0, const vector<vector<uint8_t>>& img_1, const vector<vector<uint8_t>>& img_2)
{
	Image::color = ColorSpace::RGB;
	Image::size.rows = (int)img_0.size();
	Image::size.columns = (int)img_0[0].size();
	Image::img_0 = img_0;
	Image::img_1 = img_1;
	Image::img_2 = img_2;
}

Image::Image(ImageSize size, uint8_t value)
{
	Image::color = ColorSpace::RGB;
	Image::size = size;
	Image::img_0 = vector<vector<uint8_t>>(size.rows, vector<uint8_t>(size.columns, value));
	Image::img_1 = vector<vector<uint8_t>>(size.rows, vector<uint8_t>(size.columns, value));
	Image::img_2 = vector<vector<uint8_t>>(size.rows, vector<uint8_t>(size.columns, value));
}

Image Image::operator=(const Image& other)
{
	Image::color = other.color;
	Image::size = other.size;
	Image::img_0 = other.img_0;
	Image::img_1 = other.img_1;
	Image::img_2 = other.img_2;
	return *this;
}

uint8_t Image::mapping(double value, double min_f, double max_f, uint8_t min_i, uint8_t max_i)
{
	return (uint8_t)((value - min_f) / (max_f - min_f) * (max_i - min_i) + min_i);
}

vector<vector<uint8_t>> Image::padding(vector<vector<uint8_t>>& img, int pad)
{
	vector<vector<uint8_t>> img_pad(size.rows + 2 * pad, vector<uint8_t>(size.columns + 2 * pad, 0));

	for (int r = 0; r < size.rows; r++)
		for (int c = 0; c < size.columns; c++)
			img_pad[r + pad][c + pad] = img[r][c];

	for (int r = 0; r < size.rows + pad * 2; r++)
	{
		for (int c = 0; c < size.columns + pad * 2; c++)
		{
			if (r < pad && c < pad)
				img_pad[r][c] = img_pad[2 * pad - 1 - r][2 * pad - 1 - c];
			else if (r < pad && pad <= c && c < size.columns + pad)
				img_pad[r][c] = img_pad[2 * pad - 1 - r][c];
			else if (r < pad && c >= size.columns + pad)
				img_pad[r][c] = img_pad[2 * pad - 1 - r][2 * (size.columns + pad) - 1 - c];
			else if (pad <= r && r < size.rows + pad && c < pad)
				img_pad[r][c] = img_pad[r][2 * pad - 1 - c];
			else if (pad <= r && r < size.rows + pad && c >= size.columns + pad)
				img_pad[r][c] = img_pad[r][2 * (size.columns + pad) - 1 - c];
			else if (r >= size.rows + pad && c < pad)
				img_pad[r][c] = img_pad[2 * (size.rows + pad) - 1 - r][2 * pad - 1 - c];
			else if (r >= size.rows + pad && pad <= c && c < size.columns + pad)
				img_pad[r][c] = img_pad[2 * (size.rows + pad) - 1 - r][c];
			else if (r >= size.rows + pad && c >= size.columns + pad)
				img_pad[r][c] = img_pad[2 * (size.rows + pad) - 1 - r][2 * (size.columns + pad) - 1 - c];
		}
	}

	return img_pad;
}

double Coordinate::length(const Coordinate& source)
{
	double dx = Coordinate::column - source.column;
	double dy = Coordinate::row - source.row;
	return sqrt(dx * dx + dy * dy);
}

double Coordinate::orientation(const Coordinate& source)
{
	double numerator = Coordinate::row - source.row;
	double denominator = Coordinate::column - source.column;
	return atan(-numerator / denominator);
}

Coordinate::Coordinate()
{
	Coordinate::row = 0;
	Coordinate::column = 0;
}

Coordinate::Coordinate(int row, int column)
{
	Coordinate::row = row;
	Coordinate::column = column;
}

Coordinate::Coordinate(const Coordinate& source)
{
	Coordinate::row = source.row;
	Coordinate::column = source.column;
}

Coordinate Coordinate::operator=(const Coordinate& other)
{
	Coordinate::row = other.row;
	Coordinate::column = other.column;
	return *this;
}

bool Coordinate::operator==(const Coordinate& other)
{
	bool result = Coordinate::row == other.row;
	result &= Coordinate::column == other.column;
	return result;
}

bool Coordinate::operator!=(const Coordinate& other)
{
	bool result = Coordinate::row != other.row;
	result |= Coordinate::column != other.column;
	return result;
}

CCpair::CCpair(const int& up, const int& left)
{
	CCpair::up = up;
	CCpair::left = left;
}

void ConnectedComponents::label()
{
	int rows = this->size.rows;
	int columns = this->size.columns;
	this->numOfRegion = 0;
	this->table = vector<vector<int>>(rows, vector<int>(columns, 0));
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			this->table[r][c] = this->img_0[r][c] == 255;

	vector<CCpair> pair;
	int region = 0;
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
		{
			if (this->table[r][c] == 1)
			{
				int up = (r - 1 >= 0) ? this->table[r - 1][c] : 0;
				int left = (c - 1 >= 0) ? this->table[r][c - 1] : 0;
				if (up >= 1)
					this->table[r][c] = up;
				else if (left >= 1)
					this->table[r][c] = left;
				else
					this->table[r][c] = ++region;

				if (up >= 1 && left >= 1 && up != left)
					pair.push_back(CCpair(up, left));
			}
		}

	vector<vector<bool>> regionTable(region, vector<bool>(region, 0));
	for (int i = 0; i < region; i++)
	{
		for (auto& j : pair)
		{
			if (i == j.up)
				regionTable[i - 1][j.left - 1] = true;
			if (i == j.left)
				regionTable[i - 1][j.up - 1] = true;
		}
	}

	vector<vector<int>> equivalence;
	for (int i = 0; i < region; i++)
	{
		int exist = this->checkEquivalence(equivalence, i + 1);
		if (exist > equivalence.size())
		{
			equivalence.push_back(vector<int>(1, i + 1));
			this->madeEqList(equivalence, regionTable, i + 1);
			this->numOfRegion++;
		}
	}

	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			if (this->table[r][c] > 0)
				this->table[r][c] = this->checkEquivalence(equivalence, this->table[r][c]);
}

void ConnectedComponents::largest_regions(int num)
{
	if (num > this->numOfRegion)
	{
		cout << "Doesn't have enough region." << endl;
		return;
	}

	vector<int> hist(this->numOfRegion, 0);
	for (auto& i : this->table)
		for (auto& j : i)
		{
			if (j > 0)
				hist[j - 1]++;
		}

	vector<int> sort_v = hist;
	sort(sort_v.begin(), sort_v.end(), greater<int>());
	vector<int> maxRegion(num, 0);
	for (int i = 0; i < num; i++)
	{
		int j;
		for (j = 0; j < this->numOfRegion; j++)
			if (sort_v[i] == hist[j])
				break;
		maxRegion[i] = j + 1;
	}

	this->color = ColorSpace::RGB;
	int rows = this->size.rows;
	int columns = this->size.columns;
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
		{
			this->img_0[r][c] = (this->table[r][c] > 0) ? 255 : 0;
			this->img_1[r][c] = this->img_0[r][c];
			this->img_2[r][c] = this->img_0[r][c];
		}

	for (int i = 0; i < num; i++)
	{
		int area = 0;
		vector<Coordinate> coords;
		for (int r = 0; r < rows; r++)
			for (int c = 0; c < columns; c++)
				if (this->table[r][c] == maxRegion[i])
				{
					coords.push_back(Coordinate(r, c));
					area++;
				}
		cout << i + 1 << " rigion:" << endl;
		cout << "area-> " << area << endl;

		Coordinate centroid;
		int up = coords[0].row, down = coords[0].row;
		int left = coords[0].column, right = coords[0].column;
		for (auto& coord : coords)
		{
			int r = coord.row, c = coord.column;
			centroid.row += r;
			centroid.column += c;
			if (r < up)
				up = r;
			if (r > down)
				down = r;
			if (c < left)
				left = c;
			if (c > right)
				right = c;
		}
		cout << "centroid-> (" << (double)centroid.row / area << ", " << (double)centroid.column / area << ")" << endl;

		Coordinate p[8];
		for (int c = left; c <= right; c++)
		{
			int flagUp = 0, flagDown = 0;
			if (this->table[up][c] > 0 && flagUp++ == 0)
				p[0] = Coordinate(up, c);
			if (this->table[down][c] > 0 && flagDown++ == 0)
				p[5] = Coordinate(down, c);
			if (flagUp == 1 && flagDown == 1)
				break;
		}
		for (int c = right; c >= left; c--)
		{
			int flagUp = 0, flagDown = 0;
			if (this->table[up][c] > 0 && flagUp++ == 0)
				p[1] = Coordinate(up, c);
			if (this->table[down][c] > 0 && flagDown++ == 0)
				p[4] = Coordinate(down, c);
			if (flagUp == 1 && flagDown == 1)
				break;
		}
		for (int r = up; r <= down; r++)
		{
			int flagLeft = 0, flagRight = 0;
			if (this->table[r][left] > 0 && flagLeft++ == 0)
				p[7] = Coordinate(r, left);
			if (this->table[r][right] > 0 && flagRight++ == 0)
				p[2] = Coordinate(r, right);
			if (flagLeft == 1 && flagRight == 1)
				break;
		}
		for (int r = down; r >= up; r--)
		{
			int flagLeft = 0, flagRight = 0;
			if (this->table[r][left] > 0 && flagLeft++ == 0)
				p[6] = Coordinate(r, left);
			if (this->table[r][right] > 0 && flagRight++ == 0)
				p[3] = Coordinate(r, right);
			if (flagLeft == 1 && flagRight == 1)
				break;
		}
		double m[4] = { 0 };
		m[0] = p[0].length(p[4]);
		m[1] = p[1].length(p[5]);
		m[2] = p[2].length(p[6]);
		m[3] = p[3].length(p[7]);
		int max_L = (int)distance(m, max_element(m, m + 3));
		double max_O = p[max_L].orientation(p[max_L + 4]);
		max_O = max_O / M_PI * 180.0;
		cout << "longest length-> " << m[max_L] << endl;
		cout << "orientation-> " << max_O << endl << endl;

		up = (up - 1 < 0) ? 0 : up - 1;
		down = (down + 1 > rows) ? rows : down + 1;
		left = (left - 1 < 0) ? 0 : left - 1;
		right = (right + 1 > columns) ? columns : right + 1;
		for (int r = up; r <= down; r++)
		{
			this->img_0[r][left] = 255;
			this->img_1[r][left] = 0;
			this->img_2[r][left] = 0;
			this->img_0[r][right] = 255;
			this->img_1[r][right] = 0;
			this->img_2[r][right] = 0;
		}
		for (int c = left; c <= right; c++)
		{
			this->img_0[up][c] = 255;
			this->img_1[up][c] = 0;
			this->img_2[up][c] = 0;
			this->img_0[down][c] = 255;
			this->img_1[down][c] = 0;
			this->img_2[down][c] = 0;
		}
	}
}

void ConnectedComponents::RegionsToGray()
{
	this->color = ColorSpace::GRAY;
	int rows = this->size.rows;
	int columns = this->size.columns;
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
		{
			this->img_0[r][c] = (uint8_t)(this->table[r][c] / (double)this->numOfRegion * 255);
		}
}

ConnectedComponents::ConnectedComponents()
{
	this->numOfRegion = 0;
}

ConnectedComponents::ConnectedComponents(const vector<vector<uint8_t>>& img)
{
	int rows = (int)img.size();
	int columns = (int)img[0].size();
	ConnectedComponents::numOfRegion = 0;
	ConnectedComponents::table = vector<vector<int>>(rows, vector<int>(columns, 0));
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			ConnectedComponents::table[r][c] = img[r][c] == 255;
}

void ConnectedComponents::madeEqList(vector<vector<int>>& equivalence, const vector<vector<bool>>& regionTable, int region)
{
	for (int i = 0; i < regionTable.size(); i++)
	{
		if (regionTable[region - 1][i] == true)
		{
			int exist1 = this->checkEquivalence(equivalence, i + 1);
			if (exist1 > equivalence.size())
			{
				equivalence.back().push_back(i + 1);
				this->madeEqList(equivalence, regionTable, i + 1);
				for (int j = 0; j < regionTable.size(); j++)
				{
					if (regionTable[j][i] == true)
					{
						int exist2 = this->checkEquivalence(equivalence, i + 1);
						if (exist2 > equivalence.size())
						{
							equivalence.back().push_back(j + 1);
							this->madeEqList(equivalence, regionTable, j + 1);
						}
					}
				}
			}
		}
	}
}

int ConnectedComponents::checkEquivalence(const vector<vector<int>>& equivalence, int region)
{
	bool found = false;
	int i = 0;
	for (i = 0; i < equivalence.size(); i++)
	{
		for (auto& j : equivalence[i])
		{
			if (region == j)
			{
				found = true;
				break;
			}
		}
		if (found == true)
			break;
	}

	return i + 1;
}

void MorphologyKernel::setKernelSize(ImageSize kernelSize, Coordinate origin, uint8_t binary, bool valid)
{
	this->kernelSize = kernelSize;
	this->origin = origin;
	int rows = kernelSize.rows;
	int columns = kernelSize.columns;
	this->valid = vector<vector<bool>>(rows, vector<bool>(columns, valid));
	this->binary = vector<vector<uint8_t>>(rows, vector<uint8_t>(columns, binary));
}

void MorphologyKernel::setKernel(Coordinate coord, uint8_t binary, bool valid)
{
	int r = coord.row, c = coord.column;
	this->binary[r][c] = binary;
	this->valid[r][c] = valid;
}

MorphologyKernel::MorphologyKernel()
{
	this->origin = Coordinate(0, 0);
	this->kernelSize = ImageSize(0, 0);
}

MorphologyKernel::MorphologyKernel(int rows, int columns)
{
	this->origin = Coordinate(rows / 2, columns / 2);
	this->kernelSize = ImageSize(rows, columns);
	this->valid = vector<vector<bool>>(rows, vector<bool>(columns, false));
	this->binary = vector<vector<uint8_t>>(rows, vector<uint8_t>(columns, 0));
}

MorphologyKernel MorphologyKernel::operator=(const MorphologyKernel& other)
{
	this->origin = other.origin;
	this->kernelSize = other.kernelSize;
	this->valid = other.valid;
	this->binary = other.binary;
	return *this;
}

void Morphology::setStarKernel(int n)
{
	this->kernel = MorphologyKernel(n, n);
	for (int r = 0; r < n; r++)
		this->kernel.setKernel(Coordinate(r, n / 2), 255, true);
	for (int c = 0; c < n; c++)
		this->kernel.setKernel(Coordinate(n / 2, c), 255, true);
}

void Morphology::setStarKernel(int rows, int columns)
{
	this->kernel = MorphologyKernel(rows, columns);
	for (int r = 0; r < rows; r++)
		this->kernel.setKernel(Coordinate(r, columns / 2), 255, true);
	for (int c = 0; c < columns; c++)
		this->kernel.setKernel(Coordinate(rows / 2, c), 255, true);
}

void Morphology::setBoxKernel(int n)
{
	this->kernel = MorphologyKernel(n, n);
	for (int r = 0; r < n; r++)
		for (int c = 0; c < n; c++)
			this->kernel.setKernel(Coordinate(r, c), 255, true);
}

void Morphology::setBoxKernel(int rows, int columns)
{
	this->kernel = MorphologyKernel(rows, columns);
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			this->kernel.setKernel(Coordinate(r, c), 255, true);
}

void Morphology::dilation()
{
	if (this->color != ColorSpace::Binary)
	{
		cout << "Morphology::dilation(): this->color != ColorSpace::Binary" << endl;
		return;
	}

	int rows = this->size.rows;
	int columns = this->size.columns;
	int rowsKernel = this->kernel.kernelSize.rows;
	int columnsKernel = this->kernel.kernelSize.columns;
	int rowOrigin = this->kernel.origin.row;
	int columnOrigin = this->kernel.origin.column;
	vector<vector<uint8_t>> img_temp(rows, vector<uint8_t>(columns, 0));
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			for (int i = -rowOrigin; i < rowsKernel - rowOrigin; i++)
				for (int j = -columnOrigin; j < columnsKernel - columnOrigin; j++)
					if (this->img_0[r][c] == 255 && 0 <= r + i && r + i < rows && 0 <= c + j && c + j < columns)
						if (this->kernel.valid[i + rowOrigin][j + columnOrigin] == true)
							img_temp[r + i][c + j] = this->kernel.binary[i + rowOrigin][j + columnOrigin];

	this->img_0 = img_temp;
}

void Morphology::erosion()
{
	if (this->color != ColorSpace::Binary)
	{
		cout << "Morphology::erosion(): this->color != ColorSpace::Binary" << endl;
		return;
	}

	int rows = this->size.rows;
	int columns = this->size.columns;
	int rowsKernel = this->kernel.kernelSize.rows;
	int columnsKernel = this->kernel.kernelSize.columns;
	int rowOrigin = this->kernel.origin.row;
	int columnOrigin = this->kernel.origin.column;
	vector<vector<uint8_t>> img_temp(rows, vector<uint8_t>(columns, 0));
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
		{
			bool flag = true;
			for (int i = -rowOrigin; flag && i < rowsKernel - rowOrigin; i++)
				for (int j = -columnOrigin; flag && j < columnsKernel - columnOrigin; j++)
					if (this->kernel.valid[i + rowOrigin][j + columnOrigin] == true)
					{
						flag &= (0 <= r + i && r + i < rows && 0 <= c + j && c + j < columns);
						if (flag)
							flag &= (this->img_0[r + i][c + j] == this->kernel.binary[i + rowOrigin][j + columnOrigin]);
						else
							flag = false;
					}
			if (flag)
				img_temp[r][c] = 255;
		}

	this->img_0 = img_temp;
}

Morphology::Morphology()
{

}
