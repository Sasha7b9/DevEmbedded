/**
  ******************************************************************************
  * @file    USB_Device/HID_Standalone/Inc/usbd_desc.h
  * @author  MCD Application Team
  * @brief   Header for usbd_desc.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_DESC_H
#define __USBD_DESC_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define         DEVICE_ID1          (0x1FFFF7AC)
#define         DEVICE_ID2          (0x1FFFF7B0)
#define         DEVICE_ID3          (0x1FFFF7B4)

#define  USB_SIZ_STRING_SERIAL               0x1A
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern USBD_DescriptorsTypeDef HID_Desc;

#endif /* __USBD_DESC_H */



//
///* Exported types ------------------------------------------------------------*/
///* Exported constants --------------------------------------------------------*/
//#define         DEVICE_ID1          (0x1FFFF7AC)
//#define         DEVICE_ID2          (0x1FFFF7B0)
//#define         DEVICE_ID3          (0x1FFFF7B4)
//
//#define  USB_SIZ_STRING_SERIAL       0x1A
///* Exported macro ------------------------------------------------------------*/
///* Exported functions ------------------------------------------------------- */
//extern USBD_DescriptorsTypeDef HID_Desc;
//
//#endif /* __USBD_DESC_H */
// 
//
