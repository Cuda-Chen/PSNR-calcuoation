//
//    Program: Bitmap functions
// Written by: Frank Lee
//       Date: May 2000
// Modified by Pierre Chen, Nov. 2010     
//
// This program contains functions to read and write graphic bitmap data.
// The functions are capable of only handling uncompressed 24 bit images.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "array.h"
#include "bmp.h"

using namespace std;

bool Read_BMP_SIZE(const char *filename,int &nr,int &nc)
{
    bool ok = true;         // assume file is handlable
    int row, col, padding;
    char temp;
    bmp_h header;
    ifstream file;
    
    unsigned char R, G, B;
    
    file.open(filename, ios::binary);
    
    if(file.is_open())
    {
      ok = file.seekg(0x0002);
      ok = file.read ((char *)&header, sizeof(header));
    }
	
    // bitmap must be 24 bit, uncompressed
    if (!ok)
    {
        cout << "File Problems.\n";
    }
    else
    if ((header.bits != 32 && header.bits != 24 &&header.bits != 8) ||header.comp != 0)
    {
      ok = false;
      cout << "File Limitation: Bitmap file must be 24 bit with no compression.\n";
    } 
    
    if (ok)
	{
        nr = header.height;
        nc = header.width;
    }
    return (ok);
}

bool Read_BMP_To_2D(const char *filename,unsigned char** &ima,int &nr,int &nc)
{
    bool ok = true;         // assume file is handlable
    int row, col, padding;
#if 0//by kuolun
    char temp;
#else
	unsigned char temp;
#endif
    bmp_h header;
    ifstream file;
    
    unsigned char R, G, B;
    
    file.open(filename, ios::binary);
    
    if(file.is_open())
    {
      ok = file.seekg(0x0002);
      ok = file.read ((char *)&header, sizeof(header));
    }
	
    // bitmap must be 24 bit, uncompressed
    if (!ok)
    {
        cout << "File Problems.\n";
    }   
    else
    if ((header.bits != 32 && header.bits != 24 &&header.bits != 8) ||header.comp != 0)
    {
      ok = false;
      cout << "File Limitation: Bitmap file must be 24 bit with no compression.\n";
    } 
    
    if (ok)
	{
        nr = header.height;
        nc = header.width;
        ima = uc2D_Initialize(header.height, header.width);
        // move offset to rgb_raw_data_offset to get RGB raw data
        
        
        // row data is saved to nearest multiple of four
		// determine empty bytes for row data
		padding = (header.width*3)%4;
		if (padding != 0)
		{
			padding = 4 - padding;
		}
		
		
        file.seekg(header.bdo);
        if(header.bits == 32)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
#if 0//by kuolun
                file.read ((char *)&temp, sizeof(temp));
                B = temp;
                file.read ((char *)&temp, sizeof(temp));
                G = temp;
                file.read ((char *)&temp, sizeof(temp));
                R = temp;
                file.read ((char *)&temp, sizeof(temp));
#else
				file.read ((char *)&temp, sizeof(temp));
				B = temp;
				file.read ((char *)&temp, sizeof(temp));
				G = temp;
				file.read ((char *)&temp, sizeof(temp));
				R = temp;
				file.read ((char *)&temp, sizeof(temp));

#endif
                ima[row][col] =0.3*R+0.59*G+0.11*B;
            }
            for (col=0; col<padding; col++)
			{
#if 0
				file.read ((char *)&temp, sizeof(temp));
#else
				file.read ((char *)&temp, sizeof(temp));
#endif
			}
          }
        }
        if(header.bits == 24)
        {

          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
#if 0//by kuolun
                file.read ((char *)&temp, sizeof(temp));
                B = temp;
                file.read ((char *)&temp, sizeof(temp));
                G = temp;
                file.read ((char *)&temp, sizeof(temp));
#else
				file.read ((char *)&temp, sizeof(temp));
				B = temp;
				file.read ((char *)&temp, sizeof(temp));
				G = temp;
				file.read ((char *)&temp, sizeof(temp));
#endif
                R = temp;
                ima[row][col] =0.3*R+0.59*G+0.11*B;
            }
            for (col=0; col<padding; col++)
			{
#if 0
				file.read ((char *)&temp, sizeof(temp));
#else
				file.read ((char *)&temp, sizeof(temp));
#endif
			}
          }
        }
        if(header.bits == 8)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
#if 0//by kuolun
                file.read ((char *)&temp, sizeof(temp));
#else
				file.read ((char *)&temp, sizeof(temp));
#endif
                ima[row][col] = temp;
            }
            for (col=0; col<padding; col++)
			{
#if 0//by kuolun
				file.read ((char *)&temp, sizeof(temp));
#else
				file.read ((char*)&temp, sizeof(temp));
#endif
			}
          }
        }
    }
    return (ok);
}

unsigned char* Read_BMP_To_1D(const char *fname_s, int *Height, int *Width, int *Depth)
{
  FILE          *fp_s = NULL;    // source file handler
  unsigned int  x,y;             // for loop counter
  unsigned int  width, height;   // image width, image height
  unsigned char R, G, B, Y;      // color of R, G, B
  unsigned char *image_t = NULL; // source image array
  unsigned char *image_s = NULL; // source image array
  unsigned int y_avg;            // average of y axle
  unsigned int y_t;              // target of y axle
   /*
   unsigned char header[54] = {
     0x42,        // identity : B
     0x4d,        // identity : M
     0, 0, 0, 0,  // file size
     0, 0,        // reserved1
     0, 0,        // reserved2
     54, 0, 0, 0, // RGB data offset
     40, 0, 0, 0, // struct BITMAPINFOHEADER size
     0, 0, 0, 0,  // bmp width
     0, 0, 0, 0,  // bmp height
     1, 0,        // planes
     24, 0,       // bit per pixel
     0, 0, 0, 0,  // compression
     0, 0, 0, 0,  // data size
     0, 0, 0, 0,  // h resolution
     0, 0, 0, 0,  // v resolution
     0, 0, 0, 0,  // used colors
     0, 0, 0, 0   // important colors
   };  */
   
   unsigned char Palette[256*4];
   int nbpal;
   int padding;

   unsigned int file_size;           // file size
   unsigned int rgb_raw_data_offset; // RGB raw data offset
   unsigned short bit_per_pixel;     // bit per pixel
   unsigned short byte_per_pixel;    // byte per pixel

   fp_s = fopen(fname_s, "rb");
   if (fp_s == NULL) {
     printf("fopen fp_s error\n");
     return NULL;
   }

   // move offset to 10 to find rgb raw data offset
   fseek(fp_s, 10, SEEK_SET);
   fread(&rgb_raw_data_offset, sizeof(unsigned int), 1, fp_s);
   // move offset to 18    to get width & height;
   fseek(fp_s, 18, SEEK_SET);
   fread(&width,  sizeof(unsigned int), 1, fp_s);
   fread(&height, sizeof(unsigned int), 1, fp_s);
   // get  bit per pixel  //addr=0x1c
   fseek(fp_s, 28, SEEK_SET);
   fread(&bit_per_pixel, sizeof(unsigned short), 1, fp_s);
   byte_per_pixel = bit_per_pixel / 8;
   // move offset to rgb_raw_data_offset to get RGB raw data
   //fseek(fp_s, rgb_raw_data_offset, SEEK_SET);
   fseek(fp_s, rgb_raw_data_offset, SEEK_SET);

   //check width%4==0, if not width space need offset
   padding = (width * byte_per_pixel) % 4;
   if(padding!=0){
   		padding = 4-padding;
   }
   
   image_s = (unsigned char *)malloc((size_t)(width * byte_per_pixel + padding)* height);
   if (image_s == NULL) {
     printf("malloc image_s error\n");
     return NULL;
   }
   image_t = (unsigned char *)malloc((size_t)width * height);
   if (image_t == NULL) {
     printf("malloc image_t error\n");
     return NULL;
   }  

   fread(image_s, sizeof(unsigned char), (size_t)(long)( (width * byte_per_pixel + padding)* height) , fp_s);

   //vertical inverse algorithm
   y_avg = 0 + (height-1);
   if(byte_per_pixel>1)
   {
     for(y = 0; y != height; ++y)
     {
       y_t = y_avg - y;
       for(x = 0; x != width; ++x)
       {
         R = *(image_s + byte_per_pixel * (width *  y + x) + (padding * y) + 2);
         G = *(image_s + byte_per_pixel * (width *  y + x) + (padding * y) + 1);
         B = *(image_s + byte_per_pixel * (width *  y + x) + (padding * y) + 0);
         Y = 0.3*R+0.59*G+0.11*B;
         *(image_t + (width * y_t + x))=Y;
       }
     }
   }
   else if(byte_per_pixel==1)
   {
     for(y = 0; y != height; ++y)
     {
       y_t = y_avg - y;
       for(x = 0; x != width; ++x)
       {
         Y=*(image_s + ( (width+padding) *  y + x));
         *(image_t + (width * y_t + x))=Y;
       }
     }
   }
   else
   {
     printf("image format error\n");
     return NULL;
   }

   *Height=height;
   *Width=width;
   *Depth=(int)bit_per_pixel;
   fclose(fp_s);
   free(image_s);
   return image_t;
}


bool Read_BMP_To_2D(const char *filename,unsigned char** &R,unsigned char** &G,unsigned char** &B,unsigned char** &Y,int &nr,int &nc)
{
#if 0
    bool ok = true;         // assume file is handlable
    int row, col, padding;
    char temp;
    bmp_h header;   
    ifstream file;

    file.open(filename, ios::binary);
    
    if(file.is_open())
    {
      ok = file.seekg(0x0002);
      ok = file.read ((char *)&header, sizeof(header));
    }

    // bitmap must be uncompressed
    if (!ok)
    {
        cout << "File Problems.\n";
    }
    else
    if ((header.bits != 32 && header.bits != 24 &&header.bits != 8) ||header.comp != 0)
    {
      ok = false;
      cout << "File Limitation: Bitmap file must be 24 bit with no compression.\n";
    }

    
    if (ok)
    {
        nr=header.height;
        nc=header.width;
        R = uc2D_Initialize(header.height, header.width);
        G = uc2D_Initialize(header.height, header.width);
        B = uc2D_Initialize(header.height, header.width);
        Y = uc2D_Initialize(header.height, header.width);
         // move offset to rgb_raw_data_offset to get RGB raw data
        file.seekg(header.bdo);
        
        // row data is saved to nearest multible of four
		// determine empty bytes for row data
		padding = (header.width*3)%4;
		if (padding != 0)
		{
			padding = 4 - padding;
		}
        
        if(header.bits == 32)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
                file.read ((char *)&temp, sizeof(temp));
                B[row][col] = temp;
                file.read ((char *)&temp, sizeof(temp));
                G[row][col] = temp;
                file.read ((char *)&temp, sizeof(temp));
                R[row][col] = temp;
                file.read ((char *)&temp, sizeof(temp));
                Y[row][col] =0.3*R[row][col]+0.59*G[row][col]+0.11*B[row][col];
            }
            for (col=0; col<padding; col++)
			{
				file.read ((char *)&temp, sizeof(temp));
			}
          }
        }
        if(header.bits == 24)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
                file.read ((char *)&temp, sizeof(temp));
                B[row][col] = temp;
                file.read ((char *)&temp, sizeof(temp));
                G[row][col] = temp;
                file.read ((char *)&temp, sizeof(temp));
                R[row][col] = temp;
                Y[row][col] =0.3*R[row][col]+0.59*G[row][col]+0.11*B[row][col];
            }
            for (col=0; col<padding; col++)
			{
				file.read ((char *)&temp, sizeof(temp));
			}
          }
        }
        if(header.bits == 8)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
                file.read ((char *)&temp, sizeof(temp));
                Y[row][col] = temp;
                R[row][col] = Y[row][col];
                G[row][col] = Y[row][col];
                B[row][col] = Y[row][col];
            }
            for (col=0; col<padding; col++)
			{
				file.read ((char *)&temp, sizeof(temp));
			}
          }         
        }       
    }
    return (ok);
#else //by kuolun
	bool ok = true;         // assume file is handlable
    int row, col, padding;
    unsigned char temp;
    bmp_h header;   
    ifstream file;

    file.open(filename, ios::binary);
    
    if(file.is_open())
    {
      ok = file.seekg(0x0002);
      ok = file.read ((char *)&header, sizeof(header));
    }

    // bitmap must be uncompressed
    if (!ok)
    {
        cout << "File Problems.\n";
    }   
    else
    if ((header.bits != 32 && header.bits != 24 &&header.bits != 8) ||header.comp != 0)
    {
      ok = false;
      cout << "File Limitation: Bitmap file must be 24 bit with no compression.\n";
    }

    
    if (ok)
    {
        nr=header.height;
        nc=header.width;
        R = uc2D_Initialize(header.height, header.width);
        G = uc2D_Initialize(header.height, header.width);
        B = uc2D_Initialize(header.height, header.width);
        Y = uc2D_Initialize(header.height, header.width);
         // move offset to rgb_raw_data_offset to get RGB raw data
        file.seekg(header.bdo);
        
        // row data is saved to nearest multible of four
		// determine empty bytes for row data
		padding = (header.width*3)%4;
		if (padding != 0)
		{
			padding = 4 - padding;
		}
        
        if(header.bits == 32)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
                file.read ((char  *)&temp, sizeof(temp));
                B[row][col] = temp;
                file.read ((char  *)&temp, sizeof(temp));
                G[row][col] = temp;
                file.read ((char  *)&temp, sizeof(temp));
                R[row][col] = temp;
                file.read ((char  *)&temp, sizeof(temp));
                Y[row][col] =0.3*R[row][col]+0.59*G[row][col]+0.11*B[row][col];
            }
            for (col=0; col<padding; col++)
			{
				file.read ((char  *)&temp, sizeof(temp));
			}
          }
        }
        if(header.bits == 24)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
                file.read ((char  *)&temp, sizeof(temp));
                B[row][col] = temp;
                file.read ((char  *)&temp, sizeof(temp));
                G[row][col] = temp;
                file.read ((char  *)&temp, sizeof(temp));
                R[row][col] = temp;
                Y[row][col] =0.3*R[row][col]+0.59*G[row][col]+0.11*B[row][col];
            }
            for (col=0; col<padding; col++)
			{
				file.read ((char  *)&temp, sizeof(temp));
			}
          }
        }
        if(header.bits == 8)
        {
          // data stored bottom up, left to right
          for (row=header.height-1; row>=0; row--)
          {
            for (col=0; col<header.width; col++)
            {
                file.read ((char  *)&temp, sizeof(temp));
                Y[row][col] = temp;
                R[row][col] = Y[row][col];
                G[row][col] = Y[row][col];
                B[row][col] = Y[row][col];
            }
            for (col=0; col<padding; col++)
			{
				file.read ((char  *)&temp, sizeof(temp));
			}
          }         
        }       
    }
    return (ok);
#endif
}
// file should be open in binary mode
//
//bool __fastcall TForm1::Write_BMP(ofstream &file, bmp_h header, unsigned char** r, unsigned char** g, unsigned char** b)
bool  Write_BMP_8bits(const char *filename,unsigned char** ima,int nr,int nc)
{
#if 0//by kuolun
    bool ok = true;         // for checking file output problems
    char i = 'B', d = 'M';
    int row, col, padding;
    char temp;
    bmp_h header;
    int byte_per_pixel=1;
    unsigned char Palette[256*4];
    int nbpal;
    ofstream file;

    file.open(filename, ios::binary);

    ok=file.is_open();
    if( !ok )
    {
        cout << "File Problems.\n";
        return ok;
    }
          
    //raw data offset
    header.bdo=1078;  
    header.bhs=40;
    header.height=nr;
    header.width=nc;
    header.planes=1;
    header.bits=8;
    header.comp=0;
    header.bds=0;
    header.hr=0;
    header.vr=0;
    header.colors=0;
    header.imp_colors=0;

    // file size
    header.fs = nr * nc * byte_per_pixel + header.bdo;
    header.res=0;
    // BM id header
    ok = file.write ((char *)&i, sizeof(i));
    ok = file.write ((char *)&d, sizeof(d));

    // rest of header
    ok = file.write ((char *)&header, sizeof(header));
    
    //Palette
    for(nbpal=0;nbpal<256;nbpal++)
    {
      Palette[4*nbpal+0]=nbpal;
      Palette[4*nbpal+1]=nbpal;
      Palette[4*nbpal+2]=nbpal;
      Palette[4*nbpal+3]=0;
    }
    //fwrite(Palette, sizeof(unsigned char), 256*4, fp_t);
    ok = file.write ((char *)&Palette, sizeof(Palette));
    
    // write image
    if (ok)
    {
    	// row data is saved to nearest multible of four
		// determine empty bytes for row data
		padding = (header.width)%4;
		if (padding != 0)
		{
			padding = 4 - padding;
		}
    	
        // data stored bottom up, left to right
        for (row=header.height-1; row>=0; row--)
        {
            for (col=0; col<header.width; col++)
            {
                temp = ima[row][col];
                file.write ((char *)&temp, sizeof(temp));
            }
            for (col=0; col<padding; col++)
			{
				file.write ((char *)&temp, sizeof(temp));
			}
        }
    }
    return (ok);
#else
	bool ok = true;         // for checking file output problems
	char i = 'B', d = 'M';
	int row, col, padding;
	unsigned char temp;
	bmp_h header;
	int byte_per_pixel=1;
	unsigned char Palette[256*4];
	int nbpal;
	ofstream file;

	file.open(filename, ios::binary);

	ok=file.is_open();
	if( !ok )
	{
		cout << "File Problems.\n";
		return ok;
	}

	//raw data offset
	header.bdo=1078;  
	header.bhs=40;
	header.height=nr;
	header.width=nc;
	header.planes=1;
	header.bits=8;
	header.comp=0;
	header.bds=0;
	header.hr=0;
	header.vr=0;
	header.colors=0;
	header.imp_colors=0;

	// file size
	header.fs = nr * nc * byte_per_pixel + header.bdo;
	header.res=0;
	// BM id header
	ok = file.write ((char *)&i, sizeof(i));
	ok = file.write ((char  *)&d, sizeof(d));

	// rest of header
	ok = file.write ((char *)&header, sizeof(header));

	//Palette
	for(nbpal=0;nbpal<256;nbpal++)
	{
		Palette[4*nbpal+0]=nbpal;
		Palette[4*nbpal+1]=nbpal;
		Palette[4*nbpal+2]=nbpal;
		Palette[4*nbpal+3]=0;
	}
	//fwrite(Palette, sizeof(unsigned char), 256*4, fp_t);
	ok = file.write ((char  *)&Palette, sizeof(Palette));

	// write image
	if (ok)
	{
		// row data is saved to nearest multible of four
		// determine empty bytes for row data
		padding = (header.width)%4;
		if (padding != 0)
		{
			padding = 4 - padding;
		}

		// data stored bottom up, left to right
		for (row=header.height-1; row>=0; row--)
		{
			for (col=0; col<header.width; col++)
			{
				temp = ima[row][col];
				file.write ((char *)&temp, sizeof(temp));
			}
			for (col=0; col<padding; col++)
			{
				file.write ((char *)&temp, sizeof(temp));
			}
		}
	}
	return (ok);
#endif
}
//---------------------------------------------------------------------------
bool Write_BMP_8bits_1D(const char *filename,unsigned char* img,int nr,int nc)
{
	
	bool ok = true;         // for checking file output problems
	char i = 'B', d = 'M';
	int row, col, padding;
	unsigned char padding_pixel = 0;
	unsigned char *temp;
	bmp_h header;
	int byte_per_pixel=1;
	unsigned char Palette[256*4];
	int nbpal;
	ofstream file;

	file.open(filename, ios::binary);

	ok=file.is_open();
	if( !ok )
	{
		cout << "File Problems.\n";
		return ok;
	}

	//raw data offset
	header.bdo=1078;  
	header.bhs=40;
	header.height=nr;
	header.width=nc;
	header.planes=1;
	header.bits=8;
	header.comp=0;
	header.bds=0;
	header.hr=0;
	header.vr=0;
	header.colors=0;
	header.imp_colors=0;

	// file size
	header.fs = nr * nc * byte_per_pixel + header.bdo;
	header.res=0;
	// BM id header
	ok = file.write ((char *)&i, sizeof(i));
	ok = file.write ((char  *)&d, sizeof(d));

	// rest of header
	ok = file.write ((char *)&header, sizeof(header));

	//Palette
	for(nbpal=0;nbpal<256;nbpal++)
	{
		Palette[4*nbpal+0]=nbpal;
		Palette[4*nbpal+1]=nbpal;
		Palette[4*nbpal+2]=nbpal;
		Palette[4*nbpal+3]=0;
	}
	//fwrite(Palette, sizeof(unsigned char), 256*4, fp_t);
	ok = file.write ((char  *)&Palette, sizeof(Palette));

	// write image
	if (ok)
	{
		// row data is saved to nearest multible of four
		// determine empty bytes for row data
		padding = (header.width)%4;
		if (padding != 0)
		{
			padding = 4 - padding;
		}

		// data stored bottom up, left to right
		for (row=header.height-1; row>=0; row--)
		{
			temp = &img[row * header.width];
			file.write ((char *)temp, sizeof(char) * header.width);
			for (col=0; col<padding; col++)
			{
				file.write ((char *)&padding_pixel, sizeof(padding_pixel));
			}
		}
	}
	return (ok);
}

//---------------------------------------------------------------------------
bool  Write_BMP_24bits(const char *filename,unsigned char** R,unsigned char** G,unsigned char** B,int nr,int nc)
{
    bool ok = true;         // for checking file output problems
    char i = 'B', d = 'M';
    int row, col, padding;
    char temp;
    bmp_h header;
    int byte_per_pixel=1;
    unsigned char Palette[256*4];
    int nbpal;
    ofstream file;

    file.open(filename, ios::binary);

    ok=file.is_open();
    if( !ok )
    {
        cout << "File Problems.\n";
        return ok;
    }
          
    //raw data offset
    header.bdo=54;
    header.bhs=40;
    header.height=nr;
    header.width=nc;
    header.planes=1;
    header.bits=24;
    header.comp=0;
    header.bds=0;
    header.hr=0;
    header.vr=0;
    header.colors=0;
    header.imp_colors=0;

    // file size
    header.fs = nr * nc * byte_per_pixel + header.bdo;
    header.res=0;
    // BM id header
    ok = file.write ((char *)&i, sizeof(i));
    ok = file.write ((char *)&d, sizeof(d));

    // rest of header
    ok = file.write ((char *)&header, sizeof(header));

    // write image
    if (ok)
    {
    	// row data is saved to nearest multible of four
		// determine empty bytes for row data
		padding = (header.width*3)%4;
		if (padding != 0)
		{
			padding = 4 - padding;
		}
    	
        // data stored bottom up, left to right
        for (row=header.height-1; row>=0; row--)
        {
            for (col=0; col<header.width; col++)
            {
                temp = B[row][col];
                file.write ((char *)&temp, sizeof(temp));
                temp = G[row][col];
                file.write ((char *)&temp, sizeof(temp));
                temp = R[row][col];
                file.write ((char *)&temp, sizeof(temp)); 
            }
            for (col=0; col<padding; col++)
			{
				file.write ((char *)&temp, sizeof(temp));
			}
        }
    }
    return (ok);

}

//---------------------------------------------------------------------------
bool  Write_BMP_24bits_3(const char *filename,unsigned char** R,unsigned char** G,unsigned char** B, int point_x, int point_y,int nr,int nc)
{
	bool ok = true;         // for checking file output problems
	char i = 'B', d = 'M';
	int row, col, padding;
	char temp;
	bmp_h header;
	int byte_per_pixel=1;
	unsigned char Palette[256*4];
	int nbpal;
	ofstream file;

	file.open(filename, ios::binary);

	ok=file.is_open();
	if( !ok )
	{
		cout << "File Problems.\n";
		return ok;
	}

	//raw data offset
	header.bdo=54;
	header.bhs=40;
	header.height=nr;
	header.width=nc;
	header.planes=1;
	header.bits=24;
	header.comp=0;
	header.bds=0;
	header.hr=0;
	header.vr=0;
	header.colors=0;
	header.imp_colors=0;

	// file size
	header.fs = nr * nc * byte_per_pixel + header.bdo;
	header.res=0;
	// BM id header
	ok = file.write ((char *)&i, sizeof(i));
	ok = file.write ((char *)&d, sizeof(d));

	// rest of header
	ok = file.write ((char *)&header, sizeof(header));

	// write image
	if (ok)
	{
		// row data is saved to nearest multible of four
		// determine empty bytes for row data
		padding = (header.width*3)%4;
		if (padding != 0)
		{
			padding = 4 - padding;
		}

		// data stored bottom up, left to right
		for (row=header.height-1; row>=0; row--)
		{
			for (col=0; col<header.width; col++)
			{
				if (row == point_y || col == point_x){
					temp = B[row][col];
					temp = 0;
					file.write ((char *)&temp, sizeof(temp));
					temp = G[row][col];
					temp = 0;
					file.write ((char *)&temp, sizeof(temp));
					temp = R[row][col];
					temp = 255;
					file.write ((char *)&temp, sizeof(temp));
				}
				else{
					temp = B[row][col];
					file.write ((char *)&temp, sizeof(temp));
					temp = G[row][col];
					file.write ((char *)&temp, sizeof(temp));
					temp = R[row][col];
					file.write ((char *)&temp, sizeof(temp));
				}
			}
			for (col=0; col<padding; col++)
			{
				temp = 0;
				file.write ((char *)&temp, sizeof(temp));
			}
		}
	}
	return (ok);

}

//---------------------------------------------------------------------------



//
// Function: Print_BMP_Header
// Display Bitmap header info to console
//
void Print_BMP_Header (bmp_h h)
{
	cout << endl;  
	//cout << "Char 1             = " << h.c1 << endl;
	//cout << "Char 2             = " << h.c2 << endl;
	cout << "File Size          = " << h.fs << endl;
	cout << "Width              = " << h.width << endl;
	cout << "Height             = " << h.height << endl;
	cout << "Bits per Pixel     = " << h.bits << endl;
	cout << "Compression        = " << h.comp << endl;
}

