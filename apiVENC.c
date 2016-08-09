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
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
     
#include <sys/stat.h>
#include <sys/utsname.h>
#include <sys/eventfd.h>
#include <sys/timerfd.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#include <libvega_encoder_api/VEGA330X_types.h>
#include <libvega_encoder_api/VEGA330X_encoder.h>

#include "apiVENC_types.h"
#include "apiVENC.h"

/**
@brief Print the version information of VEGA 330X.

The \b Api_VENC_PrintVersion function prints out the version information of the VEGA 330X device.

@param eBoard board number
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_PrintVersion(API_VENC_BOARD_E eBoard)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_PrintVersion((API_VEGA330X_BOARD_E) eBoard);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_RET_E) VEGA331X_ENC_PrintVersion((API_VEGA330X_BOARD_E) eBoard);
#endif
}

/**
@brief Enumerate VEGA 330X device.

The \b Api_VENC_Enum function enumerates the VEGA 330X device and its bus information.

@param p_enum_info pointer of API_VENC_ENUM_INFO_T
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_Enum(API_VENC_ENUM_INFO_T *p_enum_info)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_Enum((API_VEGA330X_ENUM_INFO_T *) p_enum_info);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_RET_E) VEGA331X_ENC_Enum((API_VEGA330X_ENUM_INFO_T *) p_enum_info);
#endif
}

/**
@brief Dump VEGA 330X register values.

The \b Api_VENC_Dump function reads VEGA 330X register values and saves them as bin files.

@param eBoard board number
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_Dump(API_VENC_BOARD_E eBoard)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_Dump((API_VEGA330X_BOARD_E) eBoard);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_RET_E) VEGA331X_ENC_Dump((API_VEGA330X_BOARD_E) eBoard);
#endif
}

/**
@brief Initialize a VEGA 330X channel.

The \b Api_VENC_Init function initializes a VEGA 330X channel.

Caller of Api_VENC_Init should provide input image format (default is NV12), and output bitstream parameters in a API_VENC_INIT_PARAM_T struct.

Channel state changes from OFF to STANDBY.

@param eBoard board number
@param eCh channel number
@param pApiInitParam pointer of API_VENC_INIT_PARAM_T type
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E
Api_VENC_Init
(
        API_VENC_BOARD_E       eBoard,
        API_VENC_CHN_E         eCh,
  const API_VENC_INIT_PARAM_T *pApiInitParam
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_Init
            (
                (API_VEGA330X_BOARD_E) eBoard,
                (API_VEGA330X_CHN_E) eCh,
                (const API_VEGA330X_INIT_PARAM_T *) pApiInitParam
            );
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_Init
            (
                (API_VEGA330X_BOARD_E) eBoard,
                (API_VEGA330X_CHN_E) eCh,
                (const API_VEGA330X_INIT_PARAM_T *) pApiInitParam
            );
#endif
}

/**
@brief Turns off a channel of VEGA 330X.

The \b Api_VENC_Exit function turns off an encoding channel and cleans up variables. Channel state changes from STANDBY to OFF.

Before calling this function, use \b Api_VENC_GetStatus to check if channel state is in API_VENC_STATUS_STANDBY.

Api_VENC_Exit can be used after \b Api_VENC_Stop function successfully returns.

Channel state changes from STANDBY to OFF.

@param eBoard board number
@param eCh channel number
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E
Api_VENC_Exit
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E eCh
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_Exit((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_RET_E) VEGA331X_ENC_Exit((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#endif
}

/**
@brief Reset VEGA 330X main status.

The \b Api_VENC_Reset function resets driver to initial state. All channel state change to OFF.

@param eBoard board number
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_Reset(API_VENC_BOARD_E eBoard)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_Reset((API_VEGA330X_BOARD_E) eBoard);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_RET_E) VEGA331X_ENC_Reset((API_VEGA330X_BOARD_E) eBoard);
#endif
}

/**
@brief Start a channel encoding process.

The \b Api_VENC_Start function sets the channel to get ready for encoding. Channel state changes from STANDBY to ENCODING.

Before calling this function, use \b Api_VENC_Init to set encoder parameters (only for first time).

@param eBoard board number
@param eCh channel number
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E
Api_VENC_Start
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E eCh
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_Start((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_RET_E) VEGA331X_ENC_Start((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#endif
}

/**
@brief One-shot starting multiple channel encoding processes.

The \b Api_VENC_MultiStart function sets multiple channels to get ready for encoding. Channel state changes from STANDBY to ENCODING.

Before calling this function, use \b Api_VENC_Init to set encoder parameters (only for first time).

This function is used for 1:N encoding. All channels receives input source from first channel placed in eChs array.

@param eBoard board number
@param eChs array of channels
@param u32NumberOfChannels number of channels in array
@return
- API_VEGA330X_RET_SUCCESS: Successful
- API_VEGA330X_RET_FAIL: Failed
*/

API_VENC_RET_E
Api_VENC_MultiStart
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E eChs[],
    uint32_t xyz
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_MultiStart((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E *) eChs, xyz);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    //return (API_VENC_RET_E) VEGA331X_ENC_MultiStart((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E *) eChs, xyz);
#endif
}


/**
@brief Stop a channel encoding on VEGA 330X.

The \b Api_VENC_Stop function stops a channel to encode any further frame. Channel state changes from ENCODING to STANDBY, after all input frames are encoded.

Before calling this function, an image, API_VENC_IMG_T struct with bLastFrame=true must be pushed into encoder.

Before calling this function, you can use \b Api_VENC_GetStatus to check if channel state is in API_VENC_STATUS_ENCODING.

The registered callback thread is terminated after Api_VENC_Stop suscessfully returns, and all queued ES will be flushed out from encoder.

The caller must make sure function return API_VENC_RET_SUCCESS before taking any further actions.

Channel state changes from ENCODING to STANDBY.

@param eBoard board number
@param eCh channel number
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
- API_VENC_RET_NO_LAST_FRAME: API_VENC_IMG_T with bLastFrame=true not pushed yet
*/
API_VENC_RET_E
Api_VENC_Stop
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E eCh
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_Stop((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_RET_E) VEGA331X_ENC_Stop((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#endif
}

API_VENC_RET_E
Api_VENC_MultiStop
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E eChs[],
    uint32_t    u32NumberOfChannels
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_MultiStop((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E *) eChs, u32NumberOfChannels);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    //return (API_VENC_RET_E) VEGA331X_ENC_MultiStop((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E *) eChs, u32NumberOfChannels);
#endif
}


/**
@brief Stop a channel encoding on VEGA 330X.

The \b Api_VENC_BlockingStop function stops a channel to encode any further frame. Channel state
changes from ENCODING to STANDBY, after all input frames are encoded.

Before calling this function, you can use \b Api_VENC_GetStatus to check if channel state
is in API_VENC_STATUS_ENCODING.

User does not require to push image with bLastFrame=true.

The registered callback thread is terminated after Api_VENC_BlockingStop suscessfully
returns, and all queued ES will be flushed out from encoder.

Api_VENC_BlockingStop is blocked until last ES poped out. If you care about
responsiveness, use non-blocking Api_VENC_Stop instead.

@param eBoard board number
@param eCh channel number
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E
Api_VENC_BlockingStop
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E eCh
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_BlockingStop((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_RET_E) VEGA331X_ENC_BlockingStop((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#endif
}


/**
@brief Send one YUV raw frame to encoder.

The \b Api_VENC_PushImage function sends one YUV raw frame to device.

Caller of Api_VENC_PushImage should prepare a API_VENC_IMT_T struct, which describes the raw frame address, size, pixel format, whether last frame or not.

The Api_VENC_PushImage function buffers raw frame pixels inside API, therefore caller is free to reclaim its raw frame buffer after Api_VENC_PushImage returns.

Setting of last frame flag in API_VENC_IMG_T is important; without last frame flag be set properly, stop encoder is impossible.

Before calling this function, the state must be in ENCODING state, i.e: after calling Api_VENC_Start .

The Api_VENC_PushImage function only works in \b API_VENC_INPUT_MODE_DATA mode.

@param eBoard board number
@param eCh channel number
@param pImg pointer of API_VENC_IMG_T type, which contains raw frame info.
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
- API_VENC_RET_NO_MEM: Can't allocate memory for image transform
*/
API_VENC_RET_E
Api_VENC_PushImage
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E   eCh,
    API_VENC_IMG_T  *pImg
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_PushImage((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, (API_VEGA330X_IMG_T *) pImg);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_RET_E) VEGA331X_ENC_PushImage((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, (API_VEGA330X_IMG_T *) pImg);
#endif
}

/**
@brief Pop one coded frame from device.

The \b Api_VENC_PopES function pops out an coded frame, API_VENC_HEVC_CODED_PICT_T.

@param eBoard board number
@param eCh channel number
@param pPic ES output
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E
Api_VENC_PopES
(
    API_VENC_BOARD_E             eBoard,
    API_VENC_CHN_E               eCh,
    API_VENC_HEVC_CODED_PICT_T  *pPic
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_PopES((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, (API_VEGA330X_HEVC_CODED_PICT_T *) pPic);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_RET_E) VEGA331X_ENC_PopES((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, (API_VEGA330X_HEVC_CODED_PICT_T *) pPic);
#endif
}

/**
@brief Register callback function for handling ES data.

The \b Api_VENC_RegisterCallback function installs a callback to be called when an encoded frame is available.

The registered callback is called when an encoded frame, API_VENC_HEVC_CODED_PICT_T is available.

The passed API_VENC_HEVC_CODED_PICT_T struct describes coded picture frame type, PTS, DTS, and NALs information composing the frame.

API stores frame ES inside internal buffer; once callback returns, internal buffer for storing ES data is reclaimed. Caller must buffer ES during callback execution.

@param eBoard board number
@param eCh channel number
@param callback pointer to function to be registered
@param args TBA
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E
Api_VENC_RegisterCallback
(
    API_VENC_BOARD_E  eBoard,
    API_VENC_CHN_E    eCh,
    API_VENC_CALLBACK callback,
    void             *args
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_RegisterCallback((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, (API_VEGA330X_CALLBACK) callback, args);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_RET_E) VEGA331X_ENC_RegisterCallback((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, (API_VEGA330X_CALLBACK) callback, args);
#endif
}

/**
@brief Register callback function for user to provide picture information data(SEI).

@param eBoard board number
@param eCh channel number
@param callback pointer to function to be registered
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E
Api_VENC_RegisterPictureInfoCallback
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E eCh,
    API_VENC_PICT_INFO_CALLBACK callback
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_RegisterPictureInfoCallback
            (
                (API_VEGA330X_BOARD_E) eBoard,
                (API_VEGA330X_CHN_E) eCh,
                (API_VEGA330X_PICT_INFO_CALLBACK) callback
            );
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_RegisterPictureInfoCallback
            (
                (API_VEGA330X_BOARD_E) eBoard,
                (API_VEGA330X_CHN_E) eCh,
                (API_VEGA330X_PICT_INFO_CALLBACK) callback
            );
#endif
}

/**
@brief Register callback function.

@param eBoard board number
@param eCh channel number
@param callback pointer to function to be registered
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E
Api_VENC_RegisterVideoCaptureStartCallback
(
    API_VENC_BOARD_E                        eBoard,
    API_VENC_CHN_E                          eCh,
    API_VENC_VIDEO_CAPTURE_START_CALLBACK   callback,
    void                                   *args
)
{    
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_RegisterVideoCaptureStartCallback
            (
                (API_VEGA330X_BOARD_E) eBoard,
                (API_VEGA330X_CHN_E) eCh,
                (API_VEGA330X_VIDEO_CAPTURE_START_CALLBACK) callback,
                args
            );
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_RegisterVideoCaptureStartCallback
            (
                (API_VEGA330X_BOARD_E) eBoard,
                (API_VEGA330X_CHN_E) eCh,
                (API_VEGA330X_VIDEO_CAPTURE_START_CALLBACK) callback,
                args
            );
#endif
}

/**
@brief Report number of encoded frames.

The \b Api_VENC_GetEncodedFrameNumbers function provides number of encoded frame for specific channel since most recent Api_VENC_Init.

@param eBoard board number
@param eCh channel number.
@return An unsigned integer to represent number of encoded frame.
*/
uint32_t
Api_VENC_GetEncodedFrameNumbers
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E   eCh
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_GetEncodedFrameNumbers((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_GetEncodedFrameNumbers((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#endif
}

/**
@brief Set debug message level.

The \b Api_VENC_SetDbgMsgLevel function sets debug message level.

@param eDbgLevel new debug message level
*/
void Api_VENC_SetDbgMsgLevel(const API_VENC_DBG_LEVEL_E eDbgLevel)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    VEGA330X_ENC_SetDbgMsgLevel((const API_VEGA330X_DBG_LEVEL_E) eDbgLevel);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    VEGA331X_ENC_SetDbgMsgLevel((const API_VEGA330X_DBG_LEVEL_E) eDbgLevel);
#endif
}

/**
@brief Report current status of device.

The \b Api_VENC_GetStatus function provides current status of encoder. This function is aimed to help what user program can
do with current encoder state.

The user shall use this function to get current state of encoder before next action; non
sensible function call made in inappropriate manner is rejected immediately.

@param eBoard board number
@param eCh channel number.
@return Current encoder status.
*/
API_VENC_STATUS_E Api_VENC_GetStatus
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E   eCh
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_STATUS_E) VEGA330X_ENC_GetStatus((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_STATUS_E) VEGA331X_ENC_GetStatus((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#endif
}

/**
@brief Report bitrate setting.

The \b Api_VENC_GetBitrate function provides current bitrate setting of encoder.

@param eBoard board number
@param eCh channel number
@return Encoder bitrate setting.
*/
uint32_t Api_VENC_GetBitrate
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E   eCh
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_GetBitrate((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_GetBitrate((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#endif
}

/**
@brief Set new bitrate for channel.

The \b Api_VENC_SetBitrate function sets a new bitrate (in kbps) for a channel on encoder.

New bitrate should be smaller or equal to API_MAX_BITRATE.

@param eBoard board number
@param eCh channel number.
@param u32Bitrate new bitrate value in kbps. 0 < u32Bitrate <= API_MAX_BITRATE.
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_SetBitrate
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E   eCh,
    uint32_t        u32Bitrate
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return (API_VENC_RET_E) VEGA330X_ENC_SetBitrate((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, u32Bitrate);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return (API_VENC_RET_E) VEGA331X_ENC_SetBitrate((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, u32Bitrate);
#endif
}

/**
@brief Set new variable bitrate for channel.

The \b Api_VENC_SetVBR function sets a new variable bitrate (in kbps) for a channel on encoder.

@param eBoard board number
@param eCh channel number.
@param u32MaxBitrate new max bitrate value in kbps.
@param u32AveBitrate new average bitrate value in kbps.
@param u32MinBitrate new min bitrate value in kbps.
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_SetVBR
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E   eCh,
    uint32_t        u32MaxBitrate,
    uint32_t        u32AveBitrate,
    uint32_t        u32MinBitrate
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_SetVBR
            (
                (API_VEGA330X_BOARD_E) eBoard,
                (API_VEGA330X_CHN_E) eCh,
                u32MaxBitrate,
                u32AveBitrate,
                u32MinBitrate
            );
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_SetVBR
            (
                (API_VEGA330X_BOARD_E) eBoard,
                (API_VEGA330X_CHN_E) eCh,
                u32MaxBitrate,
                u32AveBitrate,
                u32MinBitrate
            );
#endif
}

/**
@brief Request an immediate IDR for channel.

The \b Api_VENC_ForceIDR requests encoder to generate an IDR as soon as possible.

@param eBoard board number
@param eCh channel number
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_ForceIDR
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E   eCh
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_ForceIDR((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_ForceIDR((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#endif
}

/**
@brief Request encoder to encode a specific frame as an IDR.

The \b Api_VENC_ForceIDRAt requests encoder to generate an IDR for frame u32PicNum.
u32PicNum starts from 0, so Api_VENC_ForceIDRAt u32PicNum gives you an IDR with POC 99.

If encoder has already decided picture type for frame number u32PicNum, 
an IDR will be generated as closest to the targeted frame as possible.

@param eBoard       board number
@param eCh          channel number
@param u32PicNum    targeted frame to be the IDR
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_ForceIDRAt
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E   eCh,
    uint32_t         u32PicNum
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_ForceIDRAt((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, u32PicNum);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_ForceIDRAt((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, u32PicNum);
#endif
}


/**
@brief Report current frame rate setting.

The \b Api_VENC_GetFramerate function provides the current encoder frame rate setting.

The frame rate of encoder is set during Api_VENC_Init process, or set independently
by using Api_VENC_SetFramerate.

The return value is an enum, API_VENC_FPS_E. API_VENC_FPS_E enumerates supported frame rate.

The definition of API_VENC_FPS_E is in following table:

                        num_uints_in_tick       time_scale

    API_VENC_FPS_23_98   24000                   1001
    API_VENC_FPS_24      24                      1
    API_VENC_FPS_25      25                      1
    API_VENC_FPS_29_97   30000                   1001
    API_VENC_FPS_30      30                      1
    API_VENC_FPS_50      50                      1
    API_VENC_FPS_59_94   60000                   1001
    API_VENC_FPS_60      60                      1

@param eBoard board number
@param eCh channel number
@return Encoder frame rate setting.
*/
API_VENC_FPS_E Api_VENC_GetFramerate
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E   eCh
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_GetFramerate((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_GetFramerate((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#endif
}

/**
@brief Set new frame rate of device.

The \b Api_VENC_SetBitrate function sets a new frame rate of encoder.

Before calling this function, use \b Api_VENC_Stop to flush all queued ES.

@param eBoard board number
@param eCh channel number.
@param eFps New frame rate value.
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_SetFramerate
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E   eCh,
    API_VENC_FPS_E   eFps
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_SetFramerate((API_VEGA330X_BOARD_E) eBoard,(API_VEGA330X_CHN_E) eCh,(API_VEGA330X_FPS_E) eFps);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_SetFramerate((API_VEGA330X_BOARD_E) eBoard,(API_VEGA330X_CHN_E) eCh,(API_VEGA330X_FPS_E) eFps);
#endif
}

/**
@brief Report current memory allocation setting.

The \b Api_VENC_GetMemoryAllocMode function provides the current encoder memory allocation setting.

The memory allocation mode of encoder is initialized during Api_VENC_Init process and only set by the channel that first started.

The return value is an enum, API_VENC_MEMORY_ALLOC_MODE_E. API_VENC_MEMORY_ALLOC_MODE_E enumerates supported memory allocation mode.

 * \enum API_VENC_MEMORY_ALLOC_MODE_E
 * \b API_VENC_MEMORY_ALLOC_MODE_E enumerates the memory allocation mode for M31 device.
 *
    Enum                                        Description

    API_VENC_MEMORY_ALLOC_MODE_1CH_4K2K          Specify the memory allocation mode is 4K2K. The maximum resolution is 4K2K and the maximum number of channels is 1.
    API_VENC_MEMORY_ALLOC_MODE_4CH_1080P         Specify the memory allocation mode is 1080P. The maximum resolution is 1080P and the maximum number of channels is 4.
    API_VENC_MEMORY_ALLOC_MODE_8CH_720P          Specify the memory allocation mode is 720P. The maximum resolution is 720P and the maximum number of channels is 8.
    API_VENC_MEMORY_ALLOC_MODE_8CH_MIXING        Specify the memory allocation mode is MIXING. The maximum resolution is 1080P and the maximum number of channels is 8.
    API_VENC_MEMORY_ALLOC_MODE_16CH_SD           Specify the memory allocation mode is SD. The maximum resolution is SD and the maximum number of channels is 16.
    API_VENC_MEMORY_ALLOC_MODE_16CH_SEQUENCE     Specify the memory allocation mode is SEQUENCE. The maximum resolutions are ordered in a sequence from large to small(CH0~CH3:1080P,CH4~CH7:720P,CH8~CH15:SD). The maximum number of channels is 16.
    API_VENC_MEMORY_ALLOC_MODE_16CH_720P_MIXING  Specify the memory allocation mode is 720P_MIXING. The maximum resolution is 720P and the maximum number of channels is 16.
    API_VENC_MEMORY_ALLOC_MODE_INVALID           There is no channel in encode status. The memory allocation mode is not set.

@param eBoard board number
@param eCh channel number
@return Encoder memory allocation setting.

*/
API_VENC_MEMORY_ALLOC_MODE_E Api_VENC_GetMemoryAllocMode
(
    API_VENC_BOARD_E      eBoard,
    API_VENC_CHN_E        eCh
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_GetMemoryAllocMode((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_GetMemoryAllocMode((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh);
#endif
}

/**
@brief Report current resolution and interlace settings.

The \b Api_VENC_GetResolution function provides the current encoder resolution and interlace settings.

These parameters of encoder are set during Api_VENC_Init process.

The definition of API_VENC_RESOLUTION_E is in following table:

    Enum                          Width   Height

    API_VENC_RESOLUTION_352x288    352     288
    API_VENC_RESOLUTION_416x240    416     240
    API_VENC_RESOLUTION_720x480    720     480
    API_VENC_RESOLUTION_720x576    720     576
    API_VENC_RESOLUTION_1280x720   1280    720
    API_VENC_RESOLUTION_1920x1080  1920    1080
    API_VENC_RESOLUTION_2048x1080  2048    1080
    API_VENC_RESOLUTION_3840x2160  3840    2160
    API_VENC_RESOLUTION_4096x2160  4096    2160
    API_VENC_RESOLUTION_INVALID    0       0

@param eBoard board number
@param eCh channel number
@param pResolution pointer of API_VENC_RESOLUTION_E type
@param pInterlace pointer of bool type, which indicate whether the scan mode is interlace or not. (0=progressive, 1=interlace)

@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed

*/
API_VENC_RET_E Api_VENC_GetResolution
(
    API_VENC_BOARD_E        eBoard,
    API_VENC_CHN_E          eCh,
    API_VENC_RESOLUTION_E  *pResolution,
    bool                   *pInterlace
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_GetResolution((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, (API_VEGA330X_RESOLUTION_E *) pResolution, pInterlace);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_GetResolution((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, (API_VEGA330X_RESOLUTION_E *) pResolution, pInterlace);
#endif
}

/**
@brief Report current bitrate.

The \b Api_VENC_GetCurrentBitrate function provides realtime bitrate of the encoder.

Current bitrate is computed by summing frame bytes during last second.

@param eBoard board number.
@param eCh channel number.
@return Number of bits(kbps) generated by encoder during last second.
*/
uint32_t Api_VENC_GetCurrentBitrate
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E   eCh
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_GetCurrentBitrate((API_VEGA330X_BOARD_E) eBoard,(API_VEGA330X_CHN_E) eCh);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_GetCurrentBitrate((API_VEGA330X_BOARD_E) eBoard,(API_VEGA330X_CHN_E) eCh);
#endif
}

/**
@brief Report version information.

The \b Api_VENC_GetVersion function provides version information of encoder system,
including API, firmware and OS.

@param eBoard board number
@param pVersion version information
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_GetVersion
(
    API_VENC_BOARD_E eBoard,
    API_VENC_VERSION_INFO_T *pVersion
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_GetVersion((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_VERSION_INFO_T *) pVersion);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_GetVersion((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_VERSION_INFO_T *) pVersion);
#endif
}

/**
@brief Report VEGA 330X EHParam register values.

The \b Api_VENC_GetEHParam function reads VEGA 330X EHParam register values.

@param eBoard board number
@param eCh    channel number
@param data   destination of register values to be saved
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_GetEHParam
(
    API_VENC_BOARD_E eBoard,
    API_VENC_CHN_E   eCh,
    uint8_t          data[]
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_GetEHParam((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, data);
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_GetEHParam((API_VEGA330X_BOARD_E) eBoard, (API_VEGA330X_CHN_E) eCh, data);
#endif
}

/**
@brief Creates a API_VENC_INIT_PARAM_T structure.

The \b Api_VENC_MakeInitParam function helps user to create a VEGA330X init parameter, which can be used to initialize the VEGA330X encoder.

@param pApiInitParam    pointer to init parameter to be set; provided by caller.
@param eProfile         profile value.
@param eLevel           level value
@param eTier            tier value.
@param eResolution      resolution value.
@param eChromaFmt       chroma format.
@param eBitDepth        bit depth.
@param eTargetFrameRate frame rate value.
@param u32Bitrate       bitrate value in kbps. 0 < u32Bitrate <= API_MAX_BITRATE.
@param u32CpbDelay      CPB delay value.
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_MakeInitParam
(
        API_VENC_INIT_PARAM_T      *pApiInitParam,
  const API_VENC_HEVC_PROFILE_E     eProfile,
  const API_VENC_HEVC_LEVEL_E       eLevel,
  const API_VENC_HEVC_TIER_E        eTier,
  const API_VENC_RESOLUTION_E       eResolution,
  const API_VENC_CHROMA_FORMAT_E    eChromaFmt,
  const API_VENC_BIT_DEPTH_E        eBitDepth,
  const API_VENC_FPS_E              eTargetFrameRate,
  const uint32_t                        u32Bitrate,
  const uint32_t                        u32CpbDelay
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_MakeInitParam
            (
                (API_VEGA330X_INIT_PARAM_T *) pApiInitParam,
                (const API_VEGA330X_HEVC_PROFILE_E) eProfile,
                (const API_VEGA330X_HEVC_LEVEL_E) eLevel,
                (const API_VEGA330X_HEVC_TIER_E) eTier,
                (const API_VEGA330X_RESOLUTION_E) eResolution,
                eChromaFmt,
                eBitDepth,
                eTargetFrameRate,
                u32Bitrate,
                u32CpbDelay
            );
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_MakeInitParam
            (
                (API_VEGA330X_INIT_PARAM_T *) pApiInitParam,
                (const API_VEGA330X_HEVC_PROFILE_E) eProfile,
                (const API_VEGA330X_HEVC_LEVEL_E) eLevel,
                (const API_VEGA330X_HEVC_TIER_E) eTier,
                (const API_VEGA330X_RESOLUTION_E) eResolution,
                eChromaFmt,
                eBitDepth,
                eTargetFrameRate,
                u32Bitrate,
                u32CpbDelay
            );

#endif
}

/**
@brief Creates a API_VENC_SEI_PARAM_T structure.

The \b Api_VENC_MakeSeiParam function helps user to create a VEGA 330X SEI parameter, which can be used to insert into specific video source frame.

@param pSeiParam        pointer to SEI parameter to be set; provided by caller.
@param ePayloadType     SEI payload type.
@param u8PayloadSize    SEI payload size.
@param u8Payload        SEI payload(data).
@return
- API_VENC_RET_SUCCESS: Successful
- API_VENC_RET_FAIL: Failed
*/
API_VENC_RET_E Api_VENC_MakeSeiParam
(
        API_VENC_SEI_PARAM_T       *pSeiParam,
  const API_VENC_SEI_PAYLOAD_TYPE_E ePayloadType,
  const uint8_t                     u8PayloadSize,
  const uint8_t                    *u8Payload
)
{
#if (API_CHIP_TYPE == API_CHIP_M31)
    return VEGA330X_ENC_MakeSeiParam
            (
                (API_VEGA330X_SEI_PARAM_T *) pSeiParam,
                (const API_VEGA330X_SEI_PAYLOAD_TYPE_E) ePayloadType,
                (const uint8_t) u8PayloadSize,
                (const uint8_t *) u8Payload
            );
#elif (API_CHIP_TYPE == API_CHIP_M30)
    return VEGA331X_ENC_MakeSeiParam
            (
                (API_VEGA330X_SEI_PARAM_T *) pSeiParam,
                (const API_VEGA330X_SEI_PAYLOAD_TYPE_E) ePayloadType,
                (const uint8_t) u8PayloadSize,
                (const uint8_t *) u8Payload
            );
#endif
}


