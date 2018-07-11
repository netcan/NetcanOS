#!/usr/bin/env python
# encoding: utf-8

import os
import ycm_core

flags = [ '-Wall',
        '-Werror',
        '-m32',
        '-c',
        '-ffreestanding',
        '-Ikernel',
        '-Ilibc',
        '-Icpu',
        '-Idrivers',
        ]

SOURCE_EXTENSIONS = ['.c', '.asm']

def FlagsForFile( filename, **kwargs ):
  return {
    'flags': flags,
    'do_cache': True
  }
