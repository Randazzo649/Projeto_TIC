<?php


    if($_SERVER["REQUEST_METHOD"] == "GET"){
        
        $selecionado = $_GET["selecionado"];
        if($selecionado === "Hoje")
            $selecionado = date("Y-m-d");
        
        $arquivo = "../dados/med/".$selecionado.".json";

        $dados = json_decode(file_get_contents($arquivo, true));

        header("Content-Type: application/json");
        echo json_encode($dados);

    }

?>