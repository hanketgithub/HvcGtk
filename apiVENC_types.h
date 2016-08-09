/*
 *
 * Copyright (C) 2015 Advantech Co., Ltd. - http://www.advantech.com.tw/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Advantech Co., Ltd. nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __API_VENC_TYPES_H__
#define __API_VENC_TYPES_H__

#ifdef  __cplusplus
extern  "C" {
#endif


/*!
  \def API_MAX_NAL_NUM
  Defines maxumum number of NAL in an encoded frame.
 */
#define API_MAX_NAL_NUM     255


/*!
  \def API_MAX_SEI_NUM
  Defines maximum number of SEI encoder can take.
 */
#define API_MAX_SEI_NUM     5


/*!
  \def API_MAX_BITRATE
  Defines maximum bitrate encoder can accept. Unit: kbps
 */
#define API_MAX_BITRATE     500000


/*!
  \def API_VERSION_SIZE_DRIVER
  Defines bufffer size for sotring driver version
 */
#define API_VERSION_SIZE_DRIVER             20


/*!
  \def API_VERSION_SIZE_HEVC_ENCODER_FIRM
  Defines bufffer size for sotring encoder firmware version
 */
#define API_VERSION_SIZE_HEVC_ENCODER_FIRM  (15 * sizeof(uint32_t))


/*!
  \def API_VERSION_SIZE_SYSTEM_FIRM
  Defines bufffer size for sotring system firmware version
 */
#define API_VERSION_SIZE_SYSTEM_FIRM        ( 5 * sizeof(uint32_t))


/*!
  \def API_CHIP_TYPE
  Defines hardware chip type for project
 */
#define API_CHIP_M31    0
#define API_CHIP_M30    1
#define API_CHIP_TYPE   API_CHIP_M31
//#define API_CHIP_TYPE   API_CHIP_M30

/*!
 * \enum API_VENC_RET_E
 * \b API_VENC_RET_E enumerates the return values of VEGA330X API.
 *
    Enum                        | Description
    --------------------------- | --------------------
    API_VENC_RET_SUCCESS         | Function executes correctly
    API_VENC_RET_FAIL            | Can not executes function
    API_VENC_RET_EMPTY           | No output can be read
    API_VENC_RET_NO_LAST_FRAME   | Last frame is not pushed
    API_VENC_RET_NO_LAST_ES      | Last ES is not poped
    API_VENC_RET_OUT_OF_RANGE    | Input value is out of spec
    API_VENC_RET_NO_MEM          | Can not allocate needed memory
 *
 */
typedef enum
{
    API_VENC_RET_SUCCESS,    /**< OK */

    API_VENC_RET_FAIL,       /**< NG */

    API_VENC_RET_EMPTY,

    API_VENC_RET_NO_LAST_FRAME,

    API_VENC_RET_NO_LAST_ES,

    API_VENC_RET_OUT_OF_RANGE,

    API_VENC_RET_NO_MEM,
} API_VENC_RET_E;


/*!
 * \enum API_VENC_STATUS_E
 * \b API_VENC_STATUS_E enumerates the VEGA330X API status.
 */
typedef enum
{
    API_VENC_STATUS_OFF,
    API_VENC_STATUS_STANDBY,
    API_VENC_STATUS_ENCODING,
    API_VENC_STATUS_ERROR,
    API_VENC_STATUS_UNAVAILABLE,
} API_VENC_STATUS_E;


/*!
 * \enum API_VENC_BOARD_E
 * \b API_VENC_BOARD_E enumerates the board ID.
 */
typedef enum
{
    API_VENC_BOARD_1,
    API_VENC_BOARD_2,
    API_VENC_BOARD_3,
    API_VENC_BOARD_4,
    API_VENC_BOARD_5,
    API_VENC_BOARD_6,
    API_VENC_BOARD_7,
    API_VENC_BOARD_8,
    API_VENC_BOARD_MAX,
} API_VENC_BOARD_E;


/*!
 * \enum API_VENC_CHN_E
 * \b API_VENC_CHN_E enumerates channel ID.
 */
typedef enum
{
    API_VENC_CHN_1,
    API_VENC_CHN_2,
    API_VENC_CHN_3,
    API_VENC_CHN_4,
    API_VENC_CHN_5,
    API_VENC_CHN_6,
    API_VENC_CHN_7,
    API_VENC_CHN_8,
    API_VENC_CHN_9,
    API_VENC_CHN_10,
    API_VENC_CHN_11,
    API_VENC_CHN_12,
    API_VENC_CHN_13,
    API_VENC_CHN_14,
    API_VENC_CHN_15,
    API_VENC_CHN_16,
    API_VENC_CHN_MAX,
} API_VENC_CHN_E;


/*!
 * \enum API_VENC_INPUT_MODE_E
 * \b API_VENC_INPUT_MODE_E enumerates the input source for M31 device.
 *
    Enum                                       | Description
    ------------------------------------------ | --------------------
    API_VENC_INPUT_MODE_DATA                    | Input source is from host
    API_VENC_INPUT_MODE_VIF_SQUARE              | Input source is from video interface and the input format of 4K is Square division
    API_VENC_INPUT_MODE_VIF_2_SAMPLE_INTERLEAVE | Input source is from video interface and the input format of 4K is 2-Sample interleave division format
 *
 */
typedef enum
{
    API_VENC_INPUT_MODE_DATA,
    API_VENC_INPUT_MODE_VIF_SQUARE,
    API_VENC_INPUT_MODE_VIF_2_SAMPLE_INTERLEAVE,
} API_VENC_INPUT_MODE_E;

/*!
 * \enum API_VENC_VIF_MODE_INPUT_PORT_E
 * \b API_VENC_VIF_MODE_INPUT_PORT_E enumerates the SDI input port for M31 device.
 *
    Enum                                | Description
    ----------------------------------- | --------------------
    API_VENC_VIF_MODE_INPUT_PORT_DEFAULT | SDI input source is from default port (VI0: PortA/VI1: PortB/VI2: PortC/VI3: PortD)
    API_VENC_VIF_MODE_INPUT_PORT_A       | SDI input source is from Port A
    API_VENC_VIF_MODE_INPUT_PORT_B       | SDI input source is from Port B
    API_VENC_VIF_MODE_INPUT_PORT_C       | SDI input source is from Port C
    API_VENC_VIF_MODE_INPUT_PORT_D       | SDI input source is from Port D
 *
 */
typedef enum
{
    API_VENC_VIF_MODE_INPUT_PORT_DEFAULT,
    API_VENC_VIF_MODE_INPUT_PORT_A = 1,
    API_VENC_VIF_MODE_INPUT_PORT_B = 2,
    API_VENC_VIF_MODE_INPUT_PORT_C = 4,
    API_VENC_VIF_MODE_INPUT_PORT_D = 8,
} API_VENC_VIF_MODE_INPUT_PORT_E;


typedef enum
{
    API_VENC_VIN_MODE_AUTO,
    API_VENC_VIN_MODE_MANUAL,
} API_VENC_VIN_MODE_E;


/*!
 * \enum API_VENC_VIF_ROBUST_MODE_E
 * \b API_VENC_VIF_ROBUST_MODE_E enumerates the robustness method for SDI input port.
 *
    Enum                                  | Description
    ------------------------------------- | --------------------
    API_VENC_VIF_ROBUST_MODE_STOP_ENCODING | The encoder stops encoding while the video signal is lost
    API_VENC_VIF_ROBUST_MODE_BLUE_SCREEN   | The encoder encodes "blue screen" while the video signal is lost
 *
 */
typedef enum
{
    API_VENC_VIF_ROBUST_MODE_STOP_ENCODING,
    API_VENC_VIF_ROBUST_MODE_BLUE_SCREEN,
} API_VENC_VIF_ROBUST_MODE_E;

/*!
 * \enum API_VENC_MEMORY_ALLOC_MODE_E
 * \b API_VENC_MEMORY_ALLOC_MODE_E enumerates the memory allocation mode for M31 device.
 *
    Enum                                       | Description
    ------------------------------------------ | --------------------
    API_VENC_MEMORY_ALLOC_MODE_1CH_4K2K         | Specify the memory allocation mode is 4K2K. The maximum resolution is 4K2K and the maximum number of channels is 1.
    API_VENC_MEMORY_ALLOC_MODE_4CH_1080P        | Specify the memory allocation mode is 1080P. The maximum resolution is 1080P and the maximum number of channels is 4.
    API_VENC_MEMORY_ALLOC_MODE_8CH_720P         | Specify the memory allocation mode is 720P. The maximum resolution is 720P and the maximum number of channels is 8.
    API_VENC_MEMORY_ALLOC_MODE_8CH_MIXING       | Specify the memory allocation mode is MIXING. The maximum resolution is 1080P and the maximum number of channels is 8.
    API_VENC_MEMORY_ALLOC_MODE_16CH_SD          | Specify the memory allocation mode is SD. The maximum resolution is SD and the maximum number of channels is 16.
    API_VENC_MEMORY_ALLOC_MODE_16CH_SEQUENCE    | Specify the memory allocation mode is SEQUENCE. The maximum resolutions are ordered in a sequence from large to small(CH0~CH3:1080P,CH4~CH7:720P,CH8~CH15:SD). The maximum number of channels is 16.
    API_VENC_MEMORY_ALLOC_MODE_16CH_720P_MIXING | Specify the memory allocation mode is 720P_MIXING. The maximum resolution is 720P and the maximum number of channels is 16.
    API_VENC_MEMORY_ALLOC_MODE_INVALID          | There is no channel in encode status. The memory allocation mode is not set.
 *
 */
typedef enum
{
    API_VENC_MEMORY_ALLOC_MODE_1CH_4K2K,
    API_VENC_MEMORY_ALLOC_MODE_4CH_1080P,
    API_VENC_MEMORY_ALLOC_MODE_8CH_720P,
    API_VENC_MEMORY_ALLOC_MODE_8CH_MIXING,
    API_VENC_MEMORY_ALLOC_MODE_16CH_SD,
    API_VENC_MEMORY_ALLOC_MODE_16CH_SEQUENCE,
    API_VENC_MEMORY_ALLOC_MODE_16CH_720P_MIXING,
    API_VENC_MEMORY_ALLOC_MODE_INVALID,
} API_VENC_MEMORY_ALLOC_MODE_E;


/*!
 * \enum API_VENC_HEVC_PROFILE_E
 * \b API_VENC_HEVC_PROFILE_E enumerates HEVC profiles accepted by M31.
 *
 * A profile is a defined set of coding tools that can be used to create a bitstream that conforms to that profile.
 *
 * The detailed description of HEVC profile is in ITU-T H.265, Annex A.3.
 *
    Enum                                  | Description
    ------------------------------------- | --------------------
    API_VENC_HEVC_MAIN_PROFILE             | Main profile allows for a bit depth of 8-bits per sample with 4:2:0 chroma sampling
    API_VENC_HEVC_MAIN10_PROFILE           | Main 10 profile allows for a bit depth of 8-bits to 10-bits per sample with 4:2:0 chroma sampling
    API_VENC_HEVC_MAINSTILLPICTURE_PROFILE | Main Still Picture profile allows for a single still picture to be encoded with the same constraints as the Main profile
    API_VENC_HEVC_MAIN422_10_PROFILE       | Main 4:2:2 10 profile allows for a bit depth of 8-bits to 10-bits per sample with support for 4:0:0, 4:2:0, and 4:2:2 chroma sampling
 *
 */
typedef enum
{
    API_VENC_HEVC_MAIN_PROFILE              = 1,
    API_VENC_HEVC_MAIN10_PROFILE            = 2,
    API_VENC_HEVC_MAINSTILLPICTURE_PROFILE  = 3,
    API_VENC_HEVC_MAIN422_10_PROFILE        = 4,
} API_VENC_HEVC_PROFILE_E;


/*!
 * \enum API_VENC_HEVC_LEVEL_E
 * \b API_VENC_HEVC_LEVEL_E enumerates HEVC levels.
 *
 * A level is a set of constraints for a bitstream.
 *
 * The detailed definition of HEVC level is in ITU-T H.265, Annex A.4.
 *
    Enum                    | Description
    ------------------------| --------------------
    API_VENC_HEVC_LEVEL_AUTO | Decide by encoder automatically
    API_VENC_HEVC_LEVEL_10   | Level 1.0
    API_VENC_HEVC_LEVEL_20   | Level 2.0
    API_VENC_HEVC_LEVEL_21   | Level 2.1
    API_VENC_HEVC_LEVEL_30   | Level 3.0
    API_VENC_HEVC_LEVEL_31   | Level 3.1
    API_VENC_HEVC_LEVEL_40   | Level 4.0
    API_VENC_HEVC_LEVEL_41   | Level 4.1
    API_VENC_HEVC_LEVEL_50   | Level 5.0
    API_VENC_HEVC_LEVEL_51   | Level 5.1
    API_VENC_HEVC_LEVEL_52   | Level 5.2
    API_VENC_HEVC_LEVEL_60   | Level 6.0
    API_VENC_HEVC_LEVEL_61   | Level 6.1
    API_VENC_HEVC_LEVEL_62   | Level 6.2
 *
 */
typedef enum
{
    API_VENC_HEVC_LEVEL_AUTO,

    API_VENC_HEVC_LEVEL_10 = 10,

    API_VENC_HEVC_LEVEL_20 = 20,
    API_VENC_HEVC_LEVEL_21 = 21,

    API_VENC_HEVC_LEVEL_30 = 30,
    API_VENC_HEVC_LEVEL_31 = 31,

    API_VENC_HEVC_LEVEL_40 = 40,
    API_VENC_HEVC_LEVEL_41 = 41,

    API_VENC_HEVC_LEVEL_50 = 50,
    API_VENC_HEVC_LEVEL_51 = 51,
    API_VENC_HEVC_LEVEL_52 = 52,

    API_VENC_HEVC_LEVEL_60 = 60,
    API_VENC_HEVC_LEVEL_61 = 61,
    API_VENC_HEVC_LEVEL_62 = 62,
} API_VENC_HEVC_LEVEL_E;


/*!
 * \enum API_VENC_HEVC_TIER_E
 * \b API_VENC_HEVC_TIER_E enumerates HEVC tiers.
 *
 * The detailed description of HEVC tier is in ITU-T H.265, Annex A.4.
 *
    Enum                   | Description
    -----------------------| --------------------
    API_VENC_HEVC_MAIN_TIER | Main tier is designed for most applications
    API_VENC_HEVC_HIGH_TIER | High tier is designed for very demanding applications
 *
 */
typedef enum
{
    API_VENC_HEVC_MAIN_TIER,
    API_VENC_HEVC_HIGH_TIER,
} API_VENC_HEVC_TIER_E;


/*!
 * \enum API_VENC_RESOLUTION_E
 * \b API_VENC_RESOLUTION_E enumerates possible input image dimensions.
 *
    Enum                         | Width  | Height
    ---------------------------- | ------ | -------
    API_VENC_RESOLUTION_352x288   | 352    | 288
    API_VENC_RESOLUTION_416x240   | 416    | 240
    API_VENC_RESOLUTION_720x480   | 720    | 480
    API_VENC_RESOLUTION_720x576   | 720    | 576
    API_VENC_RESOLUTION_1280x720  | 1280   | 720
    API_VENC_RESOLUTION_1920x1080 | 1920   | 1080
    API_VENC_RESOLUTION_2048x1080 | 2048   | 1080
    API_VENC_RESOLUTION_3840x2160 | 3840   | 2160
    API_VENC_RESOLUTION_4096x2160 | 4096   | 2160
    API_VENC_RESOLUTION_INVALID   | 0      | 0
 *
 */
typedef enum
{
    API_VENC_RESOLUTION_352x288,
    API_VENC_RESOLUTION_416x240,
    API_VENC_RESOLUTION_720x480,
    API_VENC_RESOLUTION_720x576,
    API_VENC_RESOLUTION_1280x720,
    API_VENC_RESOLUTION_1920x1080,
    API_VENC_RESOLUTION_2048x1080,
    API_VENC_RESOLUTION_3840x2160,
    API_VENC_RESOLUTION_4096x2160,
    API_VENC_RESOLUTION_INVALID,
} API_VENC_RESOLUTION_E;


/*!
 * \enum API_VENC_HEVC_ASPECT_RATIO_IDC_E
 * \b API_VENC_HEVC_ASPECT_RATIO_IDC_E enumerates the sample aspect ratio indicator of the luma samples.
 *
 * The description of aspect ratio is in ITU-T H.265, Table E.1.
 *
    Enum                              | Sample Aspect Ratio
    --------------------------------- | --------------------
    API_VENC_HEVC_ASPECT_RATIO_IDC_0   | Unspecified
    API_VENC_HEVC_ASPECT_RATIO_IDC_1   | 1:1
    API_VENC_HEVC_ASPECT_RATIO_IDC_2   | 12:11
    API_VENC_HEVC_ASPECT_RATIO_IDC_3   | 10:11
    API_VENC_HEVC_ASPECT_RATIO_IDC_4   | 16:11
    API_VENC_HEVC_ASPECT_RATIO_IDC_5   | 40:33
    API_VENC_HEVC_ASPECT_RATIO_IDC_6   | 24:11
    API_VENC_HEVC_ASPECT_RATIO_IDC_7   | 20:11
    API_VENC_HEVC_ASPECT_RATIO_IDC_8   | 32:11
    API_VENC_HEVC_ASPECT_RATIO_IDC_9   | 80:33
    API_VENC_HEVC_ASPECT_RATIO_IDC_10  | 18:11
    API_VENC_HEVC_ASPECT_RATIO_IDC_11  | 15:11
    API_VENC_HEVC_ASPECT_RATIO_IDC_12  | 64:33
    API_VENC_HEVC_ASPECT_RATIO_IDC_13  | 160:99
    API_VENC_HEVC_ASPECT_RATIO_IDC_14  | 4:3
    API_VENC_HEVC_ASPECT_RATIO_IDC_15  | 3:2
    API_VENC_HEVC_ASPECT_RATIO_IDC_16  | 2:1
    API_VENC_HEVC_ASPECT_RATIO_IDC_EXTENDED_SAR | User defined SAR width and height
 */
typedef enum
{
    API_VENC_HEVC_ASPECT_RATIO_IDC_0,
    API_VENC_HEVC_ASPECT_RATIO_IDC_1,
    API_VENC_HEVC_ASPECT_RATIO_IDC_2,
    API_VENC_HEVC_ASPECT_RATIO_IDC_3,
    API_VENC_HEVC_ASPECT_RATIO_IDC_4,
    API_VENC_HEVC_ASPECT_RATIO_IDC_5,
    API_VENC_HEVC_ASPECT_RATIO_IDC_6,
    API_VENC_HEVC_ASPECT_RATIO_IDC_7,
    API_VENC_HEVC_ASPECT_RATIO_IDC_8,
    API_VENC_HEVC_ASPECT_RATIO_IDC_9,
    API_VENC_HEVC_ASPECT_RATIO_IDC_10,
    API_VENC_HEVC_ASPECT_RATIO_IDC_11,
    API_VENC_HEVC_ASPECT_RATIO_IDC_12,
    API_VENC_HEVC_ASPECT_RATIO_IDC_13,
    API_VENC_HEVC_ASPECT_RATIO_IDC_14,
    API_VENC_HEVC_ASPECT_RATIO_IDC_15,
    API_VENC_HEVC_ASPECT_RATIO_IDC_16,
    API_VENC_HEVC_ASPECT_RATIO_IDC_EXTENDED_SAR = 255,
} API_VENC_HEVC_ASPECT_RATIO_IDC_E;


/*!
 * \enum API_VENC_IMAGE_FORMAT_E
 * \b API_VENC_IMAGE_FORMAT_E enumerates the pixel formats supported for input.
 *
    Enum                             | Description
    -------------------------------- | ------------------------
    API_VENC_IMAGE_FORMAT_NV12        | NV12 4:2:0 8bit
    API_VENC_IMAGE_FORMAT_NV16        | NV16 4:2:2 8bit
    API_VENC_IMAGE_FORMAT_YUV420      | YUV planar 4:2:0 8bit
    API_VENC_IMAGE_FORMAT_YUV420P010  | 4:2:0 10bit packed
    API_VENC_IMAGE_FORMAT_YUV422P010  | 4:2:2 10bit packed
    API_VENC_IMAGE_FORMAT_YUV420P10LE | 4:2:0 Enveopled 10bit (16bit)
    API_VENC_IMAGE_FORMAT_YUV422P10LE | 4:2:2 Enveopled 10bit (16bit)
 *
 */
typedef enum
{
    API_VENC_IMAGE_FORMAT_NV12,
    API_VENC_IMAGE_FORMAT_NV16,
    API_VENC_IMAGE_FORMAT_YUV420,
    API_VENC_IMAGE_FORMAT_YUV420P010,
    API_VENC_IMAGE_FORMAT_YUV422P010,
    API_VENC_IMAGE_FORMAT_YUV420P10LE,
    API_VENC_IMAGE_FORMAT_YUV422P10LE,
} API_VENC_IMAGE_FORMAT_E;


/*!
 * \enum API_VENC_CHROMA_FORMAT_E
 * \b API_VENC_CHROMA_FORMAT_E enumerates input chroma pixel formats.
 *
    Enum                                    | Description
    --------------------------------------- | ------------------------
    API_VENC_CHROMA_FORMAT_MONO         | Only luma are sampled
    API_VENC_CHROMA_FORMAT_420          | The two chroma components are sampled at quarter the sample rate of luma: the horizontal and vertical chroma resolution are halved
    API_VENC_CHROMA_FORMAT_422          | The two chroma components are sampled at half the sample rate of luma: the horizontal chroma resolution is halved
    API_VENC_CHROMA_FORMAT_422_to_420   | To convert the format from 422 to 420
 *
 */
typedef enum
{
    API_VENC_CHROMA_FORMAT_MONO,
    API_VENC_CHROMA_FORMAT_420,
    API_VENC_CHROMA_FORMAT_422,
    API_VENC_CHROMA_FORMAT_422_to_420,
} API_VENC_CHROMA_FORMAT_E;


/*!
 * \enum API_VENC_OVERSCAN_INFO_E
 * \b API_VENC_OVERSCAN_INFO_E enumerates VUI overscan information flag.
 *
    Enum                                | Description
    ----------------------------------- | ------------------------
    API_VENC_OVERSCAN_INFO_NOT_PRESENT   | Unspecified
    API_VENC_OVERSCAN_INFO_INAPPROPRIATE | Do not display using overscan
    API_VENC_OVERSCAN_INFO_APPROPRIATE   | Display using overscan 
 *
 */
typedef enum
{
    API_VENC_OVERSCAN_INFO_NOT_PRESENT,
    API_VENC_OVERSCAN_INFO_INAPPROPRIATE,
    API_VENC_OVERSCAN_INFO_APPROPRIATE
} API_VENC_OVERSCAN_INFO_E;


/*!
 * \enum API_VENC_VIDEO_FORMAT_E
 * \b API_VENC_VIDEO_FORMAT_E enumerates the source format of the original analog video prior to digitizing and encoding.
 *
    Enum                                | Description
    ----------------------------------- | ------------------------
    API_VENC_VIDEO_FORMAT_COMPONENT      | YPbPr analog component video
    API_VENC_VIDEO_FORMAT_PAL            | Western Europe
    API_VENC_VIDEO_FORMAT_NTSC           | North America
    API_VENC_VIDEO_FORMAT_SECAM          | France and East Europe
    API_VENC_VIDEO_FORMAT_MAC            | MAC
    API_VENC_VIDEO_FORMAT_UNSPECIFIED    | Unspecified video format
 *
 */
typedef enum
{
    API_VENC_VIDEO_FORMAT_COMPONENT,
    API_VENC_VIDEO_FORMAT_PAL,
    API_VENC_VIDEO_FORMAT_NTSC,
    API_VENC_VIDEO_FORMAT_SECAM,
    API_VENC_VIDEO_FORMAT_MAC,
    API_VENC_VIDEO_FORMAT_UNSPECIFIED
} API_VENC_VIDEO_FORMAT_E;


/*!
 * \enum API_VENC_COLOR_PRIMARY_E
 * \b API_VENC_COLOR_PRIMARY_E enumerates color primaries to use when converting to RGB
 *
    Enum                            | Description
    ------------------------------- | ------------------------
    API_VENC_COLOR_PRIMARY_0         | Reserved
    API_VENC_COLOR_PRIMARY_BT709     | Rec. ITU-R BT.709-5
    API_VENC_COLOR_PRIMARY_2         | Unspecified
    API_VENC_COLOR_PRIMARY_3         | Reserved
    API_VENC_COLOR_PRIMARY_BT470M    | Rec. ITU-R BT.470-6 System M
    API_VENC_COLOR_PRIMARY_BT470BG   | Rec. ITU-R BT.470-6 System B, G
    API_VENC_COLOR_PRIMARY_SMPTE170M | Society of Motion Picture and Television Engineers 170M (2004)
    API_VENC_COLOR_PRIMARY_SMPTE240M | Society of Motion Picture and Television Engineers 240M (1999)
    API_VENC_COLOR_PRIMARY_FILM      | Generic film
    API_VENC_COLOR_PRIMARY_BT2020    | Rec. ITU-R BT.2020
    API_VENC_COLOR_PRIMARY_RESERVED  | Reserved
 *
 */
typedef enum
{
    API_VENC_COLOR_PRIMARY_0,
    API_VENC_COLOR_PRIMARY_BT709,
    API_VENC_COLOR_PRIMARY_2,
    API_VENC_COLOR_PRIMARY_3,
    API_VENC_COLOR_PRIMARY_BT470M,
    API_VENC_COLOR_PRIMARY_BT470BG,
    API_VENC_COLOR_PRIMARY_SMPTE170M,
    API_VENC_COLOR_PRIMARY_SMPTE240M,
    API_VENC_COLOR_PRIMARY_FILM,
    API_VENC_COLOR_PRIMARY_BT2020,
    API_VENC_COLOR_PRIMARY_RESERVED
} API_VENC_COLOR_PRIMARY_E;


/*!
 * \enum API_VENC_TRANSFER_CHAR_E
 * \b API_VENC_TRANSFER_CHAR_E enumerates the opto-electronic transfer characteristic of the source picture.
 *
    Enum                                | Description
    ----------------------------------- | ------------------------
    API_VENC_TRANSFER_CHAR_0             | Reserved
    API_VENC_TRANSFER_CHAR_BT709         | Rec. ITU-R BT.709-5
    API_VENC_TRANSFER_CHAR_2             | Unspecified
    API_VENC_TRANSFER_CHAR_3             | Reserved
    API_VENC_TRANSFER_CHAR_BT470M        | Rec. ITU-R BT.470-6 System M
    API_VENC_TRANSFER_CHAR_BT470BG       | Rec. ITU-R BT.470-6 System B, G
    API_VENC_TRANSFER_CHAR_SMPTE170M     | Society of Motion Picture and Television Engineers 170M (2004)
    API_VENC_TRANSFER_CHAR_SMPTE240M     | Society of Motion Picture and Television Engineers 240M (1999)
    API_VENC_TRANSFER_CHAR_LINEAR        | Linear transfer characteristics
    API_VENC_TRANSFER_CHAR_LOG100        | Logarithmic transfer characteristic (100:1 range)
    API_VENC_TRANSFER_CHAR_LOG316        | Logarithmic transfer characteristic (100 * Sqrt( 10 ) : 1 range)
    API_VENC_TRANSFER_CHAR_IEC61966_2_4  | IEC 61966-2-4
    API_VENC_TRANSFER_CHAR_BT1361E       | Rec. ITU-R BT.1361 extended colour gamut system
    API_VENC_TRANSFER_CHAR_IEC61966_2_1  | IEC 61966-2-1 (sRGB or sYCC)
    API_VENC_TRANSFER_CHAR_BT2020_10     | Rec. ITU-R BT.2020 for 10 bit system
    API_VENC_TRANSFER_CHAR_BT2020_12     | Rec. ITU-R BT.2020 for 12 bit system
 *
 */
typedef enum
{
    API_VENC_TRANSFER_CHAR_0,
    API_VENC_TRANSFER_CHAR_BT709,
    API_VENC_TRANSFER_CHAR_2,
    API_VENC_TRANSFER_CHAR_3,
    API_VENC_TRANSFER_CHAR_BT470M,
    API_VENC_TRANSFER_CHAR_BT470BG,
    API_VENC_TRANSFER_CHAR_SMPTE170M,
    API_VENC_TRANSFER_CHAR_SMPTE240M,
    API_VENC_TRANSFER_CHAR_LINEAR,
    API_VENC_TRANSFER_CHAR_LOG100,
    API_VENC_TRANSFER_CHAR_LOG316,
    API_VENC_TRANSFER_CHAR_IEC61966_2_4,
    API_VENC_TRANSFER_CHAR_BT1361E,
    API_VENC_TRANSFER_CHAR_IEC61966_2_1,
    API_VENC_TRANSFER_CHAR_BT2020_10,
    API_VENC_TRANSFER_CHAR_BT2020_12,
    API_VENC_TRANSFER_CHAR_RESERVED
} API_VENC_TRANSFER_CHAR_E;


/*!
 * \enum API_VENC_MATRIX_COEFFS_E
 * \b API_VENC_MATRIX_COEFFS_E enumerates the matrix coefficients used in deriving luma and chroma signals from the green, blue, and red primaries.
 *
    Enum                            | Description
    ------------------------------- | ------------------------
    API_VENC_MATRIX_COEFFS_GBR       | RGB
    API_VENC_MATRIX_COEFFS_BT709     | Rec. ITU-R BT.709-5
    API_VENC_MATRIX_COEFFS_2         | Unspecified
    API_VENC_MATRIX_COEFFS_3         | Reserved
    API_VENC_MATRIX_COEFFS_FCC       | United States Federal Communications Commission Title 47 Code of Federal Regulations (2003) 73.682 (a) (20)
    API_VENC_MATRIX_COEFFS_BT470BG   | Rec. ITU-R BT.470-6 System B, G
    API_VENC_MATRIX_COEFFS_SMPTE170M | Society of Motion Picture and Television Engineers 170M (2004)
    API_VENC_MATRIX_COEFFS_SMPTE240M | Society of Motion Picture and Television Engineers 240M (1999)
    API_VENC_MATRIX_COEFFS_YCGCO     | See Equations E-22 to E-36
    API_VENC_MATRIX_COEFFS_BT2020NC  | Rec. ITU-R BT.2020 non-constant luminance system
    API_VENC_MATRIX_COEFFS_BT2020C   | Rec. ITU-R BT.2020 constant luminance system
 *
 */
typedef enum
{
    API_VENC_MATRIX_COEFFS_GBR,
    API_VENC_MATRIX_COEFFS_BT709,
    API_VENC_MATRIX_COEFFS_2,
    API_VENC_MATRIX_COEFFS_3,
    API_VENC_MATRIX_COEFFS_FCC,
    API_VENC_MATRIX_COEFFS_BT470BG,
    API_VENC_MATRIX_COEFFS_SMPTE170M,
    API_VENC_MATRIX_COEFFS_SMPTE240M,
    API_VENC_MATRIX_COEFFS_YCGCO,
    API_VENC_MATRIX_COEFFS_BT2020NC,
    API_VENC_MATRIX_COEFFS_BT2020C,
    API_VENC_MATRIX_COEFFS_RESERVED
} API_VENC_MATRIX_COEFFS_E;


/*!
 * \enum API_VENC_CHROMA_SAMPLE_POSITION_E
 * \b API_VENC_CHROMA_SAMPLE_POSITION_E enumerates chroma sampling location.
 *
    Enum                                        | Description
    ------------------------------------------- | ------------------------
    API_VENC_CHROMA_SAMPLE_POSITION_LEFT         | Sampling chroma at left
    API_VENC_CHROMA_SAMPLE_POSITION_CENTER       | Sampling chroma at center
    API_VENC_CHROMA_SAMPLE_POSITION_UP_LEFT      | Sampling chroma at upper left
    API_VENC_CHROMA_SAMPLE_POSITION_UP           | Sampling chroma at up
    API_VENC_CHROMA_SAMPLE_POSITION_BOT_LEFT     | Sampling chroma at bottom left
    API_VENC_CHROMA_SAMPLE_POSITION_BOT          | Sampling chroma at bottom
 *
 */
typedef enum
{
    API_VENC_CHROMA_SAMPLE_POSITION_LEFT,
    API_VENC_CHROMA_SAMPLE_POSITION_CENTER,
    API_VENC_CHROMA_SAMPLE_POSITION_UP_LEFT,
    API_VENC_CHROMA_SAMPLE_POSITION_UP,
    API_VENC_CHROMA_SAMPLE_POSITION_BOT_LEFT,
    API_VENC_CHROMA_SAMPLE_POSITION_BOT,
    API_VENC_CHROMA_SAMPLE_POSITION_INVALID
} API_VENC_CHROMA_SAMPLE_POSITION_E;


/*!
 * \enum API_VENC_BIT_DEPTH_E
 * \b API_VENC_BIT_DEPTH_E enumerates the possible color depth per pixel.
 *
    Enum                 | Description
    -------------------- | ------------------------
    API_VENC_BIT_DEPTH_8  | color depth is in 8 bit
    API_VENC_BIT_DEPTH_10 | color depth is in 10 bit
 *
 */
typedef enum
{
    API_VENC_BIT_DEPTH_8,
    API_VENC_BIT_DEPTH_10,
} API_VENC_BIT_DEPTH_E;


/*!
 * \enum API_VENC_FPS_E
 * \b API_VENC_FPS_E enumerates the possible output frame rates.
 *
 * HEVC frame rate is calculated by formula: vps_num_units_in_tick / vps_time_scale
 *
 *
    Enum                | vps_num_units_in_tick | vps_time_scale
    ------------------- | --------------------- | ---------------
    API_VENC_FPS_15      | 15                    | 1
    API_VENC_FPS_23_98   | 24000                 | 1001
    API_VENC_FPS_24      | 24                    | 1
    API_VENC_FPS_25      | 25                    | 1
    API_VENC_FPS_29_97   | 30000                 | 1001
    API_VENC_FPS_30      | 30                    | 1
    API_VENC_FPS_50      | 50                    | 1
    API_VENC_FPS_59_94   | 60000                 | 1001
    API_VENC_FPS_60      | 60                    | 1
    API_VENC_FPS_CUSTOMED| u32NumUnitsInTicks    | u32TimeScale
 *
 */
typedef enum
{
    API_VENC_FPS_15      = 15,
    API_VENC_FPS_23_98   = 23,
    API_VENC_FPS_24      = 24,
    API_VENC_FPS_25      = 25,
    API_VENC_FPS_29_97   = 29,
    API_VENC_FPS_30      = 30,
    API_VENC_FPS_50      = 50,
    API_VENC_FPS_59_94   = 59,
    API_VENC_FPS_60      = 60,
    API_VENC_FPS_CUSTOMED = 255,
} API_VENC_FPS_E;


/*!
 * \enum API_VENC_GOP_TYPE_E
 * \b API_VENC_GOP_TYPE_E enumerates the possible group of picture ncoding methods.
 *
    Enum                    | Description
    ----------------------- | ---------------------------------------------
    API_VENC_GOP_I      | All frames are intra frames
    API_VENC_GOP_IP     | Intra frame and predictive frame only
    API_VENC_GOP_IPB    | Intra frame, predictive frame and bi-predictive frame. Number of B frame (\b eBFrameNum) must be specified. eBFrameNum can be 1, 3, and 7.
    API_VENC_GOP_IB     | Intra frame and bi-predictive frame. Number of B frame (\b eBFrameNum) must be specified. eBFrameNum can be 1, 2, 4 and 8.
 *
 */
typedef enum
{
    API_VENC_GOP_I,
    API_VENC_GOP_IP,
    API_VENC_GOP_IPB,
    API_VENC_GOP_IB,
} API_VENC_GOP_TYPE_E;


/*!
 * \enum API_VENC_GOP_HIERARCHY_E
 * \b API_VENC_GOP_HIERARCHY_E enumerates the hierarchy method of the gop.
 *
    Enum                                            | Description
    ----------------------------------------------- | ---------------------------------------------
    API_VENC_GOP_HIERARCHY                      | Hierarchical GOP.
    API_VENC_GOP_HIERARCHY_NONE                 | Non hierarchical GOP.
    API_VENC_GOP_HIERARCHY_NO_LEADING_PICTURE   | Use IDR_N_LP.
 *
 */
typedef enum
{
    API_VENC_GOP_HIERARCHY,
    API_VENC_GOP_HIERARCHY_NONE,
    API_VENC_GOP_HIERARCHY_NO_LEADING_PICTURE,
} API_VENC_GOP_HIERARCHY_E;


/*!
 * \enum API_VENC_GOP_SIZE_E
 * \b API_VENC_GOP_SIZE_E enumerates GOP size, the number of frames between two consecutive intra frames
 *
    Enum               | Description
    ------------------ | ---------------
    API_VENC_GOP_SIZE_0 | Except for first I, no other I frame allowed
    API_VENC_GOP_SIZE_1 | Intra frame only
    API_VENC_GOP_SIZE_X | X = number of I + number of P + number of B
 *
 */
typedef enum
{
    API_VENC_GOP_SIZE_0  = 0,
    API_VENC_GOP_SIZE_1  = 1,
    API_VENC_GOP_SIZE_24 = 24,
    API_VENC_GOP_SIZE_25 = 25,
    API_VENC_GOP_SIZE_30 = 30,
    API_VENC_GOP_SIZE_32 = 32,
    API_VENC_GOP_SIZE_60 = 60,
    API_VENC_GOP_SIZE_64 = 64,
    API_VENC_GOP_SIZE_100 = 100,
    API_VENC_GOP_SIZE_128 = 128,
} API_VENC_GOP_SIZE_E;


/*!
 * \enum API_VENC_B_FRAME_NUM_E
 * \b API_VENC_B_FRAME_NUM_E enumerates the possible settings of B frame number in a GOP.
 *
 * The encoded GOP structure is influenced by API_VENC_B_FRAME_NUM_E and API_VENC_GOP_TYPE_E.
 *
    Enum                  | API_VENC_GOP_IB  | API_VENC_GOP_IPB
    --------------------- | --------------- | ----------------
    API_VENC_B_FRAME_ONE   | B               | PB
    API_VENC_B_FRAME_TWO   | BB              | x
    API_VENC_B_FRAME_THREE | x               | PBBB
    API_VENC_B_FRAME_FOUR  | BBBB            | x
    API_VENC_B_FRAME_SEVEN | x               | PBBBBBBB
    API_VENC_B_FRAME_MAX   | BBBBBBBB        | PBBBBBBB
 *
 */
typedef enum
{
    API_VENC_B_FRAME_NONE    = 0,
    API_VENC_B_FRAME_ONE     = 1,
    API_VENC_B_FRAME_TWO     = 2,
    API_VENC_B_FRAME_THREE   = 3,
    API_VENC_B_FRAME_FOUR    = 4,
    API_VENC_B_FRAME_FIVE    = 5,
    API_VENC_B_FRAME_SIX     = 6,
    API_VENC_B_FRAME_SEVEN   = 7,
    API_VENC_B_FRAME_MAX     = 8,
} API_VENC_B_FRAME_NUM_E;


/*!
 * \enum API_VENC_IDR_FRAME_NUM_E
 * \b API_VENC_IDR_FRAME_NUM_E enumerates interval between two IDR frames; unit of this parameter is intraFrameInterval(IRAP)
 *
    Enum                         | Description
    ---------------------------- | ---------------
    API_VENC_IDR_FRAME_FIRST | Only first IRAP frame as IDR (open GOP)
    API_VENC_IDR_FRAME_ALL   | All IRAP frames are also IDR (closed GOP)
    API_VENC_IDR_FRAME_TWO   | Every two IRAP frames has one as IDR
    API_VENC_IDR_FRAME_100   | Every 100 IRAP frames has one as IDR
 *
 */
typedef enum
{
    API_VENC_IDR_FRAME_FIRST = 0,
    API_VENC_IDR_FRAME_ALL   = 1,
    API_VENC_IDR_FRAME_TWO   = 2,
    API_VENC_IDR_FRAME_100   = 100,
} API_VENC_IDR_FRAME_NUM_E;


/*!
 * \enum API_VENC_HEVC_IDR_TYPE_E
 * \b API_VENC_HEVC_IDR_TYPE_E enumerates IDR NAL type.
 *
    Enum                              | Description
    --------------------------------- | ---------------
    API_VENC_HEVC_IDR_TYPE_W_RADL | Use random access decodable leading pictures IDR NAL
    API_VENC_HEVC_IDR_TYPE_N_LP   | Use no leading picture IDR NAL
 *
 */
typedef enum
{
    API_VENC_HEVC_IDR_TYPE_W_RADL,
    API_VENC_HEVC_IDR_TYPE_N_LP,
} API_VENC_HEVC_IDR_TYPE_E;


/*!
 * \enum API_VENC_FRAME_TYPE_E
 * \b API_VENC_FRAME_TYPE_E enumerates encoded frame type.
 *
 *
    Enum                 | Description
    -------------------- | ------------------------
    API_VENC_FRAME_TYPE_I | Encoded frame contains intra slices only
    API_VENC_FRAME_TYPE_P | Encoded frame may contain predictive slices
    API_VENC_FRAME_TYPE_B | Encoded frame may contain bi-predictive slices
 *
 */
typedef enum
{
    API_VENC_FRAME_TYPE_I,
    API_VENC_FRAME_TYPE_P,
    API_VENC_FRAME_TYPE_B,
} API_VENC_FRAME_TYPE_E;


typedef enum
{
    API_VENC_PICTURE_STRUCT_FRAME,
    API_VENC_PICTURE_STRUCT_FIELD_TOP,
    API_VENC_PICTURE_STRUCT_FIELD_BOT,
} API_VENC_PICTURE_STRUCT_E;


/*!
 * \enum API_VENC_NAL_UNIT_TYPE_E
 * \b API_VENC_NAL_UNIT_TYPE_E enumerates HEVC NAL types
 * The description of nal unit type is in ITU-T H.265, Table 7.1.
 *
    Enum                                        | Description
    ------------------------------------------- | ------------------------
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_TRAIL_N   | Non-TSA, non-STSA trailing, sub-layer non reference
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_TRAIL_R   | Non-TSA, non-STSA trailing, sub-layer reference
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_TSA_N     | Temporal sub-layer access, sub-layer non reference
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_TSA_R     | Temporal sub-layer access, sub-layer reference
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_STSA_N    | Step-wise temporal sub-layer, sub-layer non reference
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_STSA_R    | Step-wise temporal sub-layer, sub-layer reference
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_RADL_N    | Random access decodable, sub-layer non reference
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_RADL_R    | Random access decodable, sub-layer reference
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_RASL_N    | Random access skipped leading, sub-layer non reference
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_RASL_R    | Random access skipped leading, sub-layer reference
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_BLA_W_LP  | Broken link access, may have leading picture
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_BLA_W_RADL| Broken link access, may have RADL
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_BLA_N_LP  | Broken link access, without leading picture
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_IDR_W_RADL| IDR, may have RADL
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_IDR_N_LP  | IDR, without leading picture
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_CRA       | Clean random access
    API_VENC_HEVC_NAL_UNIT_VPS                   | Video parameter set
    API_VENC_HEVC_NAL_UNIT_SPS                   | Sequence parameter set
    API_VENC_HEVC_NAL_UNIT_PPS                   | Picture parameter set
    API_VENC_HEVC_NAL_UNIT_EOS                   | End of sequence
    API_VENC_HEVC_NAL_UNIT_EOB                   | End of bitstream
    API_VENC_HEVC_NAL_UNIT_FILLER_DATA           | Filler data
    API_VENC_HEVC_NAL_UNIT_PREFIX_SEI            | Supplemental enhancement information
    API_VENC_HEVC_NAL_UNIT_SUFFIX_SEI            | Supplemental enhancement information
 *
 */
typedef enum
{
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_TRAIL_N = 0, // 0
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_TRAIL_R,     // 1

    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_TSA_N,       // 2
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_TSA_R,       // 3

    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_STSA_N,      // 4
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_STSA_R,      // 5

    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_RADL_N,      // 6
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_RADL_R,      // 7

    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_RASL_N,      // 8
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_RASL_R,      // 9

    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL_N10,
    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL_R11,
    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL_N12,
    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL_R13,
    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL_N14,
    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL_R15,

    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_BLA_W_LP,    // 16
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_BLA_W_RADL,  // 17
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_BLA_N_LP,    // 18
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_IDR_W_RADL,  // 19
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_IDR_N_LP,    // 20
    API_VENC_HEVC_NAL_UNIT_CODED_SLICE_CRA,         // 21
    API_VENC_HEVC_NAL_UNIT_RESERVED_IRAP_VCL22,
    API_VENC_HEVC_NAL_UNIT_RESERVED_IRAP_VCL23,

    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL24,
    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL25,
    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL26,
    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL27,
    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL28,
    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL29,
    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL30,
    API_VENC_HEVC_NAL_UNIT_RESERVED_VCL31,

    API_VENC_HEVC_NAL_UNIT_VPS,                     // 32
    API_VENC_HEVC_NAL_UNIT_SPS,                     // 33
    API_VENC_HEVC_NAL_UNIT_PPS,                     // 34
    API_VENC_HEVC_NAL_UNIT_ACCESS_UNIT_DELIMITER,   // 35
    API_VENC_HEVC_NAL_UNIT_EOS,                     // 36
    API_VENC_HEVC_NAL_UNIT_EOB,                     // 37
    API_VENC_HEVC_NAL_UNIT_FILLER_DATA,             // 38
    API_VENC_HEVC_NAL_UNIT_PREFIX_SEI,              // 39
    API_VENC_HEVC_NAL_UNIT_SUFFIX_SEI,              // 40

    API_VENC_HEVC_NAL_UNIT_RESERVED_NVCL41,
    API_VENC_HEVC_NAL_UNIT_RESERVED_NVCL42,
    API_VENC_HEVC_NAL_UNIT_RESERVED_NVCL43,
    API_VENC_HEVC_NAL_UNIT_RESERVED_NVCL44,
    API_VENC_HEVC_NAL_UNIT_RESERVED_NVCL45,
    API_VENC_HEVC_NAL_UNIT_RESERVED_NVCL46,
    API_VENC_HEVC_NAL_UNIT_RESERVED_NVCL47,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_48,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_49,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_50,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_51,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_52,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_53,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_54,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_55,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_56,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_57,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_58,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_59,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_60,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_61,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_62,
    API_VENC_HEVC_NAL_UNIT_UNSPECIFIED_63,
    API_VENC_HEVC_NAL_UNIT_INVALID,
} API_VENC_NAL_UNIT_TYPE_E;


/*!
 * \enum API_VENC_SEI_PAYLOAD_TYPE_E
 * \b API_VENC_SEI_PAYLOAD_TYPE_E enumerates SEI payload types
 * The description of nal unit type is in ITU-T H.265, Table D.1.
 *
    Enum                                                          | Description
    ------------------------------------------------------------- | ------------------------    
    API_VENC_SEI_PAYLOAD_TYPE_BUFFERING_PERIOD                     | Buffering period
    API_VENC_SEI_PAYLOAD_TYPE_PICTURE_TIMING                       | Picture timing
    API_VENC_SEI_PAYLOAD_TYPE_PAN_SCAN_RECT                        | Pan-scan rectangle
    API_VENC_SEI_PAYLOAD_TYPE_FILLER_PAYLOAD                       | Filler payload
    API_VENC_SEI_PAYLOAD_TYPE_USER_DATA_REGISTERED_ITU_T_T35       | User data registered by Rec. ITU-T T.35
    API_VENC_SEI_PAYLOAD_TYPE_USER_DATA_UNREGISTERED               | User data unregistered
    API_VENC_SEI_PAYLOAD_TYPE_RECOVERY_POINT                       | Recovery point
    API_VENC_SEI_PAYLOAD_TYPE_SCENE_INFO                           | Scene information
    API_VENC_SEI_PAYLOAD_TYPE_FULL_FRAME_SNAPSHOT                  | Picture snapshot
    API_VENC_SEI_PAYLOAD_TYPE_PROGRESSIVE_REFINEMENT_SEGMENT_START | Progressive refinement segment start
    API_VENC_SEI_PAYLOAD_TYPE_PROGRESSIVE_REFINEMENT_SEGMENT_END   | Progressive refinement segment end
    API_VENC_SEI_PAYLOAD_TYPE_FILM_GRAIN_CHARACTERISTICS           | Film grain characteristics
    API_VENC_SEI_PAYLOAD_TYPE_POST_FILTER_HINT                     | Post-filter hint
    API_VENC_SEI_PAYLOAD_TYPE_TONE_MAPPING_INFO                    | Tone mapping information
    API_VENC_SEI_PAYLOAD_TYPE_FRAME_PACKING                        | Frame packing arrangement
    API_VENC_SEI_PAYLOAD_TYPE_DISPLAY_ORIENTATION                  | Display orientation
    API_VENC_SEI_PAYLOAD_TYPE_SOP_DESCRIPTION                      | Structure of pictures information
    API_VENC_SEI_PAYLOAD_TYPE_ACTIVE_PARAMETER_SETS                | Active parameter sets
    API_VENC_SEI_PAYLOAD_TYPE_DECODING_UNIT_INFO                   | Decoding unit information
    API_VENC_SEI_PAYLOAD_TYPE_TEMPORAL_LEVEL0_INDEX                | Temporal sub-layer zero index
    API_VENC_SEI_PAYLOAD_TYPE_DECODED_PICTURE_HASH                 | Decoded picture hash
    API_VENC_SEI_PAYLOAD_TYPE_SCALABLE_NESTING                     | Scalable nesting
    API_VENC_SEI_PAYLOAD_TYPE_REGION_REFRESH_INFO                  | Region refresh information
 *
 */
typedef enum
{
    API_VENC_SEI_PAYLOAD_TYPE_BUFFERING_PERIOD                     = 0,
    API_VENC_SEI_PAYLOAD_TYPE_PICTURE_TIMING                       = 1,
    API_VENC_SEI_PAYLOAD_TYPE_PAN_SCAN_RECT                        = 2,
    API_VENC_SEI_PAYLOAD_TYPE_FILLER_PAYLOAD                       = 3,
    API_VENC_SEI_PAYLOAD_TYPE_USER_DATA_REGISTERED_ITU_T_T35       = 4,
    API_VENC_SEI_PAYLOAD_TYPE_USER_DATA_UNREGISTERED               = 5,
    API_VENC_SEI_PAYLOAD_TYPE_RECOVERY_POINT                       = 6,
    API_VENC_SEI_PAYLOAD_TYPE_SCENE_INFO                           = 9,
    API_VENC_SEI_PAYLOAD_TYPE_FULL_FRAME_SNAPSHOT                  = 15,
    API_VENC_SEI_PAYLOAD_TYPE_PROGRESSIVE_REFINEMENT_SEGMENT_START = 16,
    API_VENC_SEI_PAYLOAD_TYPE_PROGRESSIVE_REFINEMENT_SEGMENT_END   = 17,
    API_VENC_SEI_PAYLOAD_TYPE_FILM_GRAIN_CHARACTERISTICS           = 19,
    API_VENC_SEI_PAYLOAD_TYPE_POST_FILTER_HINT                     = 22,
    API_VENC_SEI_PAYLOAD_TYPE_TONE_MAPPING_INFO                    = 23,
    API_VENC_SEI_PAYLOAD_TYPE_FRAME_PACKING                        = 45,
    API_VENC_SEI_PAYLOAD_TYPE_DISPLAY_ORIENTATION                  = 47,
    API_VENC_SEI_PAYLOAD_TYPE_SOP_DESCRIPTION                      = 128,
    API_VENC_SEI_PAYLOAD_TYPE_ACTIVE_PARAMETER_SETS                = 129,
    API_VENC_SEI_PAYLOAD_TYPE_DECODING_UNIT_INFO                   = 130,
    API_VENC_SEI_PAYLOAD_TYPE_TEMPORAL_LEVEL0_INDEX                = 131,
    API_VENC_SEI_PAYLOAD_TYPE_DECODED_PICTURE_HASH                 = 132,
    API_VENC_SEI_PAYLOAD_TYPE_SCALABLE_NESTING                     = 133,
    API_VENC_SEI_PAYLOAD_TYPE_REGION_REFRESH_INFO                  = 134,
    API_VENC_SEI_PAYLOAD_TYPE_NO_DISPLAY                           = 135,
    API_VENC_SEI_PAYLOAD_TYPE_TIME_CODE                            = 136,
    API_VENC_SEI_PAYLOAD_TYPE_MASTERING_DISPLAY_COLOUR_VOLUME      = 137,
    API_VENC_SEI_PAYLOAD_TYPE_SEGM_RECT_FRAME_PACKING              = 138,
    API_VENC_SEI_PAYLOAD_TYPE_TEMP_MOTION_CONSTRAINED_TILE_SETS    = 139,
    API_VENC_SEI_PAYLOAD_TYPE_CHROMA_SAMPLING_FILTER_HINT          = 140,
    API_VENC_SEI_PAYLOAD_TYPE_KNEE_FUNCTION_INFO                   = 141
} API_VENC_SEI_PAYLOAD_TYPE_E;


/*!
 * \enum API_VENC_RATE_CTRL_ALGO_E
 * \b API_VENC_RATE_CTRL_ALGO_E enumerates the possible bitrate control algorithms for encoder.
 *
     Enum                              | Description
     --------------------------------- | ------------------------
     API_VENC_RATE_CTRL_ALGO_CBR        | constant bitrate
     API_VENC_RATE_CTRL_ALGO_CAPPED_VBR | variable bitrate with upper bound and lower bound
 *
 */
typedef enum
{
    API_VENC_RATE_CTRL_ALGO_CBR,
    API_VENC_RATE_CTRL_ALGO_CAPPED_VBR,
} API_VENC_RATE_CTRL_ALGO_E;


/*!
 * \enum API_VENC_TIMEBASE_E
 * \b API_VENC_TIMEBASE_E enumerates the possible time base units for PTS.
 *
     Enum                           | Description
     ------------------------------ | ------------------------
     API_VENC_TIMEBASE_SECOND        | Unit of PTS is (1/FPS) second
     API_VENC_TIMEBASE_MILLI_SECOND  | Unit of PTS is (1000/FPS) seconds
     API_VENC_TIMEBASE_90KHZ         | Unit of PTS is 90kHz
 *
 */
typedef enum
{
    API_VENC_TIMEBASE_SECOND,
    API_VENC_TIMEBASE_MILLI_SECOND,
    API_VENC_TIMEBASE_90KHZ,
} API_VENC_TIMEBASE_E;


/*!
 * \enum API_VENC_PTS_MODE_E
 * \b API_VENC_PTS_MODE_E enumerates the possible PTS input mode.
 *
     Enum                           | Description
     ------------------------------ | ------------------------
     API_VENC_PTS_MODE_AUTO          | PTS is incremented automatically
     API_VENC_PTS_MODE_USER          | PTS is set by HOST for each time. Before using \b VEGA330X_ENC_PushImage, please set parameter pts and eTimeBase of \b API_VENC_IMG_T for handling the PTS.
 *
 */
typedef enum
{
    API_VENC_PTS_MODE_AUTO,
    API_VENC_PTS_MODE_USER,
} API_VENC_PTS_MODE_E;


/*!
 * \enum API_VENC_DBG_LEVEL_E
 * \b API_VENC_DBG_LEVEL_E enumerates debug message levels.
 *
 * Higher level prints more messages.
 */
typedef enum
{
    API_VENC_DBG_LEVEL_0,
    API_VENC_DBG_LEVEL_1,
    API_VENC_DBG_LEVEL_2,
    API_VENC_DBG_LEVEL_3,
} API_VENC_DBG_LEVEL_E;



/*!
 *@brief The \b API_VENC_VERSION_INFO_T structure represents version information.
 *
 *
    Member                      | Description
    --------------------------- | ------------------------
    u32KernelVer                | API kernel version
    u32MajorVer                 | API Major version
    u32MinorVer                 | API Minor version
    u32SvnVer                   | API SVN version
    u32McpuKernelVer            | MCPU kernel version
    u32McpuMajorVer             | MCPU Major version
    u32McpuMinorVer             | MCPU Minor version
    u32McpuExtraVer             | MCPU SVN version
    u8Driver                    |
    u8HevcEncoderStdFirmSingle  |
    u8HevcEncoderStdFirmMulti   |
    u8HevcEncoderUserFirmSingle |
    u8HevcEncoderUserFirmMulti  |
    u8SystemFirm                |
 *
 */
typedef struct
{
    uint32_t u32KernelVer;
    uint32_t u32MajorVer;
    uint32_t u32MinorVer;
    uint32_t u32SvnVer;

    uint32_t u32McpuKernelVer;
    uint32_t u32McpuMajorVer;
    uint32_t u32McpuMinorVer;
    uint32_t u32McpuExtraVer;

    uint8_t u8Driver[API_VERSION_SIZE_DRIVER];
    uint8_t u8HevcEncoderStdFirmSingle[API_VERSION_SIZE_HEVC_ENCODER_FIRM];
    uint8_t u8HevcEncoderStdFirmMulti[API_VERSION_SIZE_HEVC_ENCODER_FIRM];
    uint8_t u8HevcEncoderUserFirmSingle[API_VERSION_SIZE_HEVC_ENCODER_FIRM];
    uint8_t u8HevcEncoderUserFirmMulti[API_VERSION_SIZE_HEVC_ENCODER_FIRM];
    uint8_t u8SystemFirm[API_VERSION_SIZE_SYSTEM_FIRM];
} API_VENC_VERSION_INFO_T;


/*!
 *@brief The \b API_VENC_COLOR_DESC_T structure represents VUI color description information.
 *
    Member                      | Description
    --------------------------- | ------------------------
    bPresentFlag                | presentation of color description information in VUI
    eColorPrimaries             | color primaries
    eTransferCharacteristics    | transfer characteristics
    eMatrixCoeff                | matrix coefficient
 *
 */
typedef struct
{
    bool                    bPresentFlag;
    API_VENC_COLOR_PRIMARY_E eColorPrimaries;
    API_VENC_TRANSFER_CHAR_E eTransferCharacteristics;
    API_VENC_MATRIX_COEFFS_E eMatrixCoeff;
} API_VENC_COLOR_DESC_T;


/*!
 *@brief The \b API_VENC_VIDEO_SIGNAL_TYPE_T structure represents VUI video signal information.
 *
    Member          | Description
    --------------- | ------------------------
    bPresentFlag    | presentation of video signal type information in VUI
    eVideoFormat    | video format
    bVideoFullRange | video full range
    tColorDesc      | color description
 *
 */
typedef struct
{
    bool                    bPresentFlag;
    API_VENC_VIDEO_FORMAT_E  eVideoFormat;
    bool                    bVideoFullRange;
    API_VENC_COLOR_DESC_T    tColorDesc;
} API_VENC_VIDEO_SIGNAL_TYPE_T;


/*!
 *@brief The \b API_VENC_CHROMA_LOC_INFO_T structure represents VUI chroma location information.
 *
 * \b API_VENC_CHROMA_LOC_INFO_T specifies the location of chroma samples as 
 * \b API_VENC_CHROMA_SAMPLE_POSITION_E, which conforms the Figure E-1 in spec.
 *
 * When coding progressive source material, eTopFieldLoc and eBotFieldLoc should have the same value.
 *
    Member          | Description
    --------------- | ------------------------
    bChromaLoc      | chroma_loc_info_present_flag
    eTopFieldLoc    | chroma_sample_loc_type_top_field
    eBotFieldLoc    | chroma_sample_loc_type_bottom_field
 *
 */
typedef struct
{
    bool                                bChromaLoc;
    API_VENC_CHROMA_SAMPLE_POSITION_E    eTopFieldLoc;
    API_VENC_CHROMA_SAMPLE_POSITION_E    eBotFieldLoc;
} API_VENC_CHROMA_LOC_INFO_T;


/*!
 *@brief The \b API_VENC_CROP_INFO_T structure represents cropping information.
 *
 * \b API_VENC_CROP_INFO_T specifies the samples of the pictures in the CVS that are output
 * from the decoding process, in terms of a rectangular region specified picture coordinates
 * for output.
 *
 * The conformance cropping window contains the luma samples with horizontal picture coordinates
 * from conf_win_left_offset to pic_width_in_luma_samples - (conf_win_right_offset + 1),
 * vertical picture coordinates from conf_win_top_offset to pic_height_in_luma_samples -
 * (conf_win_bottom_offset + 1),
 *
    Member        | Description
    ------------- | ------------------------
    u32CropLeft   | conf_win_left_offset
    u32CropRight  | conf_win_right_offset
    u32CropTop    | conf_win_top_offset
    u32CropBottom | conf_win_bottom_offset
 *
 */
typedef struct
{
    uint32_t    u32CropLeft;
    uint32_t    u32CropRight;
    uint32_t    u32CropTop;
    uint32_t    u32CropBottom;
} API_VENC_CROP_INFO_T;


/*!
 *@brief The \b API_VENC_FPS_CUSTOMED_T structure represents customed frame rate setting.
 *
 * \b API_VENC_FPS_CUSTOMED_T is activated if 
 * (API_VENC_INIT_PARAM_T::eTargetFrameRate == API_VENC_FPS_CUSTOMED).
 *
 * The tested customed frame rate includes 300, 144, 120, 119.8, 100, 72 & 48.
 *
 *
    Member              | Description
    ------------------- | ------------------------
    u32TimeScale        | customed vps_time_scale
    u32NumUnitsInTicks  | customed vps_num_units_in_tick
 *
 */
typedef struct
{
    uint32_t    u32TimeScale;
    uint32_t    u32NumUnitsInTicks;
} API_VENC_FPS_CUSTOMED_T;


/*!
 *@brief The \b API_VENC_SEI_PARAM_T structure represents a SEI NAL.
 *
 * \b API_VENC_SEI_PARAM_T describes the SEI data prepared by user program.
 *
 * pu8Addr points to a block of data, the first byte of data contains payload type of SEI,
 * and second byte of data contains payload size of SEI. The following bytes(maximum 254)
 * belongs to SEI payload.
 *
 *
    Member          | Description
    --------------- | ------------------------
    ePayloadType    | SEI payload type
    u8PayloadSize   | payload size
    u8PayloadData   | payload data
 *
 */
typedef struct
{
    API_VENC_SEI_PAYLOAD_TYPE_E  ePayloadType;
    uint8_t                     u8PayloadSize;
    uint8_t                     u8PayloadData[253];
} API_VENC_SEI_PARAM_T;


/*!
 *@brief The \b API_VENC_IMG_T structure represents an input image.
 *
 * \b API_VENC_IMG_T structure represents an input frame / image prepared by user of API,
 * to be sent to VEGA330X for encoding.
 *
 * The output format of the encoded frame is described by \b API_VENC_HEVC_CODED_PICT_T
 *
 *
    Member          | Description
    --------------- | ------------------------
    pu8Addr         | Address of input image
    u32Size         | Size of input image
    pts             | PTS associated with input image
    eTimeBase       | PTS unit
    bLastFrame      | Flag current input image to be the last input; after receiving this signal, device encodes any buffered and unencoded frame and flush out
    eFormat         | YUV format of input image
    u32SeiNum       | Number of SEI descriptor associated with input image
    bSeiPassThrough | True if each SEI is as indivisual NAL; all SEIs in one NAL if False;
    tSeiParam       | SEI descriptor associated with input image, to provide user data
 */
typedef struct
{
    /** Address of input image */
    uint8_t *pu8Addr;

    /** Size of input image */
    uint32_t u32Size;

    /** PTS associated with input image */
    uint64_t pts;

    /** PTS unit */
    API_VENC_TIMEBASE_E eTimeBase;

    /**
    Sets current input frame to be the last frame.

    After receiving this signal, device encodes any buffered and unencoded frame and flush out.
    */
    bool bLastFrame;

    /** YUV format of input image */
    API_VENC_IMAGE_FORMAT_E  eFormat;

    /** Number of SEI descriptor associated with image */
    uint32_t                u32SeiNum;

    /** Pass through SEI without encapsulating multiple SEIs into one NAL   */
    /** Each SEI will be an indivisual NAL.                                 */
    bool                    bSeiPassThrough;

    /** SEI descriptor associated with input image, to provide user data */
    API_VENC_SEI_PARAM_T     tSeiParam[API_MAX_SEI_NUM];
} API_VENC_IMG_T;


/**
@brief M31 device information
 *
 *
    Member             | Description
    ------------------ | ------------------------
    dev_num            | Device number: 0~7
    slot_num           | Slot number in the (domain:)bus:slot.func format, ex: 01:00.0
    dev_file_name      | Device file name, ex: /dev/m31fmb0
 */
typedef struct
{
    /** Device number: 0~7 */
    uint32_t dev_num;

    /** Slot number in the (domain:)bus:slot.func format, ex: 01:00.0 */
    char slot_num[32];

    /** Device file name, ex: /dev/m31fmb0 */
    char dev_file_name[32];
} API_VENC_ENUM_DEV_INFO_T;


/**
@brief All M31 device information
 *
 *
    Member             | Description
    ------------------ | ------------------------
    num_of_boards      | The number of boards enumerated by host OS: 0~7
    board_info         | The information of the board enumerated by host OS
 */
typedef struct
{
    /** The number of boards enumerated by host OS: 0~7 */
    uint32_t num_of_boards;

    /** The information of the board enumerated by host OS */
    API_VENC_ENUM_DEV_INFO_T board_info[API_VENC_BOARD_MAX];
} API_VENC_ENUM_INFO_T;


/*!
 *@brief The \b API_VENC_CODING_PARAM_T structure represents a detailed picture coding setting.
 *
 *
    Member                      | Description
    --------------------------- | ------------------------
    bEnableAdaptiveQuantization | Enable adaptive quantization
    u32Qmin                     | Min qp value (M31 unsupported)
    u32Qmax                     | Max qp value (M31 unsupported)
    u32CtuSize                  | Max CTU size
    u32MinCuSize                | Min CU size. 0 = 8x8(default), 8=8x8, 16=16x16, 32=32x32, 64=64x64
    u32MaxTuSize                | Max TU size. 0 = 32x32(default), 4=4x4, 8=8x8, 16=16x16, 32=32x32
    u32MinTuSize                | Min TU size. 0 = 4x4(default), 4=4x4, 8=8x8, 16=16x16, 32=32x32
    u32MaxTuDepthIntra          | Max TU depth for intra frame. Controls max_transform_hierarchy_depth_intra field. Must >= log2(CTU size) - log2(Max TU size).
    u32MaxTuDepthInter          | Max TU depth for inter frame. Controls max_transform_hierarchy_depth_inter field. Must >= log2(CTU size) - log2(Max TU size).
    bDisableDeblocking          | Disable deblocking
    bDisableAMP                 | Disable Asymmetric Motion partitioning
    bDisableSAO                 | Disable Sample Adaptive Offset
 *
 */
typedef struct
{
    /** Enable / disable adaptive quantization */
    bool        bEnableAdaptiveQuantization;

#if (API_CHIP_TYPE == API_CHIP_M31)
#else
    /** Sets minimal q value */
    uint32_t    u32Qmin;

    /** Sets maximal q value */
    uint32_t    u32Qmax;
#endif

    /** Sets Max CTU size */
    uint32_t    u32CtuSize;

    /** Sets Min CU size */
    uint32_t    u32MinCuSize;

    /** Sets Max TU size */
    uint32_t    u32MaxTuSize;

    /** Sets Min TU size */
    uint32_t    u32MinTuSize;

    /** Sets Max TU depth for intra frame */
    uint32_t    u32MaxTuDepthIntra;

    /** Sets Max TU depth for inter frame */
    uint32_t    u32MaxTuDepthInter;

    /** Disable deblocking */
    bool        bDisableDeblocking;

    /** Disable AMP */
    bool        bDisableAMP;

#if (API_CHIP_TYPE == API_CHIP_M31)
#else
    /** Disable SAO */
    bool        bDisableSAO;
#endif

} API_VENC_CODING_PARAM_T;


/*!
 *@brief The \b API_VENC_CHROMA_CONVERT_INFO_T structure represents the coefficients of the chroma 4:2:2 to 4:2:0 convert filter.
 *
 *
    Member              | Description
    ------------------- | ------------------------
    s11C420Coef         | The coefficient of the chroma 4:2:2 to 4:2:0 convert filter. The coefficient is signed 11-bit.
 *
 */
typedef struct
{
    int16_t     s11C420Coef[8];
} API_VENC_CHROMA_CONVERT_INFO_T;


/*!
  *@brief The \b API_VENC_INIT_PARAM_T structure represents initial encoder settings.
  *
  *
    Member                          | Description
    ------------------------------- | ---------------------------------------------------------------
    eInputMode                      | Video input source
    eProfile                        | Profile of encoded bitstream
    eLevel                          | Level of encoded bitstream
    eTier                           | Tier of encoded bitstream
    eResolution                     | Output bitstream resolution
    eAspectRatioIdc                 | Sample aspect ratio IDC
    u32SarWidth                     | Customed sample aspect width
    u32SarHeight                    | Customed sample aspect height
    bDisableVpsTimingInfoPresent    | Embed timing information in VPS
    eChromaFmt                      | Chroma format
    eBitDepth                       | Output bit depth
    bInterlace                      | Interlace / Progressive mode
    tCrop                           | Crop information of output frame
    eTargetFrameRate                | Frame rate of output bitstream
    eIDRFrameNum                    | Number of I frame as IDR frames; i.e. 2 means every one out of 2 I frames is an IDR.
    eGopType                        | Encoding structure in group of picture
    eGopHierarchy                   | GOP encoding hierarchy method
    eGopSize                        | Distance between two IRAPs. unit: number of frames Note: GOP size must be divisible by reference frame number, otherwise causes video image broken near GOP boundary. For example, eGopType = API_VENC_GOP_IB and eBFrameNum = API_VENC_B_FRAME_FOUR, then eGOPSize must be divisible by 4.
    eBFrameNum                      | Number of inserted B frames b/t two referenced frames
    bDisableTemporalId              | Switch off temporal ID
    eRateCtrlAlgo                   | Encoder rate control algorithm
    u32FillerTriggerLevel           | TBA
    u32Bitrate                      | Encoder bitrate. unit: kbps. u32Bitrate <= API_MAX_BITRATE
    u32MaxVBR                       | Encoder bitrate upper bound in VBR mode.(unit: kbps) u32MaxVBR is valid when rate control algorithm(eRateCtrlAlgo) is VBR. Limitation: u32AveVBR <= u32MaxVBR <= u32Bitrate
    u32AveVBR                       | Encoder average bitrate in VBR mode.(unit: kbps) u32AveVBR is valid when rate control algorithm is VBR. Limitation: u32AveVBR <= u32MaxVBR, and u32Bitrate <= 2x u32AveVBR
    u32CpbDelay                     | CPB delay time. 0 = 270,000 (default 3sec);45,000 = 45,000 (0.5s); 90,000 = 90,000 (1s); 270,000 = 270,000 (3s).
    eDbgLevel                       | Controls debug message amount
    tCoding                         | Picture coding parameters
  *
  */
typedef struct
{
    /** Sets input mode from host or video interface */
    API_VENC_INPUT_MODE_E    eInputMode;

    /** Sets the SDI input port for VIF mode */
    API_VENC_VIF_MODE_INPUT_PORT_E    eInputPort;

    /** Sets the robustness method for VIF mode */
    API_VENC_VIF_ROBUST_MODE_E    eRobustMode;

    /** Sets profile of encoder */
    API_VENC_HEVC_PROFILE_E  eProfile;

    /** Sets level of encoder */
    API_VENC_HEVC_LEVEL_E    eLevel;

    /** Sets tier of encoder */
    API_VENC_HEVC_TIER_E     eTier;

    /** Sets the memory allocation mode */
    API_VENC_MEMORY_ALLOC_MODE_E    eMemoryAllocMode;

    /** Sets output resolution generated by encoder */
    API_VENC_RESOLUTION_E    eResolution;

    /** Sets aspect ratio idc */
    API_VENC_HEVC_ASPECT_RATIO_IDC_E eAspectRatioIdc;

    /** Sets customed sample aspect width */
    uint32_t u32SarWidth;

    /** Sets customed sample aspect height */
    uint32_t u32SarHeight;

    /** Sets presentation of vps timing info. Default: use VPS timing infoformation. */
    bool bDisableVpsTimingInfoPresent;

    /** Sets input image format */
    API_VENC_IMAGE_FORMAT_E  eFormat;

    /** Sets chroma format */
    API_VENC_CHROMA_FORMAT_E eChromaFmt;

    /** Sets the coefficients of the chroma 4:2:2 to 4:2:0 convert filter */
    API_VENC_CHROMA_CONVERT_INFO_T tChromaConvertInfo;

    /** Sets VUI overscan information */
    API_VENC_OVERSCAN_INFO_E eOverScan;

    /** Sets VUI video signal information */
    API_VENC_VIDEO_SIGNAL_TYPE_T tVideoSignalType;

    /** Sets VUI chroma location information */
    API_VENC_CHROMA_LOC_INFO_T   tChromaLocation;

    /** Sets output bit depth */
    API_VENC_BIT_DEPTH_E     eBitDepth;

    /** Sets interlace / progressive mode. Default: progressive mode. */
    bool                    bInterlace;

    /** Disable scene change detection. Default: Not use scene change. */
    bool                    bDisableSceneChangeDetect;

    /** Sets crop info of output frame */
    API_VENC_CROP_INFO_T     tCrop;

    /** Sets the frame rate of encoder */
    API_VENC_FPS_E           eTargetFrameRate;

    /** Set customized frame rate */
    API_VENC_FPS_CUSTOMED_T  tCustomedFrameRateInfo;

    /** Sets if encoder accepts user PTS */
    API_VENC_PTS_MODE_E      ePtsMode;

    /** Sets number of I frame as IDR frames */
    API_VENC_IDR_FRAME_NUM_E    eIDRFrameNum;

    /** Sets IDR NAL type */
    API_VENC_HEVC_IDR_TYPE_E    eIDRType;

    /** Sets GOP structure */
    API_VENC_GOP_TYPE_E      eGopType;

    /** Sets hierarchy method */
    API_VENC_GOP_HIERARCHY_E eGopHierarchy;

    /**
    Sets GOP size. Unit: number of frames

    Note: GOP size must be divisible by reference frame number,
    otherwise causes video image broken near GOP boundary.

    For example, eGopType = API_VENC_GOP_IB and eBFrameNum = API_VENC_B_FRAME_FOUR,
    then eGOPSize must be divisible by 4.
    */
    API_VENC_GOP_SIZE_E      eGopSize;

    /** Sets number of inserted B frames b/t two referenced frames */
    API_VENC_B_FRAME_NUM_E   eBFrameNum;

    /** Switch off temporal ID. Default: use temporal ID */
    bool                    bDisableTemporalId;

    /** Sets encoder rate control algorithm */
    API_VENC_RATE_CTRL_ALGO_E    eRateCtrlAlgo;

    /** Unit: percentage */
    uint32_t                u32FillerTriggerLevel;

    /**
    Sets encoder bitrate. Unit: kbps

    Limitation: u32Bitrate <= API_MAX_BITRATE
    */
    uint32_t                u32Bitrate;

    /**
    Sets encoder bitrate upper bound. unit: kbps

    u32MaxVBR is valid when rate control algorithm(eRateCtrlAlgo) is VBR.

    Limitation: u32AveVBR <= u32MaxVBR <= u32Bitrate
    */
    uint32_t                u32MaxVBR;

    /**
    Sets encoder average bitrate. unit: kbps

    u32AveVBR is valid when rate control algorithm is VBR.

    Limitation: u32AveVBR <= u32MaxVBR, and u32Bitrate <= 2x u32AveVBR
    */
    uint32_t                u32AveVBR;

    /**
    Specify the cpb delay time.

    0 = 270,000 (default 3sec),

    45,000 =   45,000 (0.5s)

    90,000 =   90,000 (1s)

    270,000 = 270,000 (3s)
    */
    uint32_t                u32CpbDelay;

    /** Sets debug message level */
    API_VENC_DBG_LEVEL_E    eDbgLevel;

    bool                    bDisableMonitor;

    /** Sets picture coding parameters */
    API_VENC_CODING_PARAM_T tCoding;
} API_VENC_INIT_PARAM_T;


/*!
  *@brief The \b API_VENC_NAL_T structure represents a NAL.
  *
  * The pu8Addr, u32Length may be used to obtained NAL data.
  *
  * The eNalType may be used to determine if this NAL is useful to user program.
  *
    Member    | Description
    ----------| -------------
    pu8Addr   | NAL address
    u32Length | NAL length
    eNalType  | NAL type
  *
  */
typedef struct
{
    /** NAL address */
    uint8_t *pu8Addr;

    /** NAL length */
    uint32_t u32Length;

    /** NAL type */
    API_VENC_NAL_UNIT_TYPE_E eNalType;
} API_VENC_NAL_T;


/*!
  *@brief The \b API_VENC_HEVC_CODED_PICT_T structure represents a coded picture.
  *
  * \b API_VENC_HEVC_CODED_PICT_T struct describes a block of ES representing the result
  * of an encoded frame.
  *
  * The ES may contain the VCL NALs and Non-VCL NALs.
  *
  * NALs contained within the ES can be fetched by looping through the \b tNalInfo[] array.
  *
    Member     | Description
    ---------- | --------------------------------------------------------------------------
    eFrameType | Frame coding type of this ES block
    pts        | Presentation time stamp associated with this ES block
    dts        | Decoding time stamp associated with this ES block
    u64ItcBase | Internal Time Clock value Unit: 90kHz
    u32ItcExt  | Internal Time Clock value (extension) Unit: 27MHz
    u32Tid     | Temporal ID
    eTimeBase  | PTS and DTS unit
    u32CpbBoc  | Occupancy value of CPB buffer
    u32NalNum  | Number of NAL in this ES block
    bLastES    | Indicates if this ES the last ES since VEGA330X_ENC_Start, VEGA330X_ENC_Stop can be called only if last ES is poped out, which also means encoder is fully flushed
    tNalInfo   | Contains all NALs information within this ES block
  *
  */
typedef struct
{
    /** Frame coding type of this ES block. */
    API_VENC_FRAME_TYPE_E    eFrameType;

    /** Picture structure of this ES block. */
    API_VENC_PICTURE_STRUCT_E ePictureStruct;

    /** Presentation time stamp associated with this ES block. */
    uint64_t                pts;

    /** Decoding time stamp associated with this ES block. */
    int64_t                 dts;

    /** Internal Time Clock value. Unit: 90kHz. */
    uint64_t                u64ItcBase;

    /** Internal Time Clock value (extension). Unit: 27MHz */
    uint32_t                u32ItcExt;

    /** Temporal ID */
    uint32_t                u32Tid;

    /** PTS and DTS unit */
    API_VENC_TIMEBASE_E eTimeBase;

    /** Occupancy value of CPB buffer */
    uint32_t                u32CpbBoc;

    /** Number of NAL in this ES block */
    uint32_t                u32NalNum;

    /**
    Indicates if this ES the last ES since VEGA330X_ENC_Start

    VEGA330X_ENC_Stop can be called only if last ES is poped out,
    which also means encoder is fully flushed.
    */
    bool                    bLastES;

    /** Contains all NALs information within this ES block. */
    API_VENC_NAL_T           tNalInfo[API_MAX_NAL_NUM];
} API_VENC_HEVC_CODED_PICT_T;


/*!
  *@brief The \b API_VENC_PICT_INFO_T structure represents user data information to associate with particular picture.
  *
  * \b API_VENC_PICT_INFO_T struct describes an array of SEIS for encoder to associate the 
  * corresponding ES.
  *
  *
  *
    Member              | Description
    ------------------- | --------------------------------------------------------------------------
    u32PictureNumber    | Which picture information associated with
    u32SeiNum           | Number of SEI descriptor associated with the picture
    tSeiParam           | SEI descriptor associated with, to provide user data
  *
  */
typedef struct
{
    /** Where picture information associated with */
    uint32_t                u32PictureNumber;

    /** Number of SEI descriptor associated with the picture */
    uint32_t                u32SeiNum;

    /** SEI descriptor associated with input image, to provide user data */
    API_VENC_SEI_PARAM_T     tSeiParam[API_MAX_SEI_NUM];

} API_VENC_PICT_INFO_T;


/*!
  *@brief The \b API_VENC_PICT_INFO_CALLBACK_PARAM_T structure represents information when a video image is captured.
  *
  * \b API_VENC_PICT_INFO_CALLBACK_PARAM_T struct describes information when a video image is captured.
  * User can utilize this information to provide appropriate user data information, API_VENC_PICT_INFO_T
  * to associate with a particular encoded frame.
  *
  *
    Member              | Description
    ------------------- | --------------------------------------------------------------------------
    eBoard              | board ID
    eCh                 | channel ID
    u32CaptureCounter   | Captured image number
  *
  */

typedef struct
{
    API_VENC_BOARD_E eBoard;
    API_VENC_CHN_E   eCh;
    uint32_t        u32CaptureCounter;
} API_VENC_PICT_INFO_CALLBACK_PARAM_T;


/**
@brief Callback function of VEGA330X_ENC_RegisterCallback
*/
typedef void (*API_VENC_CALLBACK)(API_VENC_HEVC_CODED_PICT_T *pPic, void *args);


/**
@brief Callback function of VEGA330X_ENC_RegisterPictureInfoCallback
*/
typedef void (*API_VENC_PICT_INFO_CALLBACK)(API_VENC_PICT_INFO_T *pPicInfo, const API_VENC_PICT_INFO_CALLBACK_PARAM_T *args);


typedef void (*API_VENC_VIDEO_CAPTURE_START_CALLBACK)(const int capture_counter, void *args);

#ifdef  __cplusplus
}
#endif

#endif


