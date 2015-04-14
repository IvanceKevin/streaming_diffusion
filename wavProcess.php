<?php

function wavProcess($index, $doc, $documentPath) {

	$fileName = basename($documentPath);
	$fileNameField = \ZendSearch\Lucene\Document\Field::text(
		'filename',
		$fileName
	);
	
	//APPEL DU FICHIER PYTHON
	// echo $fileName . PHP_EOL ;

	$meta = '';
	$fp = fopen('zip://' . $documentPath . '#meta.xml', 'r');
	if (!$fp) {
	    exit("impossible d'ouvrir\n");
	}

	while (!feof($fp)) {
	    $meta .= fread($fp, 2);
	}

	$xml = new SimpleXMLElement($meta, LIBXML_XINCLUDE, false, 'office', true);

	$xml->registerXPathNamespace('meta', 'urn:oasis:names:tc:opendocument:xmlns:meta:1.0');
	$xml->registerXPathNamespace('dc', 'http://purl.org/dc/elements/1.1/');
	

	// Title	
	$title = $xml->xpath('//dc:title');
	$titleField = \ZendSearch\Lucene\Document\Field::text(
		'title',
		$title[0]
	);

	// echo "Title : " . $title[0] . PHP_EOL;

	// Subject
	$subject = $xml->xpath('//dc:subject');
	$subjectField = \ZendSearch\Lucene\Document\Field::text(
		'subject',
		$subect[0]
	);

	// echo "Subject : " . $subject[0] . PHP_EOL;
	
	// Creator
	$creator = $xml->xpath('//meta:initial-creator');
	$creatorField = \ZendSearch\Lucene\Document\Field::text(
		'creator',
		$creator[0]
	); 

	// echo "Creator : " . $creator[0] . PHP_EOL;

	// Keywords
	$Keywords = $xml->xpath('//meta:keyword');
	$KeywordsField = \ZendSearch\Lucene\Document\Field::text(
		'keywords',
		$Keywords[0]
	); 

	// echo "Keywords : " . $keywords[0] . PHP_EOL;

	// Description
	$description = $xml->xpath('//dc:description');
	$descriptionField = \ZendSearch\Lucene\Document\Field::text(
		'description',
		$description[0]
	); 

	// echo "Description : " . $description[0] . PHP_EOL;

	// LastModifiedBy
	$LastModifiedBy = $xml->xpath('//dc:creator');
	$LastModifiedByField = \ZendSearch\Lucene\Document\Field::text(
		'LastModifiedBy',
		$LastModifiedBy[0]
	); 

	// echo "LastModifiedBy : " . $LastModifiedBy[0] . PHP_EOL;

	// Version
	$version = $xml->xpath('//meta:editing-cycles');
	$versionField = \ZendSearch\Lucene\Document\Field::text(
		'version',
		$version[0]
	); 

	// echo "Version : " . $version[0] . PHP_EOL;

	// Modified
	$modified = $xml->xpath('//dc:date');
	$modifiedField = \ZendSearch\Lucene\Document\Field::text(
		'Modified',
		$modified[0]
	); 

	// echo "Modified : " . $modified[0] . PHP_EOL;

	// Created
	$created = $xml->xpath('//meta:creation-date');
	$createdField = \ZendSearch\Lucene\Document\Field::text(
		'Created',
		$created[0]
	); 

	// echo "Created : " . $created[0] . PHP_EOL;


	// Content
	
	$content = '';
	$fp = fopen('zip://' . $documentPath . '#content.xml', 'r');
	if (!$fp) {
	    exit("impossible d'ouvrir\n");
	}

	while (!feof($fp)) {
	    $content .= fread($fp, 2);
	}

	$xml = new SimpleXMLElement($content, LIBXML_NOBLANKS, false, 'office', true);

	$xml->registerXPathNamespace('text', 'urn:oasis:names:tc:opendocument:xmlns:text:1.0');

	// Body
	$bodyContent = '';

	$body = $xml->xpath('//text:h');
	foreach($body as $balise) {
		$bodyContent .= $balise[0];
	}

	$body = $xml->xpath('//text:p');
	foreach($body as $balise) {
		$bodyContent .= $balise[0];
	}

	$bodyField = \ZendSearch\Lucene\Document\Field::text(
		'body',
		$bodyContent
	); 

	// echo "Content : " .$bodyContent . PHP_EOL;

	$doc->addField($fileNameField);
	$doc->addField($titleField);
	$doc->addField($subjectField);
	$doc->addField($creatorField);
	$doc->addField($KeywordsField);
	$doc->addField($descriptionField);
	$doc->addField($LastModifiedByField);
	$doc->addField($versionField);
	$doc->addField($modifiedField);
	$doc->addField($createdField);
	$doc->addField($bodyField);

	$index->addDocument($doc);
}
