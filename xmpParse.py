#!/usr/bin/python
# -*- coding: latin-1 -*-

__author__ = 'ivance kevin & briton paul'

from libxmp import *
from libxmp.core import XMPIterator, XMPMeta
from libxmp.consts import *
import libxmp
# Read file
xmpfile = XMPFiles( file_path="./Audio/GypsyPno.wav", open_forupdate=True )

# Get XMP from file.
xmp = xmpfile.get_xmp()

# Create Meta donnees
#set localise text
#bag ( array item)
meta = libxmp.XMPMeta()

## Manque la durée et mettre à jour les tags

print 'alt2 = ',meta.set_localized_text(libxmp.consts.XMP_NS_DC, 'title','en-US','en-US','GypsyPno')
print 'alt1 = ',meta.set_localized_text(libxmp.consts.XMP_NS_DC, 'title','fr-FR','fr-FR','GypsyPno')
print 'alt2 = ',meta.set_localized_text(libxmp.consts.XMP_NS_DC, 'description','en-US','en-US','Royalty free music on the piano. Music with gypsy sounds , rhythmic tempo footprint to Balkan music, and giving a sense of celebration, joy. It will illustrate wonderfully festive scenes , night scenes , passion, lightness and joy.')
print 'alt1 = ',meta.set_localized_text(libxmp.consts.XMP_NS_DC, 'description','fr-FR','fr-FR','Musique libre de droit au piano. Musique avec des sonorités gypsy, un tempo rythmé empreinté aux musiques balkaniques, et donnant une impression de fête, de joie. Elle illustrera à merveille des scènes de fête, scènes nocturne, la passion, la légèreté et la joie de vivre.')
print 'bag1 = ',meta.append_array_item(libxmp.consts.XMP_NS_DC,'subject','pop',{'prop_value_is_array': libxmp.consts.XMP_PROP_VALUE_IS_ARRAY})
print 'bag2 = ',meta.append_array_item(libxmp.consts.XMP_NS_DC, 'subject','electro')

#print meta

print 'file could be updated = ', xmpfile.can_put_xmp(meta)

xmpfile.put_xmp(meta)
xmpfile.close_file(close_flags=1)

#Réouverture du fichier et extraction xmp meta-données

xmpfile = XMPFiles( file_path="./Audio/GypsyPno.wav", open_forupdate=True )
# Get XMP from file.
xmp = xmpfile.get_xmp()
#print xmp

fichierXMP = 'GypsyPno.xmp'
# création et ouverture du fichier test.txt en mode write 'w' (écriture)
# si le fichier test.txt existe déjà, il est écrasé
Fichier = open(fichierXMP,'w')      # instanciation de l'objet Fichier de la classe file

# écriture dans le fichier avec la méthode write()
Fichier.write(str(xmp))

# fermeture du fichier avec la méthode close()
Fichier.close()


