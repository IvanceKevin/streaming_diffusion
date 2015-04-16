#!/usr/bin/python
# -*- coding: latin-1 -*-

__author__ = 'ivance kevin & briton paul'

from libxmp import *
from libxmp.core import XMPIterator, XMPMeta
from libxmp.consts import *
import libxmp, sys

# Read file
print sys.argv[1];
#### TEST IF FILE EXIST ######
xmpfile = XMPFiles( file_path="./uploads/"+sys.argv[1], open_forupdate=False )

# Get XMP from file.
xmp = xmpfile.get_xmp();
print xmp.get_localized_text( libxmp.consts.XMP_NS_DC, 'title', 'fr', 'fr-FR');

count = xmp.count_array_items( libxmp.consts.XMP_NS_DC, 'subject');
for i in range(1, count+1):
	print xmp.get_array_item( libxmp.consts.XMP_NS_DC, 'subject', i).keys()[0];

