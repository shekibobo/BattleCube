// extract_bmp.c
// extracts color data from uncompressed 24-bit .bmp file
// gw


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1)
typedef struct {
	char id[2]; 
	int file_size;
	int reserved;
	int offset;
} header_type;

#pragma pack(1)
typedef struct {
	int header_size;
	int width;
	int height; 
	unsigned short int color_planes; 
	unsigned short int color_depth; 
	unsigned int compression; 
	int image_size;
	int xresolution;
	int yresolution; 
	int num_colors;
	int num_important_colors;
} information_type;


int main(int argc, char* argv[])
{
	header_type header;
	information_type information;
	unsigned char data[3], temp;
	int i, j, row_bytes, padding;
	FILE *fp_bmp, *fp_dat;
	char filename[256], datfile[256];

	printf ("enter image fileName: ");
	scanf ("%s", filename);

	if ((fp_bmp = fopen (filename, "rb")) == NULL) {
		printf ("file not found\n");
		abort();
	}
	strcpy (datfile, filename);
	datfile[strlen(filename) - 3] = 'd';
	datfile[strlen(filename) - 2] = 'a';
	datfile[strlen(filename) - 1] = 't';
	fp_dat = fopen (datfile, "wb");

	// read file header
	fread (&header, sizeof(header_type), 1, fp_bmp);
	if (header.id[0] != 'B' || header.id[1] != 'M') {
		fprintf (stderr, "Does not appear to be a .bmp file.  Goodbye.\n");
		abort();
	}

	// read/compute image information
	fread (&information, sizeof(information_type), 1, fp_bmp);	
	row_bytes = information.width * 3;
	padding = row_bytes % 4;
	if (padding)
		padding = 4 - padding;

	// extract RGB pixel intensities; swap red/blue; write to file
	for (i=0; i < information.height; i++) {
		for (j=0; j < information.width; j++) {
			fread (data, sizeof(unsigned char), 3, fp_bmp);
			temp = data[0];
			data[0] = data[2];
			data[2] = temp;
			fwrite (data, sizeof(unsigned char), 3, fp_dat);
		}
		if (padding)
			fread (data, sizeof(unsigned char), padding, fp_bmp);
	}
	printf ("%s: %d x %d\n", datfile, information.width, information.height);

	fclose (fp_bmp);
	fclose (fp_dat);
	return 0;
}

