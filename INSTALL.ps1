#!/usr/bin/env pwsh

foreach ($each in 'u8g2') {
  arduino-cli lib install u8g2
}
