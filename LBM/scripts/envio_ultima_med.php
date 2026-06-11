<?php

    $arquivo = "../dados/".date("Y-m-d").".json";

    if($_SERVER["REQUEST_METHOD"] == "GET"){

        $dados = json_decode(file_get_contents($arquivo, true));
        $ultima_medida = $dados[ count($dados) - 1 ];

        header("Content-Type: application/json");
        echo json_encode($ultima_medida);

    }


    
?>