#include <iostream>
#include <fstream>
#include <vector>
#include <array>

#include "pid_utils.hpp"

#define FILE_PATH "/home/xavier/Desktop/clone/pid-rgb2gray/img/lenna.bmp"

//#include "bmp.hpp"


// enum COMPRESSION_METHOD{
// 	BI_RGB,                         //Sem compressao
// 	BI_RLE8,                        //8 bit/pixel
// 	BI_RLE4,                        //4 bit/pixel
// 	BI_BITFIELDS,
// 	BI_JPEG,
// 	BI_PNG,
// 	BI_ALPHABITFIELDS,
// 	BI_CMYK,
// 	BI_CMYKRLE8,
// 	BI_CMYKRLE4
// };

// struct BMPColorTable
// {
// 	uint32_t red_mask{0x00ff0000};
// 	uint32_t green_mask{0x0000ff00};
// 	uint32_t blue_mask{0x000000ff};
// 	uint32_t alpha_mask{0xff000000};
// 	uint32_t color_space_type{0x73524742};
// 	uint32_t unused[16]{ 0 };  
// };

namespace pid
{

#pragma pack(push,1)

struct BMPFileHeader
{
	uint16_t filetype{0x4d42};      //Tipo de arquivo, sempre BM
	uint32_t filesize{0};           //Tamanho do arquivo (em bytes)
	uint16_t reserved1{0};          //Reservado (sempre 0)
	uint16_t reserved2{0};          //Reservado (sempre 0)
	uint32_t offsetdata{0};         //Posição de inicio dos dados de pixel
};

struct BMPInfoHeader
{
	uint32_t size{40};               //Tamanho desse cabeçalho (bytes)
	int32_t width{0};               //comprimento do bitmap em pixels
	int32_t height{0};              //altura do bitmap em pixels
	uint16_t planes{1};             //N. de planos para dispositivo alvo
	uint16_t bit_count{8};          //N. de bits por pixel
	uint32_t compression{0};
	uint32_t size_image{0};         //0 sem prompressao
	int32_t x_pixels_per_meter{3600};
	int32_t y_pixels_per_meter{3600};
	uint32_t colors_used{252};      //N. de indices de cores na tabela de cores. 0 para numero maximo permitido
	//(R,G,B)=>(6x7x6)=>252
	uint32_t important_colors{0};   //N. de cores usadas para exibirr o bitmap. 0 para todas as cores
};


#pragma pack(pop)

struct BMP8b
{
	BMPFileHeader file_header;
	BMPInfoHeader info_header;
	std::array<uint32_t,252UL> color_table;
	std::vector<uint8_t> data;

	BMP8b(int32_t width, int32_t height){
		if (width <= 0 || height <= 0){
			throw std::runtime_error("The image width and height must be positive numbers.");
		}

		this->info_header.width = width;
		this->info_header.height = height;
		
		this->info_header.size = sizeof(BMPInfoHeader);
		this->file_header.offsetdata = (
			sizeof(BMPFileHeader) +
			sizeof(BMPInfoHeader) +
			sizeof(uint32_t) * this->color_table.size()
		);
		
		this->info_header.bit_count = 8;
		this->info_header.compression = 0;

		this->data.resize(width * height);

		this->file_header.filesize = (
			this->file_header.offsetdata + 
			this->data.size()
		);

		this->build_color_table();
	}
	void write(const char *fname){
		std::fstream out;
		out.open(fname, std::ios::out | std::ios::binary);

		if(out.is_open()){
			out.write(reinterpret_cast<char*>(&file_header),14);
			out.write(reinterpret_cast<char*>(&info_header),40);
			
			for (size_t i = 0; i < color_table.size(); i++){
				out.write(reinterpret_cast<char*>(&color_table[i]),4);
			}

			for (size_t i = 0; i < data.size(); i++){
				out.write(reinterpret_cast<char*>(&data[i]),1);
			}
			
		}else{
			std::cout << "Erro: não foi possivel criar o arquivo de saida." << std::endl;
			return;
		}
	}
	void print(){
		std::cout << std::hex;
		//std::cout << std::dec;

		std::cout << "File Header" << std::endl;
		std::cout << "File type:" << this->file_header.filetype << std::endl;
		std::cout << std::dec << "File size: " << this->file_header.filesize << std::endl;
		std::cout << std::dec << "Offset: " << this->file_header.offsetdata << std::endl;
	}

	void build_color_table(){
		std::vector<uint32_t> red{//15 40 6b 96 c0 ea
			0x00150000,
			0x00400000,
			0x006b0000,
			0x00960000,
			0x00c00000,
			0x00ea0000
		};
		std::vector<uint32_t> green{//12 37 5c 80 ee c9 ed
			0x00001200,
			0x00003700,
			0x00005c00,
			0x00008000,
			0x0000ee00,
			0x0000c900,
			0x0000ed00
		};
		std::vector<uint32_t> blue{//15 40 6b 96 c0 ea
			0x00000015,
			0x00000040,
			0x0000006b,
			0x00000096,
			0x000000c0,
			0x000000ea
		};
		int index;
		//std::cout << std::hex;
		
		for (size_t r = 0; r < red.size(); r++){
			for (size_t g = 0; g < green.size(); g++){
				for (size_t b = 0; b < blue.size(); b++){
					index = r * green.size() * blue.size() + g * blue.size() + b;
					color_table[index] = red[r] | green[g] | blue[b];
					//std::cout << index << ":" << color_table[index] << std::endl;
				}
			}
		}
		//std::cout << std::dec;

	}
};

} // namespace pid


int main(int argc,char** argv){

	// pid::BMP8b map512(512,512);
	// for (size_t i = 0; i < map512.data.size(); i++){
	// 	map512.data[i] = 5;
	// }
	// map512.write("teste512.bmp");
	
	// pid::BMP8b map50(50,50);
	// for (size_t i = 0; i < map50.data.size(); i++){
	// 	map50.data[i] = 5;
	// }
	// map50.write("teste50.bmp");
	
	// pid::BMP8b map20(20,20);
	// for (size_t i = 0; i < map20.data.size(); i++){
	// 	map20.data[i] = 5;
	// }
	// map20.write("teste20.bmp");
	int w,h;
	std::cout << "Entre com o tamanho da imagem (width/comprimento/x) (height/altura/y):" << std::endl;
	std::cin >>	w >> h;
	pid::BMP8b mapc(w,h);
	for (size_t i = 0; i < mapc.data.size(); i++){
		mapc.data[i] = 5;//pintar imagem de azul
	}
	std::string strout = "teste_" + std::to_string(w) + "x" + std::to_string(h) + ".bmp";
	mapc.write(strout.c_str());
	
	
	//map.print();

	// std::fstream file("out.bin", std::ios::binary | std::ios::out);

	// int32_t num = 0x12345678;

	// file.write(reinterpret_cast<char*>(&num),4);

	// std::array<uint32_t,7> tarray = {18,55,92,128,238,201,237};
	// for (size_t i = 0; i < tarray.size(); i++){
	// 	std::cout << tarray[i] << " ";//pid::__red[i]
	// }
	// std::cout << std::endl;

	
	//std::fstream fout;
	//fout.open("black16x16.bmp",std::ios::binary | std::ios::out);

	// pid::BMP8b test(16,16);
	// test.data.resize(16*16);
	// for (size_t i = 0; i < test.data.size(); i++)
	// {
	// 	test.data.at(i) = 0;
	// }
	
	// std::cout << test.file_header.filesize << std::endl;
	//fout.write(reinterpret_cast<char*>(&test.file_header),sizeof(pid::BMPFileHeader));
	//fout.write(reinterpret_cast<char*>(&test.info_header),sizeof(pid::BMPInfoHeader));
	
	// std::cout << "hello." << std::endl;

	// std::fstream source;

	// source.open("deletethis",std::ios::binary | std::ios::out);

	// uint32_t var = 0x12345678;//00rrggbb

	// if(source.is_open()){
	// 	source.write(reinterpret_cast<char*>(&var),sizeof(uint32_t));
	// }else{
	// 	//
	// 	std::cout << "Error opening file." << std::endl;
	// 	exit(0);
	// }

	return 0;
}