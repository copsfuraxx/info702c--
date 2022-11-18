#include "GrayLevelImage2D.hpp"
#include <cstring>

GrayLevelImage2D::Iterator::Iterator( GrayLevelImage2D& image, int x, int y ) : Container::iterator( image.m_data.begin() + image.index( x, y ) ){

}

GrayLevelImage2D::Iterator
GrayLevelImage2D::begin(){
    return GrayLevelImage2D::Iterator(*this, 0, 0);
}

GrayLevelImage2D::Iterator 
GrayLevelImage2D::end(){
    return GrayLevelImage2D::Iterator(*this, m_width, m_height-1);
}

GrayLevelImage2D::Iterator
GrayLevelImage2D::start( int x, int y ){
    return GrayLevelImage2D::Iterator(*this, x, y);
}

GrayLevelImage2D::GrayLevelImage2D(){
    m_width = 0;
    m_height = 0;
}

GrayLevelImage2D::GrayLevelImage2D( int w, int h, GrayLevel g) : m_width(w), m_height(h){
    m_data.resize(w * h, g);
}

int GrayLevelImage2D::w() const{
    return m_width;
}

int GrayLevelImage2D::h() const{
    return m_height;
}

int GrayLevelImage2D::index( int x, int y ) const{
    return m_width*(y)+x;
}

GrayLevelImage2D::GrayLevel GrayLevelImage2D::at(int i, int j) const{
    return m_data[index(i, j)];
}

GrayLevelImage2D::GrayLevel& GrayLevelImage2D::at(int i, int j){
    return m_data[index(i, j)];
}

char* iso_latin_1_to_utf8(char* buffer, char* end, unsigned char c) {
    if (c < 128) {
        if (buffer == end) { throw std::runtime_error("out of space"); }
        *buffer++ = c;
    }
    else {
        if (end - buffer < 2) { throw std::runtime_error("out of space"); }
        *buffer++ = 0xC0 | (c >> 6);
        *buffer++ = 0x80 | (c & 0x3f);
    }
    return buffer;
}

bool GrayLevelImage2D::importPGM( std::istream & input ){
    if (!input.good()) {
        std::cerr << "Probleme !";
        return false;
        }
    std::string txt;
    std::getline(input, txt);
    if (txt == "P5")
    {
        std::cout << txt << std::endl;
        std::getline(input, txt);
        std::cout << txt << std::endl;

        std::getline(input, txt);
        if (txt.at(0) == '#')
        {
            std::cout << txt << std::endl;
            input >> m_width >> m_height;
        }else
        {
            int i = txt.find(" ");
            m_width = std::stoi(txt.substr(0, i));
            m_height = std::stoi(txt.substr(i+1, txt.length()));
        }

        // read width and height
        //
        std::cout<<"la taille de l'image est " << m_width << " " << m_height << std::endl;
        // read max gray level
        int max_gray_level;
        input >> max_gray_level;

        std::cout<<"le max gray level de l'image est : "<<max_gray_level<<std::endl;

        if (max_gray_level != 255)
        {
            std::cerr << "Error: max gray level is not 255" << std::endl;
            return false;
        }
        // read data
        m_data.resize(m_width * m_height);

        input >> std::noskipws;
        for (Iterator it = begin(); it < end(); it++){
            input >> *it;
        }
    }else
    {
        return false;
    }
    std::cout << "Fin Import" << std::endl;
    return true;
}

bool GrayLevelImage2D::exportPGM( std::ostream & output, bool ascii_mode){
    output << (ascii_mode?"P2":"P5") << std::endl;
    output << "# Created by LeBoss" << std::endl;
    output << m_width << " " << m_height << std::endl;
    output << "255" << std::endl;
    // write data
    if (ascii_mode){
        int i = 0;
        for (Iterator ptr = begin(); ptr < end(); ptr++){
             output << *ptr << " ";
             if(i == m_width-1){
                output << std::endl;
                i = 0;
             }else i++;
        }
        /*for (int j = 0; j < m_height; ++j)
        {
            for (int i = 0; i < m_width; ++i)
            {
                output << (int)at(i, j) << " ";
            }
            output << std::endl;
        }*/
    }
    else
    {
        for (Iterator it = begin(); it < end(); it++){
            output << *it;
        }
        //output.write((char *)&m_data[0], m_width * m_height);
    }
    return true;
}
