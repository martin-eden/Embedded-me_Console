#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_String

# Uninstall dependencies
arduino-cli lib uninstall \
  me_String \
  me_MemorySegment \
  me_InstallStandardStreams \
  me_UartSpeeds \
  me_BaseTypes
