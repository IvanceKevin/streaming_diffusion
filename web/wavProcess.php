<?php

function wavProcess($index, $doc, $documentPath) {

	$fileName = basename($documentPath);
	$fileNameField = \ZendSearch\Lucene\Document\Field::text(
		'filename',
		$fileName
	);
	
	//APPEL DU FICHIER PYTHON
<<<<<<< HEAD
	exec('python ./xmpParse.py '.$fileName,$res, $retcode);
=======
	exec('python ../xmpParse.py '.$fileName,$res, $retcode);
>>>>>>> 2353a3b861e45aa1d7a9ab8681aeee0521746912

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
