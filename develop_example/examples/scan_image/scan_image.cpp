#include "example_common.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>

/*******************************************************
 *  This program shows how to scan image objects in OpenCV (cv::Mat).
 *  We can scan at multiple ways
 *  1. traditional C operator[] method
 *  2. iterators
 *  3. at function for on-the-fly item address calculation.
 ********************************************************/
static double time_flowing;  // using in the function of time calculation
static constexpr const int operation_duplication_time =
#ifdef DUP_TIME
    DUP_TIME;
#else
    100;  // the number of operation duplication
#endif
static constexpr const short devision =
#ifdef Div
#if Div <= 0
#error "Division requires a number >= 0."
    0;
#else
    Div;  // the number of devision
#endif
#else
    5;  // the number of devision
#endif

static void on_involk_with_timing(
    cv::Mat& src, const uchar* table,
    std::function<void(cv::Mat&, const uchar* table)> countings);

void scanningInCMethod(cv::Mat& I, const uchar* table);
void scanningInIterator(cv::Mat& I, const uchar* table);
void scanningInRandomAddress(cv::Mat& I, const uchar* table);

static inline std::string gain_path_image() {
    return EXAMPLE_COMMON_PATH "/scan_image/image.jpg";
}

static inline cv::Mat gain_image() {
    int requested_color = cv::IMREAD_COLOR;
#ifdef Gray
    requested_color = cv::IMREAD_GRAYSCALE;
#endif
    return cv::imread(gain_path_image(), requested_color);
}

int main() {
    /* on start */
    cv::Mat src = gain_image();
    if (src.empty()) {
        std::cerr << "The image could not be loaded." << std::endl;
        return -1;
    }

    /* make up division table */
    /* it make the image working as the stepped like */
    /*  0   ~ 1*div - 1   -> 0
     *  div ~ 2*div - 1   -> div
     *  2*div ~ 3*div - 1 -> 2 * div
     *  ...
     */
    uchar table[256];
    for (int i = 0; i < 256; ++i) table[i] = (uchar)(devision * (i / devision));

    // start testing time
    on_involk_with_timing(src, table, scanningInCMethod);
    on_involk_with_timing(src, table, scanningInIterator);
    on_involk_with_timing(src, table, scanningInRandomAddress);

    return 0;
}

void scanningInCMethod(cv::Mat& I, const uchar* table) {
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    int nRows = I.rows;
    int nCols = I.cols * I.channels();

    /* if mat is continuous, we can visit it as a 1dim array! */
    if (I.isContinuous()) {
        nCols *= nRows;
        nRows = 1;
    }

    for (int i = 0; i < nRows; ++i) {
        /* the the pointer of each row */
        /* specially, if it is continuous, treat as 1dim array actually */
        uchar* p = I.ptr<uchar>(i);
        for (int j = 0; j < nCols; ++j) {
            p[j] = table[p[j]];
        }
    }
}

void scanningInIterator(cv::Mat& I, const uchar* const table) {
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch (channels) {
        case 1: {
            cv::MatIterator_<uchar> it, end;
            for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
                *it = table[*it];
            break;
        }
        case 3: {
            cv::MatIterator_<cv::Vec3b> it, end;
            for (it = I.begin<cv::Vec3b>(), end = I.end<cv::Vec3b>(); it != end;
                 ++it) {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
            break;
        }
        default:
            std::cerr << "Unsupported test channels." << std::endl;
            break;
    }
}

void scanningInRandomAddress(cv::Mat& I, const uchar* const table) {
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch (channels) {
        case 1: {
            for (int i = 0; i < I.rows; ++i)
                for (int j = 0; j < I.cols; ++j)
                    I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
            break;
        }
        case 3: {
            cv::Mat_<cv::Vec3b> _I = I;

            for (int i = 0; i < I.rows; ++i)
                for (int j = 0; j < I.cols; ++j) {
                    _I(i, j)[0] = table[_I(i, j)[0]];
                    _I(i, j)[1] = table[_I(i, j)[1]];
                    _I(i, j)[2] = table[_I(i, j)[2]];
                }
            I = _I;
            break;
        }
        default:
            std::cerr << "Unsupported test channels." << std::endl;
            break;
    }
}

static void on_involk_with_timing(
    cv::Mat& src, const uchar* table,
    std::function<void(cv::Mat&, const uchar* table)> countings) {
    /* opencv provides the funtions for time countings */
    const double t = cv::getTickCount();
    for (int i = 0; i < operation_duplication_time; i++) {
        cv::Mat example_src = src.clone();
        countings(example_src, table);
    }

    /* calculate the average time spent */
    const double avg_time =
        (1000 * ((double)cv::getTickCount() - t) / cv::getTickFrequency()) /
        operation_duplication_time;

    std::cout << "Time of reducing with the function (averaged for "
              << operation_duplication_time << " runs): " << avg_time
              << " milliseconds." << std::endl;
}
