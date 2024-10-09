#include "converter.h"
#include <libraw/libraw.h>
#include <stb_image_write.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm> // 用于 std::clamp
#include <QImage>
#include <QColor>

#define USE_JPEG 1

#include "jpeglib.h"

void write_jpeg(libraw_processed_image_t *img, const char *basename, int quality)
{
    char fn[1024];
    if (img->colors != 1 && img->colors != 3)
    {
        printf("Only BW and 3-color images supported for JPEG output\n");
        return;
    }
    snprintf(fn, 1024, "%s.jpg", basename);
    FILE *f = fopen(fn, "wb");
    if (!f)
        return;
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1]; /* pointer to JSAMPLE row[s] */
    int row_stride;          /* physical row width in image buffer */

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, f);
    cinfo.image_width = img->width; /* image width and height, in pixels */
    cinfo.image_height = img->height;
    cinfo.input_components = img->colors;                              /* # of color components per pixel */
    cinfo.in_color_space = img->colors == 3 ? JCS_RGB : JCS_GRAYSCALE; /* colorspace of input image */
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);
    row_stride = img->width * img->colors; /* JSAMPLEs per row in image_buffer */
    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = &img->data[cinfo.next_scanline * row_stride];
        (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
    jpeg_finish_compress(&cinfo);
    fclose(f);
    jpeg_destroy_compress(&cinfo);
}

#if 0
bool convertNEFtoJPEG(const std::string &inputFile, const std::string &outputFile) {
    
    LibRaw rawProcessor;
    char outfn [1024],thumbfn [1024];

    if (rawProcessor.open_file(inputFile.c_str()) != LIBRAW_SUCCESS) {
        std::cerr << "Error opening NEF file." << std::endl;
        return false;
    }

    if (rawProcessor.unpack() != LIBRAW_SUCCESS) {
        std::cerr << "Error unpacking RAW data." << std::endl;
        rawProcessor.recycle();
        return false;
    }

    // if (rawProcessor.raw2image() != LIBRAW_SUCCESS) {
    //     std::cerr << "Error processing RAW data." << std::endl;
    //     rawProcessor.recycle();
    //     return false;
    // }

    // 数据解包
    int ret = rawProcessor.dcraw_process();
    if (LIBRAW_SUCCESS != ret) // 上一步的错误
    {
        // fprintf(stderr,"不能对 % s进行后处理 : % s \ n", av[i], libraw_strerror(ret));
        // if (LIBRAW_FATAL_ERROR(RET))
            return 0;
    }
    else // 成功的文档处理
    {
        // snprintf(outfn, sizeof(outfn)," % s。 % s", av[i],"tiff");
        if (LIBRAW_SUCCESS != (ret = rawProcessor.dcraw_ppm_tiff_writer(outputFile.c_str())))
            fprintf(stderr,"不能写 % s : 错误 % d \ n", outfn, ret);
    }
    // 我们不会唤起recycle()或调用析构函数; C ++将为我们做一切
    return 0;


    // 获取图像宽高
    int width = rawProcessor.imgdata.sizes.raw_width;
    int height = rawProcessor.imgdata.sizes.raw_height;

    // 分配图像数据内存
    unsigned char* image = new unsigned char[width * height * 3]; // RGB
#if 1
    
#else
    

#endif
#if 0
    // 写入JPEG文件
    if (!stbi_write_jpg(outputFile.c_str(), width, height, 3, image, 100)) {
        std::cerr << "Error writing JPEG file." << std::endl;
        delete[] image;
        rawProcessor.recycle();
        return false;
    }
#else
    
    
#endif
    // 清理
    delete[] image;
    rawProcessor.recycle();
    return true;
}

#else

bool convertNEFtoJPEG(const std::string &inputFile, const std::string &outputFile)
{
    // 检查文件是否存在
    if (std::filesystem::exists(inputFile))
    {
        std::cout << "File exists: " << inputFile << std::endl;
    }
    else
    {
        std::cerr << "File does not exist: " << inputFile << std::endl;
        return false;
    }
    LibRaw rawProcessor;
    rawProcessor.imgdata.params.output_bps = 8;

    // 打开 NEF 文件
    int ret = rawProcessor.open_file(inputFile.c_str());
    if (ret != LIBRAW_SUCCESS)
    {
        std::cerr << "无法打开文件 " << inputFile << ": " << libraw_strerror(ret) << std::endl;
        return false;
    }

    // 解压缩图像
    ret = rawProcessor.unpack();
    if (ret != LIBRAW_SUCCESS)
    {
        std::cerr << "无法解压缩 " << inputFile << ": " << libraw_strerror(ret) << std::endl;
        rawProcessor.recycle();
        return false;
    }
    // rawProcessor.params.output_tiff = 0; // 0 表示输出 JPEG
    // 处理图像
    ret = rawProcessor.dcraw_process();
    if (ret != LIBRAW_SUCCESS)
    {
        std::cerr << "处理失败 " << inputFile << ": " << libraw_strerror(ret) << std::endl;
        rawProcessor.recycle();
        return false;
    }
#if USE_JPEG
    int output_jpeg = 1, jpgqual = 100;
#endif
    libraw_processed_image_t *image = rawProcessor.dcraw_make_mem_image(&ret);
    if (image)
    {
        if (output_jpeg)
            write_jpeg(image, outputFile.c_str(), jpgqual);
    }

#if 0 
    // 写入 JPEG 文件
    ret = rawProcessor.dcraw_ppm_tiff_writer(outputFile.c_str());
    if (ret != LIBRAW_SUCCESS)
    {
        std::cerr << "无法写入文件 " << outputFile << ": " << libraw_strerror(ret) << std::endl;
        rawProcessor.recycle();
        return false;
    }
#else

    // 从imgdata.rawdata转换为imgdata.image：
    rawProcessor.raw2image();

    // 让我们打印它的转储; 数据可通过类的数据字段访问
    int width = rawProcessor.imgdata.sizes.iwidth;
    int height = rawProcessor.imgdata.sizes.iheight;

#endif
    rawProcessor.recycle(); // 清理
    return true;
}

#endif