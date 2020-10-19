#include <iostream>
#include <list>
#include <fstream>

#include <opencv4/opencv2/opencv.hpp>

int main(int argc, char** argv )
{
    if ( argc != 2 )
	{
        std::cout << "usage: DisplayImage.out <Image_Path>" << std::endl;
        return -1;
    }
    
	cv::Mat image;
    image = cv::imread( argv[1], 1 );
    std::list<int8_t> lDate;
    //std::ofstream aTest;
    //aTest.open("texto.txt");
    
	if ( !image.data )
	{
        printf("No image data \n");
        return -1;
    }
    
	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    cv::imshow("Display Image", image);
    cv::waitKey(0);

    int i=0;
    int j=0;
    int matRows = image.rows;
    int matCols = image.cols;
    //for tipico (Funcionando)
    for(i=0;i<matRows;i++)
    {
        for(j=0;j<matCols;j++)
        {
            //std::cout << image.at<int8_t>(i,j);
            lDate.push_back(image.at<int8_t>(i,j));
        }
        /*std::cout<<std::endl<<"-------------"<<std::endl;
        std::list<int8_t>::iterator it=lDate.begin();
        for (; it!=lDate.end(); ++it)
            std::cout<<*it;
        getchar();*/
    }

    //Interator
    /*cv::MatIterator_<int8_t> _it = image.begin<int8_t>();
    for(;_it!=image.end<int8_t>(); _it++){
        //aTest<<*_it;
        lDate.push_back(*_it);
        std::cout<<std::endl<<"-------------"<<std::endl;
        std::list<int8_t>::iterator it=lDate.begin();
        for (; it!=lDate.end(); ++it)
            std::cout<<*it;
        getchar();
    }
    //aTest.close();
    */
    
	return 0;
}
