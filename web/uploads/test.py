#!/usr/bin/python
# -*- coding: latin-1 -*-

__author__ = 'ivance kevin & briton paul'


from libxmp import *
from libxmp.core import XMPIterator, XMPMeta
from libxmp.consts import *
import libxmp
import os

	
# Read file
xmpfile = XMPFiles( file_path="./GypsyPno.wav", open_forupdate=True );

# Get XMP from file.
xmp = xmpfile.get_xmp();

print xmp;


