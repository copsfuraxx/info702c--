#include <iostream>
#include <fstream>
#include "GrayLevelImage2D.hpp"
#include <algorithm>

using namespace std;

int main( int argc, char** argv )
{
  if ( argc < 3 ) 
  { 
    std::cerr << "Usage: filtrage-median <input.pgm> <output.pgm>" << std::endl;
    return 0;
  }
  GrayLevelImage2D img;
  ifstream input( argv[1] ); // récupère le 1er argument.
  bool ok = img.importPGM( input );
  if ( !ok )
  {
    std::cerr << "Error reading input file." << std::endl;
    return 1;
  }
  input.close();
  GrayLevelImage2D imgbis;
  input = ifstream(argv[1]);
  ok = imgbis.importPGM( input );
  if ( !ok )
  {
    std::cerr << "Error reading input file." << std::endl;
      return 1;
  }
  input.close();
  for (int j = 1; j < img.h()-1; j++)
  {
    for (int i = 1; i < img.w()-1; i++)
    {
      if (img.at(i, j) < 1 || img.at(i, j) > 254)
      {
        unsigned char x[] = {imgbis.at(i-1,j), imgbis.at(i+1,j), imgbis.at(i,j-1), imgbis.at(i,j+1), imgbis.at(i-1,j-1), imgbis.at(i+1,j-1), imgbis.at(i-1,j+1), imgbis.at(i+1,j+1)};
        std::sort( x, x+8 ); // x vaut { 0.4, 4.2, 5.7, 8.6, 13.2 };
        unsigned char med = x[ 3 ];
        img.at(i, j) = med;
      }

    }
  }
  ofstream output( argv[2] ); // récupère le 2ème argument.
  ok = img.exportPGM( output, false );
  if ( !ok )
    {
      std::cerr << "Error writing output file." << std::endl;
       return 1;
    }
  output.close();
  return 0;
}