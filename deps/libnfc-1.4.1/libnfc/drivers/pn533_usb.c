/*-
 * Public platform independent Near Field Communication (NFC) library
 * 
 * Copyright (C) 2009, Roel Verdult
 * 
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

/**
 * @file pn533_usb.c
 * @brief Driver for PN533 chip using USB
 */

/*
Thanks to d18c7db and Okko for example code
*/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif // HAVE_CONFIG_H

#include <stdlib.h>

#include "../drivers.h"
#include <nfc/nfc-messages.h>

nfc_device_desc_t *
pn533_usb_pick_device (void)
{
  nfc_device_desc_t *pndd;

  if ((pndd = malloc (sizeof (*pndd)))) {
    size_t  szN;

    if (!pn533_usb_list_devices (pndd, 1, &szN)) {
      DBG ("%s", "pn533_usb_list_devices failed");
      free (pndd);
      return NULL;
    }

    if (szN == 0) {
      DBG ("%s", "No device found");
      free (pndd);
      return NULL;
    }
  }

  return pndd;
}

bool
pn533_usb_list_devices (nfc_device_desc_t pnddDevices[], size_t szDevices, size_t * pszDeviceFound)
{
  // array of {vendor,product} pairs for USB devices
  usb_candidate_t candidates[] = { {0x04CC, 0x2533}
  , {0x04E6, 0x5591}
  };

  return pn53x_usb_list_devices (&pnddDevices[0], szDevices, pszDeviceFound, &candidates[0],
                                 sizeof (candidates) / sizeof (usb_candidate_t), PN533_USB_DRIVER_NAME);
}

nfc_device_t *
pn533_usb_connect (const nfc_device_desc_t * pndd)
{
  return pn53x_usb_connect (pndd, pndd->acDevice, NC_PN533);
}
