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

Nous avons regroupé les musiques dans le dossier **Audio**.

Un fichier **WAV** se compose d’un entête qui contient pas mal de meta données. Cet entête a été optimisé pour prendre peu de place.

## DefinitionRDF

Nous avons définit les **données importantes** pour les musiques : 
	
	- Title

	- Description

	- Time

	- Tags

Pour réaliser les méta-données RDF, on a préféré le construire en **N3** et le **convertir en RDFS** et ensuite le visualiser par un validateur RDF.

Le fichier RDF est : base_audio.rdfs

Le fichier N3 est : base.n3

Adresse : 
	
- Conversion : [RDF-Translator](http://rdf-translator.appspot.com/)

- Validateur : [W3](http://www.w3.org/RDF/Validator/)

On peut observer les différents noeuds RDF sur le site W3 en choisissant l'option **Graph** 

## MetadonneesWAV

Nous allons maintenant travailler sur les méta-données en format RDF pour chaque fichier son et les insérer dans les fichiers WAV correspondant.
On utilisera la bibliothèque [Python_XMP_Toolkit](https://code.google.com/p/python-xmp-toolkit/) pour ajouter au format XMP les méta-données dans les fichier WAV.

Nous avons mit les schemas RDF de chaque musique dans le dossier **Description**

Nous avons automatisé l'ajout

