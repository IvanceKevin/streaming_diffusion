<?php 

require '../vendor/autoload.php';
$file = file_get_contents('../GypsyPno.xmp', true);
//$fichier = file("../GypsyPno.xmp"); // Nom du fichier à afficher, son adresse de localisation

//print $file;

$dom = new DomDocument;
$dom->loadXml($file);
$xph = new DOMXPath($dom);
$xph->registerNamespace('rdf', "http://www.w3.org/1999/02/22-rdf-syntax-ns#");
foreach($xph->query('//@rdf:descrition') as $attribute) {
    echo $attribute->value;
}