//
//    Program: Bitmap functions
// Written by: Frank Lee
//       Date: May 2000
// Modified by Pierre Chen, Nov. 2010     
//
// This program contains functions to read and write graphic bitmap data.
// The functions are capable of only handling uncompressed 24 bit images.
//

#ifndef _BMP_H_
#define _BMP_H_

// standard bitmap header information
struct bmp_h
{
	//char c1;
	//char c2;
	unsigned int fs;		// file size in bytes, dword (4 bytes)
	unsigned int res;		// reserved for later use
	unsigned int bdo;		// Bitmap Data Offset, beginning of data
	unsigned int bhs;		// Bitmap Header Size, size of bmp info
	unsigned int width;		// horizontal width in pixels
	unsigned int height;	// vertical height in pixels
	short int planes;		// number of planes in bitmap
	short int bits;			// bits per pixel
	unsigned int comp;		// compression mode
	unsigned int bds;		// Bitmap Data Size, size of data
	unsigned int hr;		// horizontal resolution, pixels per meter
	unsigned int vr;		// vertical resolution
	unsigned int colors;	// number of colors used
	unsigned int imp_colors;// important colors
};

bool Read_BMP_SIZE(const char *filename,int &nr,int &nc);
bool Read_BMP_To_2D(const char *filename,unsigned char** &ima,int &nr,int &nc);
unsigned char* Read_BMP_To_1D(const char *fname_s, int *Height, int *Width, int *Depth);
bool Read_BMP_To_2D(const char *filename,unsigned char** &R,unsigned char** &G,unsigned char** &B,unsigned char** &Y,int &nr,int &nc);
// file should be open in binary mode
//
//bool __fastcall TForm1::Write_BMP(ofstream &file, bmp_h header, unsigned char** r, unsigned char** g, unsigned char** b)
bool  Write_BMP_8bits(const char *filename,unsigned char** ima,int nr,int nc);
//---------------------------------------------------------------------------
bool Write_BMP_8bits_1D(const char *filename,unsigned char* img,int nr,int nc);
//---------------------------------------------------------------------------
bool  Write_BMP_24bits(const char *filename,unsigned char** R,unsigned char** G,unsigned char** B,int nr,int nc);
//---------------------------------------------------------------------------
bool  Write_BMP_24bits_3(const char *filename,unsigned char** R,unsigned char** G,unsigned char** B, int point_x, int point_y,int nr,int nc);
//---------------------------------------------------------------------------

//
// Function: Print_BMP_Header
// Display Bitmap header info to console
//
void Print_BMP_Header (bmp_h h);
#endif
