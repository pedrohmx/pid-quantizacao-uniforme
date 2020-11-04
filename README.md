# pid-quantizacao-uniforme

Trabalho da disciplina de Processamento de Imagens Digitais

TEMA 09: Implementar a quantização uniforme de imagens, que converte imagens com resolução de cores em 24 bits para resolução de cores em 8 bits. A imagem de entrada deve ser fornecida pelo usuário e lida do disco. A imagem de saída deve ser salva em disco usando formato compatível com a resolução de cores, ou seja, deve ser salva em 8-bits/pixel.  Neste  caso,  para  salvar  o  arquivo,  não  é  permitido  uso  de  bibliotecas prontas. 

### Dependencias

* [CMake](https://cmake.org/) (>=3.0)
* [OpenCV](https://opencv.org/) (>=4.4)

### Instruções de Compilação

* Requer C++ 17

#### Linux

```bash
mkdir build
cd build
cmake ..
make
```

#### Windows

https://cmake.org/runningcmake/

### Instruções de uso

```
Uso: quantizacao-uniforme [opções] entrada saida 

Argumentos posicionais:
entrada         Caminho para imagem entrada.
saida           Caminho para imagem saida. (padrão: unnamed.bmp)

Argumentos opcionais:
-h --help       Exibe essa mensagem de ajuda e sai
```

```
Usage: quantizacao-uniforme [options] input output 

Positional arguments:
input           Path to input image.
output          Path to output image. (default: unnamed.bmp)

Optional arguments:
-h --help       show this help message and exit
```
