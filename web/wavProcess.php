<?php

function wavProcess($index, $doc, $documentName) {

	$fileName = explode('.',$documentName)[0];
	$fileNameField = \ZendSearch\Lucene\Document\Field::text(
		'filename',
		$fileName
	);
	
	//APPEL DU FICHIER PYTHON
	exec('python ./xmpParse.py '.$documentName,$res, $retcode);

	// Title	
	$title = $res[0];
	$titleField = \ZendSearch\Lucene\Document\Field::text(
		'title',
		$title
	);

	// echo "Title : " . $title[0] . PHP_EOL;

	// Subject
	for ($i = 1; $i < count($res); $i++) {
		$subject = $res[$i];
		$subjectField = \ZendSearch\Lucene\Document\Field::text(
			$subject,
			$subject
		);
		$doc->addField($subjectField);
	}

	// echo "Subject : " . $subject[0] . PHP_EOL;


	$doc->addField($fileNameField);
	$doc->addField($titleField);
	$index->addDocument($doc);
}
