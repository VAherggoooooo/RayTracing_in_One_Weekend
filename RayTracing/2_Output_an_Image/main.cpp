#include<iostream>
using namespace std;

int main() 
{
	//image data
	const int image_width = 256;
	const int image_height = 256;

	//P3? 255? 
	//see: https://raytracing.github.io/books/RayTracingInOneWeekend.html
	cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	//��������, �������°������
	//���½�(0,0)
	for (int j = image_height - 1; j >= 0; --j) 
	{
		cerr << "\rScanlines remaining: " << j << ' ' << flush;//������
		for (int i = 0; i < image_width; ++i) 
		{
			double r = double(i) / (image_width - 1);//��ǰ�����ڳߴ��е�ռ��[0,1]
			double g = double(j) / (image_height - 1);
			double b = 0.0;//ԭ����0.5
			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);
			cout << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
	cerr << "\nDone.\n";//���֪ͨ
}