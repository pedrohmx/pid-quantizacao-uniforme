#include <iostream>
#include <fstream>
#include <vector>
#include <array>

#pragma once

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
	uint32_t size{0};               //Tamanho desse cabeçalho (bytes)
	int32_t width{0};               //comprimento do bitmap em pixels
	int32_t height{0};              //altura do bitmap em pixels
	uint16_t planes{1};             //N. de planos para dispositivo alvo
	uint16_t bit_count{8};          //N. de bits por pixel
	uint32_t compression{0};
	uint32_t size_image{0};         //0 sem prompressao
	int32_t x_pixels_per_meter{0};
	int32_t y_pixels_per_meter{0};
	uint32_t colors_used{255};      //N. de indices de cores na tabela de cores. 0 para numero maximo permitido
	//(R,G,B)=>(6x7x6)=>252
	uint32_t important_colors{255};   //N. de cores usadas para exibirr o bitmap. 0 para todas as cores
};


#pragma pack(pop)

struct BMP8b
{
	BMPFileHeader file_header;
	BMPInfoHeader info_header;
	std::array<uint32_t,256UL> color_table;
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
			this->file_header.offsetdata + this->data.size()
		);
	}
	void write(const char *fname){
		std::fstream out;
		out.open(fname, std::ios::out | std::ios::binary);

		if(out.is_open()){
			//
		}else{
			//
			return;
		}
	}
private:
	void build_black_color_table(){
		this->color_table.fill(0U);
	}
	void build_color_table(){
		std::vector<uint32_t> red{
			0x00150000,
		};
		std::vector<uint32_t> green;
		std::vector<uint32_t> blue;
	}
};

} // namespace pid
