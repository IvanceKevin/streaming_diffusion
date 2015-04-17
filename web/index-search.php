<?php
require_once "../vendor/autoload.php";

if(isset($_GET['search']))
{   
	$indexName = 'audio_index';
	$request = $_GET['search'];

	// Vérification si l'index existe
	try {
		$index = \ZendSearch\Lucene\Lucene::open($indexName); 
	} catch (Exception $e) {
		throw new Exception("L'index " . $indexName . " n'existe pas " , 1);
	}
	// Requête
	try {

		$query = \ZendSearch\Lucene\Search\QueryParser::parse($request);
		$find = $index->find($query);
		foreach($find as $hit) {
			echo $hit->title.' '.$hit->score;
		}


	} catch (Exception $e) {
		throw new Exception("Requete invalide : " . PHP_EOL . $e, 1);
	}
}
else {
	throw new Exception("Veuillez fournir un index existant et une requête de recherche valide", 1);
}
