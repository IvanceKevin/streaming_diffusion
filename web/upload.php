<?php

if ( !empty( $_FILES ) ) {
	
    $tempPath = $_FILES[ 'file' ][ 'tmp_name' ];
    $uploadPath = dirname( __FILE__ ) . DIRECTORY_SEPARATOR . 'uploads' . DIRECTORY_SEPARATOR . $_FILES[ 'file' ][ 'name' ];

    move_uploaded_file( $tempPath, $uploadPath );
	if(!is_dir("./audio_index")) {
		exec("php index-create audio_index",$res,$ret_code);
		echo "Index Créé";
	}
	
	exec("php index-add audio_index ".$_FILES[ 'file' ][ 'name' ],$res,$ret_code);
    $answer = array( 'answer' => 'File transfer completed' );
    $json = json_encode( $answer );

    echo $json;

} else {

    echo 'No files';

}

