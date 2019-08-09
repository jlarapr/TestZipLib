#include <iostream>
#include "zlib.h"

#include <stdio.h>
#include <string.h>

using namespace std;


unsigned long file_size(char *filename) {
    FILE *pFile = fopen(filename,"rb");
    fseek (pFile, 0, SEEK_END);
    unsigned long size = static_cast<unsigned long>(ftell(pFile));
    fclose (pFile);
    return size;
}
int decompress_one_file(char *infilename, char *outfilename) {
    gzFile infile = gzopen(infilename, "rb");
    FILE *outfile = fopen(outfilename, "wb");
    if (!infile || !outfile) return -1;

    char buffer[128];
    int num_read = 0;
    while ((num_read = gzread(infile, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, static_cast<unsigned long long>(num_read), outfile);
    }

    gzclose(infile);
    fclose(outfile);
    return  0;
}
int compress_one_file(char *infilename, char *outfilename)
{
   FILE *infile = fopen(infilename, "rb");
   gzFile outfile = gzopen(outfilename, "wb");

   if (!infile || !outfile) return -1;

   char inbuffer[128];
   int num_read = 0;
   unsigned long total_read = 0;
   //unsigned long total_wrote = 0;

   while ((num_read =  static_cast<int>(fread(inbuffer, 1, sizeof(inbuffer), infile))) > 0) {
      total_read +=  static_cast<unsigned long>(num_read);
      gzwrite(outfile, inbuffer, static_cast<unsigned int>(num_read));
   }
   fclose(infile);
   gzclose(outfile);

   printf("Read %ld bytes, Wrote %ld bytes,Compression factor %4.2f%%\n",
          total_read, file_size(outfilename),
          (1.0-file_size(outfilename)*1.0/total_read)*100.0);

   return  0;
}

int main(int argc, char **argv)
{

    //Byte *compr, *uncompr;
    //uLong comprLen = 10000*sizeof(int); /* don't overflow on MSDOS */
    //uLong uncomprLen = comprLen;
    //static const char* myVersion = ZLIB_VERSION;
    //
    //if (zlibVersion()[0] != myVersion[0]) {
    //    fprintf(stderr, "incompatible zlib version\n");
    //
    //    exit(1);
    //
    //} else if (strcmp(zlibVersion(), ZLIB_VERSION) != 0) {
    //    fprintf(stderr, "warning: different zlib version\n");
    //
    //} else {
    //    printf("zlib version %s = 0x%04x, compile flags = 0x%lx\n", ZLIB_VERSION, ZLIB_VERNUM, zlibCompileFlags());
    //}
    //
    //compr    = (Byte*)calloc((uInt)comprLen, 1);
    //uncompr  = (Byte*)calloc((uInt)uncomprLen, 1);
    ///* compr and uncompr are cleared to avoid reading uninitialized
    //     * data and to ensure that uncompr compresses well.
    //     */
    //if (compr == nullptr || uncompr == nullptr) {
    //    printf("out of memory\n");
    //    exit(1);
    //}
    //

    if (argc < 4) {
        cout << "TestZipLib <fileToZip.txt> <zipName.zip> <decompressName.txt>" << endl;
        exit(1);
    }

    compress_one_file(argv[1],argv[2]);
    decompress_one_file(argv[2],argv[3]);


    cout << "Hello World!" << endl;

    return 0;
}
