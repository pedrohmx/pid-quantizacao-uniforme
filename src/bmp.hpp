#include <iostream>
#include <fstream>
#include <vector>
#include <array>

#pragma once

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
			static_cast<uint32_t>(height * width)
		);

		if(width % 4 != 0){
			this->file_header.filesize += (height * (4 - this->info_header.width % 4));
		}

		this->build_color_table();
	}
	bool write(const char *fname){
		std::fstream out;
		out.open(fname, std::ios::out | std::ios::binary);

		if(out.is_open()){
			out.write(reinterpret_cast<char*>(&file_header),14);
			out.write(reinterpret_cast<char*>(&info_header),40);
			
			for (size_t i = 0; i < color_table.size(); i++){
				out.write(reinterpret_cast<char*>(&color_table[i]),4);
			}

			// for (size_t i = 0; i < data.size(); i++){
			// 	out.write(reinterpret_cast<char*>(&data[i]),1);
			// }

			//tamanho do buffer
			int32_t buffer_size = (this->info_header.width % 4 == 0 ) ?
				this->info_header.width : 
				this->info_header.width + (4 - this->info_header.width % 4);
			
			//buffer de escrita
			char* buffer = new char[buffer_size];

			for (int32_t row = 0; row < this->info_header.height; row++){//escreve cada linha

				for (int32_t col = 0; col < this->info_header.width; col++){
					int index = row * this->info_header.width + col;
					buffer[col] = this->data[index];
				}
			
				out.write(buffer,buffer_size);
			}
			
			delete[] buffer;
			
		}else{
			std::cout << "Erro: não foi possivel criar o arquivo de saida." << std::endl;
			return false;
		}
		return true;
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
		
		//std::cout << std::hex;
		for (size_t r = 0; r < red.size(); r++){
			for (size_t g = 0; g < green.size(); g++){
				for (size_t b = 0; b < blue.size(); b++){
					int index = r * green.size() * blue.size() + g * blue.size() + b;
					color_table[index] = red[r] | green[g] | blue[b];
					//std::cout << index << ":" << color_table[index] << std::endl;
				}
			}
		}
		//std::cout << std::dec;
	}
};

} // namespace pid
