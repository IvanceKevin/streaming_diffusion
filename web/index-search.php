<!DOCTYPE html>
<html id="ng-app" ng-app="app"> <!-- id="ng-app" IE<8 -->

    <head>
        <title>Streaming diffusion - Upload WAV<</title>
        <link rel="stylesheet" href="./css/bootstrap.min.css" />

        <!-- Fix for old browsers -->
        <script src="http://nervgh.github.io/js/es5-shim.min.js"></script>
        <script src="http://nervgh.github.io/js/es5-sham.min.js"></script>
        <script src="http://code.jquery.com/jquery-1.8.3.min.js"></script>
        <script src="../console-sham.js"></script>

        <script src="./js/bootstrap.min.js"></script>

        <!--<script src="../bower_components/angular/angular.js"></script>-->
        <script src="http://code.angularjs.org/1.1.5/angular.min.js"></script>
        <script src="../angular-file-upload.js"></script>
        <script src="controllers.js"></script>
	<!-- Generic page styles -->
	<link rel="stylesheet" href="css/style.css">
        <style>
            .my-drop-zone { border: dotted 3px lightgray; }
            .nv-file-over { border: dotted 3px red; } /* Default class applied to drop zones on over */
            .another-file-over-class { border: dotted 3px green; }

            html, body { height: 100%; }
        </style>

    </head>

    <!-- 1. nv-file-drop="" uploader="{Object}" options="{Object}" filters="{String}" -->
    <body ng-controller="AppController" nv-file-drop="" uploader="uploader" filters="queueLimit, customFilter">

        <div class="container">
		
            <div class="navbar navbar-inverse navbar-fixed-top">
                <div class="navbar-header">
                    <button type="button" class="navbar-toggle " data-toggle="collapse" data-target=".navbar-fixed-top .navbar-collapse navbar-inverse">
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
            </button>
			
		<img  class="img-header navbar-brand "src="./img/AudioEditor.png" alt="Logo_minia" height="35" width="35">
             <a class="navbar-brand navbar-inverse" href="./index.html">
			Streaming Diffusion</a>
		<a class="navbar-brand navbar-inverse" href="index.html">Recherche</a>
       		<a class="navbar-brand navbar-inverse" href="upload.html">Upload</a>
		<a class="navbar-brand navbar-inverse" href="liste.php">Liste</a>
                </div>
            </div>

            <div class="row  row-centered" align="center">
<?php
require_once "../vendor/autoload.php";
echo '<ul>';

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
				echo '<li><a href="./stream.php?name='.$hit->title.'">' . $hit->title . '</a></li>';	
			}


		} catch (Exception $e) {
			throw new Exception("Requete invalide : " . PHP_EOL . $e, 1);
		}
	}
	else {
		throw new Exception("Veuillez fournir un index existant et une requête de recherche valide", 1);
}
echo '</ul>';
?>       		
	</div>

	</div>

    </body>
</html>


