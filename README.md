streaming_diffusion
===

- [Introduction](#introduction)
- [ConversionMP3-WAV](#conversionmp3-wav)
- [DefinitionRDF](#definitionrdf)
- [MetadonneesWAV](#metadonneeswav)

## Introduction

L'objectif du projet est de créer un service permettant d'**écouter en diffusion progressive des fichiers musicaux**. Le client pourra choisir ces morceaux grâce à moteur de recherche qui indexera les métadonnées contenues dans les fichiers musicaux.

Nous récupérons quelques musiques libre de droit sur le site [musicscreen](http://www.musicscreen.be).

Nous utiliseront le langage **Python** afin de réaliser le projet.

## ConversionMP3-WAV

Nous avons récupérer 3 fichiers musicaux dans la catégorie Piano: 

	- Luiz

	- Hilouine

	- GypsyPno 

Pour les convertir en WAV nous avons utilisés un site en ligne : [audio.online-convert](http://audio.online-convert.com/fr/convertir-en-wav).

Nous avons regroupé les musiques dans le dossier **web/uploads**.

Un fichier **WAV** se compose d’un entête qui contient pas mal de meta données. Cet entête a été optimisé pour prendre peu de place.

## DefinitionRDF

Nous avons définit les **données importantes** pour les musiques : 
	
	- Title

	- Description

	- Time

	- Tags

Pour réaliser les méta-données RDF, on a préféré le construire en **N3** et le **convertir en RDF** et ensuite le visualiser par un validateur RDF.

Le fichier RDF est : base_audio.rdfs

Le fichier N3 est : base.n3

Adresse : 
	
- Conversion : [RDF-Translator](http://rdf-translator.appspot.com/)

- Validateur : [W3](http://www.w3.org/RDF/Validator/)

On peut observer les différents noeuds RDF sur le site W3 en choisissant l'option **Graph** 

## MetadonneesWAV

Nous allons maintenant travailler sur les méta-données en format RDF pour chaque fichier son et les insérer dans les fichiers WAV correspondant.
On utilisera la bibliothèque [Python_XMP_Toolkit](https://code.google.com/p/python-xmp-toolkit/) pour ajouter au format XMP les méta-données dans les fichier WAV.

Nous avons mit les schemas RDF de chaque musique dans le dossier **Description**.

Nous avons automatisé l'ajout des meta données :

```
fileListWAV=os.listdir("./uploads/");
for f in fileListWAV :
	name=f.split('.', 1 )[0];
	# Read file
	xmpfile = XMPFiles( file_path="./uploads/"+name+".wav", open_forupdate=True );
	# Get XMP from file.
	xmp = xmpfile.get_xmp();
	# Create Meta donnees
	meta = libxmp.XMPMeta();
	fic = open('./Description/'+name+'.rdf');
	meta.parse_from_str(fic.read(), xmpmeta_wrap=False, input_encoding=None);
	print 'file could be updated = ', xmpfile.can_put_xmp(meta);
	xmpfile.put_xmp(meta);
	xmpfile.close_file(close_flags=1);
```

- On récupère dans une liste tout les fichiers du dossier **uploads/**.

- On parse le fichier pour récupérer que le nom.

- On lit le fichier.

- On récupère les meta données.

- On créait notre méta données en prenant le fichier description RDF associé.

(le fichier WAV et le fichier RDF doit être du même nom ).

- On l'enregistre dans le fichier WAV puis on ferme le fichier.


Afin de récupérer les métadonnées contenues dans le fichier wav précédemment insérée on a également utilisé la bibliothèque [Python_XMP_Toolkit](https://code.google.com/p/python-xmp-toolkit/).

'''
print sys.argv[1];
xmpfile = XMPFiles( file_path="./uploads/"+sys.argv[1], open_forupdate=False )

xmp = xmpfile.get_xmp();
print xmp.get_localized_text( libxmp.consts.XMP_NS_DC, 'title', 'fr', 'fr-FR');

count = xmp.count_array_items( libxmp.consts.XMP_NS_DC, 'subject');
for i in range(1, count+1):
	print xmp.get_array_item( libxmp.consts.XMP_NS_DC, 'subject', i).keys()[0];
'''

## Upload



