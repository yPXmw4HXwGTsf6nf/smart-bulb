/**
 * @file credentials.h
 * @brief Wi‑Fi credential definitions for the Smart‑Bulb application.
 *
 * @note Hard‑coding secrets in source control is convenient during
 *       development but is discouraged for production. Prefer loading
 *       credentials from an encrypted NVS partition or supplying them
 *       at build time, e.g.:
 *
 *           idf.py build -DWIFI_SSID="MySSID" -DWIFI_PASSWORD="S3cr3t!"
 *
 *       The macros below are wrapped with `#ifndef` guards, allowing them
 *       to be overridden by compiler flags or an earlier include path.
 */
#pragma once

#ifndef WIFI_SSID
#define WIFI_SSID     "your-ssid"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "your-pass"
#endif