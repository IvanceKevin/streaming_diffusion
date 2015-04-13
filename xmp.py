from libxmp import *

# Read file
xmpfile = XMPFiles( file_path="/path/to/some/file", open_forupdate=True )

# Get XMP from file.
xmp = xmpfile.get_xmp()
